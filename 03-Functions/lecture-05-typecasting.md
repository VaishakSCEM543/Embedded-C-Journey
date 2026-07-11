# Lecture 05 — Typecasting (Implicit & Explicit)

> **Course Lecture 51** | Kiran Nayak — Microcontroller Embedded C Programming

---

## 🎯 What This Lecture Covers

| Concept | Summary |
|---|---|
| What is typecasting? | Converting a variable/value from one data type to another |
| Implicit casting | Compiler does it automatically — may cause **data loss** → ⚠️ warning |
| Explicit casting | Programmer does it intentionally with `(type)` → no warning |
| When data is truncated | Higher data type → lower data type (e.g., `int` → `unsigned char`) |

---

## 📖 Definition

> **Typecasting** = a way of converting a variable or data from one data type to another data type.

> **Data will be truncated** when a higher data type is converted into a lower data type.

---

## 🔵 Implicit Casting — Compiler Does It Automatically

Implicit casting = the compiler silently promotes or truncates a value to match the target type.

### Example 1 — Storing `int` result into `unsigned char` (with data loss)

```c
unsigned char data = 0x87 + 0x65;
```

**What the compiler sees:**
- `0x87` → compiler treats as `int` (4 bytes) = `0x00000087`
- `0x65` → compiler treats as `int` (4 bytes) = `0x00000065`
- `0x87 + 0x65` = `0x000000EC`  (still fits in 1 byte — **no warning**)

**What about `0x87 + 0xAB`?**
- Sum = `0x00000132` (9 bits — **does NOT fit** in 1 byte!)
- Compiler truncates to `0x32` — **information loss**
- ⚠️ Compiler warning: *"unsigned conversion from 'int' to 'unsigned char' changes value"*

```
Rule: If the result fits → no warning. If result overflows the target → warning (data lost).
```

### Example 2 — Integer division losing fraction

```c
float result = 80 / 3;
```

**What the compiler sees:**
- `80` → `int`
- `3`  → `int`
- `int / int = int` → result is `26` (decimal part **silently dropped**)
- `26` is then implicitly cast to `float` → `26.000000`

⚠️ No warning here — but the fraction is **silently lost**!

---

## 🔴 Explicit Casting — Programmer Does It Intentionally

Explicit casting = you tell the compiler what type to use with `(type)` before the expression.

### Fix Example 1 — Silence the warning + make intent clear

```c
// ❌ Implicit — compiler warns (or silently truncates)
unsigned char data = 0x87 + 0x65;

// ✅ Explicit — programmer is aware, no warning
unsigned char data = (unsigned char)(0x87 + 0x65);
```

By casting, you tell the compiler: *"I know this might truncate — I'm doing it on purpose."*

### Fix Example 2 — Preserve the decimal in division

```c
// ❌ int / int = int → 80 / 3 = 26 (fraction LOST)
float result = 80 / 3;

// ✅ Option A — cast the numerator to float
float result = (float)80 / 3;

// ✅ Option B — cast the denominator to float (same result)
float result = 80 / (float)3;
```

**Why does casting ONE side work?**
- `float / int` → compiler implicitly promotes `int` to `float`
- So `(float)80 / 3` = `float / float` = `26.666...` ✅

---

## 📊 Quick Reference Table

| Expression | Result Type | ⚠️ Issue | ✅ Fix |
|---|---|---|---|
| `int + int` | `int` | None | — |
| `int * int` | `int` | Overflow for large numbers | `(long long int)n1 * n2` |
| `int / int` | `int` | Decimal truncated | `(float)n1 / n2` |
| `int → unsigned char` | `unsigned char` | Data loss if > 1 byte | `(unsigned char)(expr)` |
| `float + int` | `float` | None — implicit promotion | — |
| `float = int / int` | `float` | Still `int` on RHS first! | `(float)n1 / n2` |

---

## 💡 Two Types of Casting — Summary

| Type | Who does it | Syntax | Warning? |
|---|---|---|---|
| **Implicit** | Compiler — automatic | *(no syntax)* | ⚠️ Yes, if data is lost |
| **Explicit** | Programmer — intentional | `(type)expression` | ✅ No — you're in control |

---

## ⚠️ Why Casting Warnings Are Dangerous

> *"Warnings related to casting are very dangerous. Because, most of the time you will lose information. That's why those warnings should be treated with utmost care. Warnings are always dangerous and you should always try to resolve those warnings."* — Kiran Nayak

In **embedded systems** this is critical:
- A sensor reading stored in a truncated variable gives **wrong data**
- Wrong data → wrong decisions by the MCU → **hardware malfunction**

---

## 🏋️ Exercise — Typecasting Exercise Project

> See [`typecast-exercise/`](typecast-exercise/) — a multi-file exercise demonstrating both implicit and explicit casting.

**Files:**
- `math.h` — include guards + 4 prototypes (`add`, `sub`, `mul`, `divf`)
- `math.c` — function definitions with explicit casts (`long long`, `float`)
- `main.c` — demonstrates all operations + implicit cast demo

**Sample output:**
```
ADD : 1ffe2221
SUB : 267386880
MUL : FFE222FF014321
DIV : 26.666667
IMPLICIT CAST (unsigned char): 0xEC
```

---

## 🎓 Interview Questions

**Q1: What is typecasting in C?**
> Typecasting is converting a variable or value from one data type to another. Data may be truncated when converting from a higher data type to a lower one.

**Q2: What is the difference between implicit and explicit casting?**
> **Implicit**: The compiler automatically converts types based on its default rules. It can cause silent data loss and generate warnings. **Explicit**: The programmer manually specifies the target type using `(type)` syntax, making the intent clear and suppressing warnings.

**Q3: Why does `float result = 80 / 3` give `26.000000` instead of `26.666...`?**
> Because `80` and `3` are both `int` literals. `int / int = int` — the division is done in integer arithmetic and the decimal is truncated to `26`. Only then is `26` assigned to `float`. Fix: `(float)80 / 3`.

**Q4: Why is it important to cast BEFORE the operation?**
> Because by the time the result is computed, the data is already lost. You must promote the type of one operand before the operation runs: `(long long int)n1 * n2` — not `(long long int)(n1 * n2)`.
