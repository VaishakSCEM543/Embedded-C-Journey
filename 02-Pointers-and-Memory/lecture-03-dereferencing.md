# Lecture 3 — Dereferencing & Pointer Arithmetic in Practice

## 1. What is Dereferencing?

Break the word apart:

```
de  +  reference
```

A **reference** is something that *refers to* (points at) something else — i.e., an address.

**De-reference** means: *undo* the reference — stop looking at the address, go **to** that address, and grab the actual value.

```
ptr  →  stores ADDRESS   (e.g. 0061FF18)
*ptr →  goes TO that address and returns the VALUE there
```

> `*` in front of a pointer = "go fetch what's at that address"

---

## 2. The `&` and `*` Operators

| Operator | Name | Meaning |
|:---------|:-----|:--------|
| `&a` | Address-of | Give me the address where `a` lives |
| `*ptr` | Dereference | Go to the address stored in `ptr`, get the value |

```c
int a = 5;
int *ptr = &a;   /* ptr now holds the address of a */

printf("%p", ptr);   /* prints the ADDRESS — e.g. 0061FF18 */
printf("%d", *ptr);  /* dereferences — prints the VALUE  — 5 */
```

---

## 3. Writing Through a Pointer

You can **change a variable's value using its pointer** — without using the variable's name at all:

```c
int a = 5;
int *ptr = &a;

*ptr = 365;   /* writes 365 to the address where a lives */

printf("%d", a);    /* 365 — a was changed via pointer! */
printf("%d", *ptr); /* 365 — same location */
```

This is the core of how C is used in embedded systems: write to an address → control hardware.

---

## 4. Pointer Arithmetic

When you do `ptr + 1`, you do **not** add 1 to the address.

You add **sizeof(the type it points to)** bytes.

For `int*` on a 32-bit/64-bit system, `sizeof(int) = 4`:

```c
int a = 5;
int *ptr = &a;        /* ptr = 0061FF18 */

ptr = ptr + 1;        /* ptr = 0061FF1C  (+4 bytes, not +1) */
```

```
Address     Data
-------------------
0061FF18    5      ← ptr originally (a lives here)
0061FF1C    ???    ← ptr after +1   (unknown — not our variable!)
```

> ⚠️ **Never dereference a pointer after arithmetic unless you know what's there.**
> Moving the pointer into unknown memory and reading/writing it causes bugs or crashes.

---

## 5. The Safe Pattern — Reset After Arithmetic

If you need to do pointer arithmetic and then write, **reset the pointer first**:

```c
ptr = ptr + 1;           /* fine — just looking at address */
printf("%p", ptr);       /* prints the new address */
printf("%d", *ptr);      /* ⚠️ reading unknown memory — garbage */

ptr = &a;                /* RESET: point back to a — safe again */
*ptr = 365;              /* ✅ safe write — we know this address is valid */
```

---

## 6. Full Code Walk-through (from session)

```c
#include <stdio.h>

int main()
{
    int a = 3;
    printf("%d \n", a);   /* 3 */
    a = a + 1;
    printf("%d \n", a);   /* 4 */
    a = a + 1;
    printf("%d \n", a);   /* 5 */

    int* ptr = &a;
    printf("%p \n", ptr);  /* 0061FF18 — address of a */
    printf("%d \n", *ptr); /* 5        — value at that address */

    ptr = ptr + 1;
    printf("%p \n", ptr);  /* 0061FF1C — 4 bytes forward */
    printf("%d \n", *ptr); /* garbage  — unknown memory */

    ptr = &a;              /* reset to safe address */
    *ptr = 365;
    printf("%p \n", ptr);  /* 0061FF18 — back to a */
    printf("%d \n", *ptr); /* 365      — a is now 365 */

    return 0;
}
```

### Output:
```
3
4
5
0061FF18
5
0061FF1C
6422300    ← garbage (could be anything)
0061FF18
365
```

---

## 7. Two Worlds of a Pointer

Keep this table burned into your memory:

```
Variable   │  Meaning
───────────┼──────────────────────────────────────
ptr        │  the ADDRESS (e.g. 0061FF18)
*ptr       │  the VALUE at that address (e.g. 5)
&a         │  the ADDRESS of variable a
```

- `ptr == &a`   → both equal `0061FF18` ✅
- `*ptr == a`   → both equal the value stored there ✅

---

## 8. Why the Name "Dereference"?

```
reference   = pointer = something that REFERS TO a location
de-reference = UNDO the reference = don't look at the address,
               look at what IS at the address
```

Same idea as:
- **encrypt** → **decrypt** (undo encryption)
- **reference** → **dereference** (undo the indirection, get the actual value)

---

## 9. Embedded Relevance

In STM32 code, you will see:

```c
#define RCC_AHB1ENR  *((volatile unsigned int *) 0x40023830)

RCC_AHB1ENR |= (1 << 0);   /* Enable GPIOA clock */
```

What that line does:
1. Take the raw address `0x40023830`
2. Cast it to `unsigned int *` (a pointer to an unsigned int)
3. Dereference with `*` — go to that hardware register
4. Write the value — which physically enables the clock on the chip

> **Dereferencing is not an abstract concept. It is the instruction that drives the hardware.**

---

## 💡 Key Takeaways

| Concept | Summary |
|:--------|:--------|
| `*ptr` | Dereference — get the value at the address |
| `ptr + 1` | Move pointer `sizeof(type)` bytes forward |
| Reset to `&var` | Always reset before writing via arithmetic |
| `ptr == &a` | The pointer holds the address of `a` |
| `*ptr == a` | Both refer to the same value |
