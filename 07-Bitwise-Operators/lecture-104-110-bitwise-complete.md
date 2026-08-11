# Module: Bitwise Operators in C — Lectures 104–110

# Complete Bit Manipulation: TEST, SET, CLEAR, TOGGLE

---

## 🎯 Learning Objectives

After this module, you will understand:

* All four fundamental bit manipulation operations.
* The correct operator and mask for each operation.
* The six core bitwise identities that make everything logical.
* The standard Embedded C register programming patterns.
* Interview questions on bitwise operators.

---

## Part 1 — The Foundation

### The Six Bitwise Operators

| Operator | Name |
|:--------:|:-----|
| `&` | AND |
| `\|` | OR |
| `^` | XOR |
| `~` | NOT (bitwise complement) |
| `<<` | Left Shift |
| `>>` | Right Shift |

---

### Bitwise vs Logical — Don't Mix Them Up

| | Logical | Bitwise |
|:--|:--------|:--------|
| AND | `&&` | `&` |
| OR | `\|\|` | `\|` |
| NOT | `!` | `~` |
| XOR | *(none)* | `^` |

**Logical** operators work on true/false (0 vs non-zero).
**Bitwise** operators work on individual bits of the integer.

> [!IMPORTANT]
> `if (data && mask)` vs `if (data & mask)` — these are completely different. The first is logical, the second is bitwise. In embedded C, you almost always want `&`.

---

## Part 2 — The Six Core Identities

These six lines replace memorizing dozens of rules:

```
AND:   X & 0 = 0        X & 1 = X
OR:    X | 0 = X        X | 1 = 1
XOR:   X ^ 0 = X        X ^ 1 = toggle(X)
```

If you understand these, all four operations become logical.

---

## Part 3 — TEST (AND)

### What it means
> "Is this bit 0 or 1?"

### Operator: `&`

### Why?
```
X & 1 = X     ← target bit: reveals its value
X & 0 = 0     ← other bits: forced to 0, don't affect result
```

### Mask
- Target bit → **1**
- All other bits → **0**

### Example — Test Bit 3
```c
data = 10100100

mask = 00001000

data & mask = 00000000   → Bit 3 is 0

data = 10101100
data & mask = 00001000   → Bit 3 is 1 (non-zero = true)
```

### Pattern
```c
if (data & mask)
{
    /* bit is 1 */
}
```

---

## Part 4 — SET (OR)

### What it means
> "Force this bit to 1."

### Operator: `|`

### Why?
```
X | 1 = 1     ← target bit: always becomes 1
X | 0 = X     ← other bits: stay unchanged
```

### Mask
- Target bit → **1**
- All other bits → **0**

### Example — Set Bits 7 and 4

We want Bit 7 = 1 and Bit 4 = 1:

```
Bit:    7 6 5 4 3 2 1 0
Mask:   1 0 0 1 0 0 0 0   =  0x90
```

```
  01010101
| 10010000
-----------
  11010101

Bit 7 → 1  ✅
Bit 4 → 1  ✅
Others unchanged ✅
```

### Why AND fails here
```
  01010101
& 10010000
-----------
  00010000   ← other bits destroyed! ❌
```

### Pattern
```c
data |= 0x90;       /* set Bit 7 and Bit 4 */
GPIO |= mask;       /* Embedded C idiom */
```

---

## Part 5 — CLEAR (AND + NOT)

### What it means
> "Force this bit to 0."

### Operator: `&`

### Why?
```
X & 0 = 0     ← target bit: forced to 0
X & 1 = X     ← other bits: stay unchanged
```

### Mask (different from TEST!)
- Target bit → **0**
- All other bits → **1**

Notice: this mask is the **opposite** of the SET mask.

### Example — Clear Bits 4, 5, 6

```
Bit:    7 6 5 4 3 2 1 0
Mask:   1 0 0 0 1 1 1 1   =  0x8F
```

```
  10110111
& 10001111
-----------
  10000111

Bits 4, 5, 6 → 0 ✅
Others unchanged ✅
```

### Method 1 — Direct mask
```c
data &= 0x8F;
```

### Method 2 — NOT mask (preferred in embedded)

Instead of manually computing `0x8F`, create a mask for the bits you *want to clear*, then invert it:

```
Target bits:  0 1 1 1 0 0 0 0  =  0x70
~0x70      =  1 0 0 0 1 1 1 1  =  0x8F   ← exactly what we need
```

```c
data &= ~(0x70);        /* cleaner and more readable */
```

### With shift operators (preview — fully covered later)
```c
data &= ~(7 << 4);      /* 7 = 111, shifted to bits 4-6 */
```

### Pattern
```c
data &= ~mask;          /* the standard embedded C clear pattern */
GPIO &= ~(1 << 3);      /* clear Bit 3 */
```

---

## Part 6 — TOGGLE (XOR)

### What it means
> "Reverse the current state of this bit."

### Operator: `^`

### XOR Truth Table

| A | B | A ^ B |
|:-:|:-:|:-----:|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

**Easy rule: same → 0, different → 1**

### Why it toggles
```
0 ^ 1 = 1   →   0 becomes 1
1 ^ 1 = 0   →   1 becomes 0

X ^ 0 = X   →   other bits unchanged
X ^ 1 = ~X  →   target bit flips
```

### Example — Toggle Bit 3
```
DATA = 10100100

  10100100
^ 00001000
-----------
  10101100   (0 → 1) ✅

  10101100
^ 00001000
-----------
  10100100   (1 → 0) ✅
```

### Real embedded example — LED blink
```c
/* Without XOR */
while(1) {
    if (LED == 0) LED = 1;
    else          LED = 0;
}

/* With XOR — much cleaner */
while(1) {
    LED ^= 1;
}
```

### Pattern
```c
data ^= mask;
GPIO ^= 0x08;   /* toggle Bit 3 */
```

---

## Part 7 — All Four Operations Side-by-Side

```
// TEST  — is Bit 3 set?
if (GPIO & 0x08)

// SET   — turn on Bit 3
GPIO |= 0x08;

// CLEAR — turn off Bit 3
GPIO &= ~0x08;

// TOGGLE — flip Bit 3
GPIO ^= 0x08;
```

> [!TIP]
> These four patterns are the most important 4 lines in embedded C programming. You will write them thousands of times when working with microcontroller registers.

---

## Part 8 — The Complete Reference Table

| Operation | Operator | Mask (target) | Mask (others) | Embedded Pattern |
|:----------|:--------:|:-------------:|:-------------:|:----------------|
| **TEST** | `&` | 1 | 0 | `if (REG & MASK)` |
| **SET** | `\|` | 1 | 0 | `REG \|= MASK;` |
| **CLEAR** | `&` | 0 | 1 | `REG &= ~MASK;` |
| **TOGGLE** | `^` | 1 | 0 | `REG ^= MASK;` |

### The Six Identities

```
X & 0 = 0         X & 1 = X
X | 0 = X         X | 1 = 1
X ^ 0 = X         X ^ 1 = ~X
```

---

## ⚠️ Common Mistakes

| Mistake | Why It's Wrong |
|:--------|:---------------|
| `data && mask` instead of `data & mask` | `&&` is logical, not bitwise |
| Using `\|` to clear bits | OR forces bits to 1, not 0 |
| `data &= mask` to clear (no `~`) | AND with 0s destroys other bits |
| Confusing Bit 3 with value 3 | Bit 3 mask = `0x08` (= `00001000`), not `3` |

---

## 🎯 Interview Questions

**Q1. How do you test if a specific bit is set?**
```c
if (data & (1 << n))   /* n = bit position */
```

**Q2. How do you set a bit?**
```c
data |= (1 << n);
```

**Q3. How do you clear a bit?**
```c
data &= ~(1 << n);
```

**Q4. How do you toggle a bit?**
```c
data ^= (1 << n);
```

**Q5. Why is `&` used for both TEST and CLEAR?**
Same operator, different masks. TEST mask has 1 at target. CLEAR mask has 0 at target (achieved via `~`).

**Q6. Why can't you use OR to clear a bit?**
Because `X | 1 = 1` always — OR can only force bits to 1, never to 0.

**Q7. What does `data &= ~mask` mean step by step?**
1. `mask` has 1s at bits to clear, 0s elsewhere.
2. `~mask` inverts: 0s at bits to clear, 1s elsewhere.
3. `data & ~mask` forces target bits to 0, leaves others unchanged.

---

## 📊 Output-Based Interview Questions

```c
printf("%d", 5 & 3);    // 5=101, 3=011 → 001 = 1
printf("%d", 5 | 3);    // 5=101, 3=011 → 111 = 7
printf("%d", 5 ^ 3);    // 5=101, 3=011 → 110 = 6

if (10 & 1)  printf("Odd");  else printf("Even");  // 10=1010, LSB=0 → Even
if (11 & 1)  printf("Odd");  else printf("Even");  // 11=1011, LSB=1 → Odd
```

> [!NOTE]
> `number & 1` checks the LSB — this is the classic bitwise even/odd test.

---

## 📌 Quick Revision Cheat Sheet

```
╔══════════════════════════════════════════╗
║          BITWISE OPERATORS IN C          ║
╠══════════════════════════════════════════╣
║  &   → AND    |   → OR                  ║
║  ^   → XOR    ~   → NOT                 ║
║  <<  → Left   >>  → Right Shift         ║
╠══════════════════════════════════════════╣
║  TEST   → &                             ║
║  SET    → |                             ║
║  CLEAR  → & + ~                         ║
║  TOGGLE → ^                             ║
╠══════════════════════════════════════════╣
║  X & 0 = 0    X & 1 = X                 ║
║  X | 0 = X    X | 1 = 1                 ║
║  X ^ 0 = X    X ^ 1 = toggle X          ║
╠══════════════════════════════════════════╣
║  if (REG & MASK)     // TEST             ║
║  REG |= MASK;        // SET              ║
║  REG &= ~MASK;       // CLEAR            ║
║  REG ^= MASK;        // TOGGLE           ║
╚══════════════════════════════════════════╝
```

> **Placement Tip:** Don't memorize these as formulas. Understand the chain:
> → Which bits do I want to affect? → Build the mask → Choose operation (SET/CLEAR/TOGGLE/TEST) → Apply the corresponding operator.
>
> Next: **Shift Operators (`<<` and `>>`)** — these make expressions like `1 << 3` and `data &= ~(1 << 3)` fully understandable.
