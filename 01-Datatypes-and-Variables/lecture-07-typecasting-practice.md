# Lecture 07 — Typecasting Practice & Multi-File Exercise

> **Date studied:** 13 Jul 2026
> **Status:** In progress — actively practising typecasting concepts

---

## What is Typecasting?

Typecasting = converting a variable/value from **one data type to another**.

> Warning: Data loss rule — converting from a higher data type to a lower data type **truncates** the data.

---

## Two Types of Casting

### 1. Implicit Casting (Automatic / Assumed)
- Done **by the compiler** automatically, according to its default promotion rules.
- You don't write anything — the compiler decides.

**Example:**
```c
unsigned char data = 0x87 + 0x65;
// Both constants are treated as int (4 bytes) by the compiler.
// Compiler stores the result (0xEC) into unsigned char ? implicit truncation.
// WARNING: possible data loss!
```

**Key rule:** Integer constants without a suffix are `int` (4 bytes) by default.

---

### 2. Explicit Casting (Manual / Programmer-controlled)
- Done **by the programmer** using the cast operator: `(type)`.
- Overrides what the compiler would do by default.

**Fix with explicit cast:**
```c
unsigned char data = (unsigned char)(0x87 + 0x65);  /* explicit ? no warning */
```

---

## When Explicit Casting is Critical

### Case 1 — Integer Multiplication Overflow

```c
/* WRONG — int * int = int ? overflow for large values */
long long int result = n1 * n2;

/* CORRECT — cast BEFORE multiply so promotion happens first */
long long int result = (long long int)n1 * n2;
// n1 promoted to 8 bytes, THEN multiplied by n2.
// long long * int = long long ? no overflow.
```

> Why does order matter?
> n1 * n2 is evaluated as int * int first (overflow), THEN stored.
> (long long)n1 * n2 promotes n1 first, so the multiply happens in 8 bytes.

---

### Case 2 — Integer Division Truncation

```c
/* WRONG — int / int = int ? decimal part lost */
float result = 80 / 3;        /* result = 26.0, NOT 26.666... */

/* CORRECT — cast numerator to float BEFORE divide */
float result = (float)80 / 3;
// Numerator becomes float.
// Compiler implicitly promotes denominator to float too.
// float / float = float ? 26.666...
```

Both of these work:
```c
(float)n1 / n2   /* cast numerator */
n1 / (float)n2   /* cast denominator — same result */
```

---

## Multi-File Exercise — Math Project (Lecture 13)

Practised in a 3-file project: main.c + math.c + math.h

| File    | Role |
|---------|------|
| math.h  | Header — function prototypes + include guard |
| math.c  | Definitions — actual function logic |
| main.c  | Test driver — calls each function, prints result |

### Functions implemented:

| Function       | Return type    | Cast used           | Why                  |
|----------------|---------------|---------------------|----------------------|
| add(n1, n2)    | int           | none                | Safe for normal ranges |
| sub(n1, n2)    | int           | none                | Safe                 |
| mul(n1, n2)    | long long int | (long long int)n1   | Prevent overflow     |
| divf(n1, n2)   | float         | (float)n1           | Prevent truncation   |

### Compile command:
```bash
gcc main.c math.c -o math
```

---

## Casting Warnings — Treat with Utmost Care

From the lecture:
"Warnings related to casting are very dangerous. Because most of the time you will lose information.
Those warnings should be treated with utmost care. Warnings are always dangerous and you should
always try to resolve them."

### Common warning types:
- warning: implicit conversion loses integer precision
- warning: conversion to 'unsigned char' from 'int' may alter its value

Fix: always use explicit cast (type) when you intentionally convert down.

---

## C Type Promotion Rules (Quick Reference)

  char ? short ? int ? long ? long long
                  ?
                float ? double ? long double

- When two different types meet in an expression, the smaller is promoted to the larger.
- Integer constants default to int.
- Override with suffix: 100LL (long long), 100.0f (float), 100U (unsigned).

---

## Interview Q&As

**Q1. Difference between implicit and explicit casting?**
A: Implicit = compiler automatic (e.g., int ? float in mixed expression).
   Explicit = programmer-specified using (type) cast operator to override defaults.

**Q2. Why does (long long int)n1 * n2 work but (long long int)(n1 * n2) may not?**
A: First form promotes n1 before the multiply — arithmetic is in 8 bytes.
   Second form computes n1 * n2 as int * int (possible overflow) first, THEN casts — too late.

**Q3. Default data type for an integer constant in C?**
A: int (4 bytes). So 0x87 is treated as a 4-byte int, even if it fits in 1 byte.

**Q4. How to force float division without changing variable types?**
A: Cast either operand: (float)n1 / n2  OR  n1 / (float)n2.

**Q5. What happens when you assign a larger type into a smaller type without a cast?**
A: Compiler truncates the higher bytes and emits a warning.
   Example: storing int 0x1234 into unsigned char keeps only 0x34.
