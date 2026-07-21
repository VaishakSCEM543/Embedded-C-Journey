# Lecture 5 — Pointer Arithmetic

## The Rule

When you do `pAddress + 1`, it does **not** add 1 to the stored address.

It adds `sizeof(pointer_type)` bytes.

```
char*      + 1  →  address moves by  1  byte
short*     + 1  →  address moves by  2  bytes
int*       + 1  →  address moves by  4  bytes
long long* + 1  →  address moves by  8  bytes
```

This is called **pointer arithmetic** and it is by design — when you move to the "next element", you want to land at the correct position in memory for that type.

---

## Verified in Code

```c
long long int g_data = 0xFFFEABCD11112345;
```

Memory layout (little-endian, low address first):

```
Address   Data
00404008   45   ← LSB first
00404009   23
0040400A   11
0040400B   11
0040400C   CD
0040400D   AB
0040400E   FE
0040400F   FF
```

### char* — offset 1

```c
char *pAddress = (char*)&g_data;
// base address : 00404008 , value : 45
pAddress = pAddress + 1;
// after +1     : 00404009 , value : 23   <- moved exactly 1 byte
```

### short* — offset 2

```c
short *pAddress2 = (short*)&g_data;
// base address : 00404008 , value : 2345
pAddress2 = pAddress2 + 1;
// after +1     : 0040400A , value : 1111  <- moved 2 bytes
```

### int* — offset 4

```c
int *pAddress3 = (int*)&g_data;
// base address : 00404008 , value : 11112345
pAddress3 = pAddress3 + 1;
// after +1     : 0040400C , value : fffeabcd  <- moved 4 bytes
```

---

## Why the Compiler Scales It

If you have an array `int arr[4]`, each element is 4 bytes apart.

`arr + 1` needs to point to the next int — which is 4 bytes away, not 1.

The compiler automatically multiplies your `+N` by `sizeof(type)` so that `arr[1]` always means the second element regardless of type.

---

## Embedded Relevance

In MCU register access you often step through memory-mapped registers:

```c
volatile uint32_t *reg = (uint32_t*)0x40020000;   /* base of GPIOA */
reg + 0  →  MODER    (offset 0)
reg + 1  →  OTYPER   (offset 4)   /* +1 on uint32_t* moves 4 bytes */
reg + 2  →  OSPEEDR  (offset 8)
```

This is why peripheral registers are declared as `uint32_t*` — so that `+1` steps exactly 4 bytes to the next 32-bit register.

If you used `char*`, `+1` would step 1 byte and you would land in the wrong register.

---

## Summary Table

| Pointer Type | `+ 1` moves by | `+ N` moves by |
|:-------------|:--------------|:--------------|
| `char *`     | 1 byte         | N bytes         |
| `short *`    | 2 bytes        | N × 2 bytes     |
| `int *`      | 4 bytes        | N × 4 bytes     |
| `long long *`| 8 bytes        | N × 8 bytes     |
