# Lecture 4 — Effect of Pointer Data Type on Pointer Operations

## The Core Rule

The **data type of the pointer** decides how many bytes get fetched when you dereference it.

```
char*      →  reads 1 byte
short*     →  reads 2 bytes
int*       →  reads 4 bytes
long long* →  reads 8 bytes
```

All four can point to the exact same address. What changes is how much memory they pull from that address on dereference.

---

## Code Setup

```c
long long int g_data = 0xFFFEABCD11223344;  /* 8 bytes */
```

All four pointer variables point to `&g_data`. Only their types differ.

```c
char      *pAddress1 = (char*)     &g_data;
int       *pAddress2 = (int*)      &g_data;
short     *pAddress3 = (short*)    &g_data;
long long *pAddress4 = (long long*)&g_data;
```

---

## Output and What It Means

```
char* read (1 byte)  : 44              ← only the first byte fetched
int*  read (4 bytes) : 11223344        ← first 4 bytes fetched
short* read (2 bytes): 3344            ← first 2 bytes fetched
long long* (8 bytes) : FFFEABCD11223344 ← all 8 bytes fetched
```

The values come out in little-endian order (x86 stores LSB at the lowest address).

---

## The Typecasting Requirement

`g_data` is `long long int`, so `&g_data` is of type `long long int*`.

If you store it in a `char*` without casting, the compiler gives a warning:

```
warning: initialization from incompatible pointer type
```

Fix → explicit cast:

```c
char *pAddress1 = (char*)&g_data;   /* tells compiler: I know, do it anyway */
```

No information is lost here — you are just storing the address. The cast just makes LHS and RHS types match.

---

## Two Pointer Syntax Styles

Both are identical. The instructor switches to the second style from this lecture onwards:

```c
char* pAddress1 = &g_data;   /* style 1 - asterisk attached to type */
char *pAddress1 = &g_data;   /* style 2 - asterisk attached to name */
```

Style 2 is preferred in most books and codebases. Either is fine.

---

## Why This Matters in Embedded

When reading hardware registers, the number of bytes you fetch matters a lot.

- Reading a 1-byte status register → use `char*` or `uint8_t*`
- Reading a 4-byte control register → use `int*` or `uint32_t*`
- Reading the wrong size means you get wrong data or corrupt adjacent registers

This is why every peripheral register in STM32 HAL is typed as `volatile uint32_t *` — because those registers are exactly 4 bytes wide.

---

## Summary

| Pointer Type | Bytes Read on Dereference |
|:-------------|:--------------------------|
| `char *`     | 1 |
| `short *`    | 2 |
| `int *`      | 4 |
| `long long *`| 8 |

Same address. Same memory. Different pointer type = different amount read.
