# Lecture 04 — Multi-file Projects & Header Files

> **Course Lecture 50** | Kiran Nayak — Microcontroller Embedded C Programming

---

## 🎯 What This Lecture Covers

| Concept | Summary |
|---|---|
| Multi-file C project | Split code across `main.c` and `math.c` |
| Header file (`math.h`) | Expose function prototypes using include guards |
| `#include "user.h"` vs `#include <std.h>` | Double quotes vs angle brackets |
| Explicit typecasting | Fix `int * int` overflow and `int / int` truncation |

---

## 🗂️ Project Structure

```
math-project/
├── math.h      ← function PROTOTYPES (shared interface)
├── math.c      ← function DEFINITIONS (implementation)
└── main.c      ← calls functions from math.c via math.h
```

```
Compile:  gcc main.c math.c -o math.exe -Wall
```

The two source files are compiled **together** — GCC links them automatically.

---

## 📄 math.h — The Header File

```c
#ifndef MATH_H_
#define MATH_H_

int           math_add(int n1, int n2);
int           math_sub(int n1, int n2);
long long int math_mul(int n1, int n2);   // long long → 8-byte result
float         math_div(int n1, int n2);   // float     → decimal result

#endif /* MATH_H_ */
```

### Include Guards — Why They Exist

```c
#ifndef MATH_H_    // "if math.h has NOT been included before..."
#define MATH_H_    // mark it as included now
   // ... prototypes ...
#endif             // end of guard
```

**Without guards:** If two files both `#include "math.h"`, the preprocessor pastes
math.h contents **twice** → duplicate declaration error.  
**With guards:** Second inclusion is silently skipped. ✅

---

## 📄 math.c — The Implementation

```c
#include "math.h"   // include own header to keep prototypes in sync

int math_add(int n1, int n2)        { return n1 + n2; }
int math_sub(int n1, int n2)        { return n1 - n2; }

long long int math_mul(int n1, int n2)
{
    return (long long int)n1 * n2;  // EXPLICIT CAST — see below
}

float math_div(int n1, int n2)
{
    return (float)n1 / n2;          // EXPLICIT CAST — see below
}
```

---

## 📄 main.c — The Caller

```c
#include <stdio.h>
#include "math.h"   // ← double quotes for user-defined headers

int main(void)
{
    printf("Add : %d\n",    math_add(0x0FFF1111, 0x0FFF1111));
    printf("Sub : %d\n",    math_sub(0x0FFF1111, 0x000F1111));
    printf("Mul : %I64X\n", math_mul(0x0FFF1111, 0x0FFF1111)); // Windows: I64X
    printf("Div : %f\n",    math_div(100, 8));
    return 0;
}
```

---

## 🔑 Key Concept 1 — `#include` Double Quotes vs Angle Brackets

| Syntax | When to use | Where compiler looks |
|---|---|---|
| `#include <stdio.h>` | Standard library headers | System include paths |
| `#include "math.h"` | **Your own** (user-defined) headers | Current directory first, then system |

> ❌ `#include <math.h>` — WRONG for user files (looks in system paths only)  
> ✅ `#include "math.h"` — CORRECT for user-defined headers

---

## 🔑 Key Concept 2 — Explicit Typecasting

### Problem 1: Integer Multiplication Overflow

```c
// 0x0FFF1111 × 0x0FFF1111 = a very large 8-byte number
int n1 = 0x0FFF1111;
int n2 = 0x0FFF1111;

// ❌ WRONG — int * int = int (only 4 bytes — upper bytes LOST)
long long int result = n1 * n2;

// ✅ CORRECT — cast one operand to long long int FIRST
//    long long int * int = long long int (8 bytes — no loss)
long long int result = (long long int)n1 * n2;
```

**Rule:** The cast must happen **before** the operation. Once overflow occurs, the data is already lost.

### Problem 2: Integer Division Truncation

```c
// ❌ WRONG — int / int = int (decimal truncated)
//    100 / 8 = 12  (not 12.5)
float result = 100 / 8;

// ✅ CORRECT — cast one operand to float FIRST
//    float / int = float (decimal preserved)
//    100.0f / 8 = 12.5
float result = (float)100 / 8;
```

### Typecasting Rules

| Expression | Result Type | Notes |
|---|---|---|
| `int + int` | `int` | Normal |
| `int * int` | `int` | ⚠️ overflow risk for large numbers |
| `(long long)int * int` | `long long int` | ✅ Safe |
| `int / int` | `int` | ⚠️ decimal truncated |
| `(float)int / int` | `float` | ✅ Decimal preserved |
| `float + int` | `float` | Implicit promotion |

### Two Types of Casting

| Type | How | Example |
|---|---|---|
| **Explicit** (manual) | You write the cast | `(float)n1 / n2` |
| **Implicit** (automatic) | Compiler promotes silently | `float x = 5;` → 5.0 |

---

## ✅ Program Output

```
Add : 536748578        ← 0x0FFF1111 + 0x0FFF1111 = 0x1FFE2222
Sub : 267362304        ← 0x0FFF1111 - 0x000F1111
Mul : FFE222FF014321   ← correct 8-byte hex (would be wrong without cast)
Div : 12.500000        ← correct float (would be 12 without cast)
```

---

## 🔗 How the Linker Sees This

```
gcc main.c math.c -o math.exe
      │         │
      │         └── compiled to math.o  (function bodies)
      └──────────── compiled to main.o  (function calls)
                            │
                    linker resolves calls
                    in main.o to bodies in math.o
                            │
                         math.exe ✅
```

`math.h` gives `main.c` the **signature** at compile time.  
The linker connects the actual **call** to the actual **body** at link time.

---

## 💡 Embedded Perspective

In STM32 HAL, this exact pattern is everywhere:

```
stm32f4xx_hal_gpio.h  ← prototypes (you #include this)
stm32f4xx_hal_gpio.c  ← definitions (compiled and linked automatically)
```

```c
// You write this in your main.c:
#include "stm32f4xx_hal.h"
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

// You never touch stm32f4xx_hal_gpio.c
// The linker connects your call to HAL's implementation
```

This is why understanding multi-file projects is **essential for embedded**.

---

## 🎓 Interview Questions

**Q1: What is a header file and why do we need it?**
> A header file (`.h`) contains function prototypes, macro definitions, and type declarations. It acts as the **interface** between the implementation (`.c`) and its users. Any file that wants to call functions in `math.c` includes `math.h` to learn the signatures — without needing to see `math.c`'s internals.

**Q2: What are include guards and why are they necessary?**
> Include guards (`#ifndef / #define / #endif`) prevent a header file's contents from being pasted multiple times when included by multiple files. Without them, duplicate declarations cause compiler errors.

**Q3: What is the difference between `#include <stdio.h>` and `#include "math.h"`?**
> Angle brackets search only in the compiler's **system include paths** (standard library). Double quotes search the **current directory first**, then system paths. User-defined headers must use double quotes.

**Q4: Why does `int * int` give the wrong result for large numbers?**
> Both operands are 32-bit `int`, so the multiplication is performed in 32-bit arithmetic. If the result exceeds 32 bits, the upper bits are silently discarded — this is integer overflow. The fix is to cast one operand to `long long int` before multiplying, promoting the entire operation to 64-bit.

**Q5: Why does `int / int` not give a decimal result?**
> C performs **integer division** when both operands are integers — the fractional part is truncated, not rounded. To get a float result, at least one operand must be cast to `float` before the division.

**Q6: What is explicit vs implicit typecasting?**
> **Explicit** = you write the cast manually: `(float)n1 / n2`. **Implicit** = compiler promotes automatically, e.g., `float x = 5;` where `5` (int) is implicitly converted to `5.0` (float). Explicit casting is preferred in embedded code for clarity and control.
