# Lecture 07 — Type Casting in C

> One of the most important lectures in C — especially for embedded systems.
> Type casting is everywhere: ADC conversions, sensor data, UART/SPI/I2C, register operations.

---

## The Core Idea

Think of different containers:

```
Cup (1 L)   →  char  (1 byte)
Bucket (10 L) →  int   (4 bytes)
Tank (100 L)  →  long  (8 bytes)
```

Water = data.  
Moving water between containers = type casting.

> **Type casting = converting data from one data type to another.**

```c
int num = 100;
float value = (float)num;   // int → float
```

---

## Two Types of Casting

```
Type Casting
│
├── Implicit  (compiler does it automatically)
└── Explicit  (you tell the compiler what to do)
```

---

## 1. Implicit Casting

**The compiler converts automatically. You write nothing.**

```c
float value = 10;    // compiler converts 10 (int) → 10.0 (float). No warning.
```

```c
char x = 100;        // 100 fits in a char. No warning.
```

### When does it go wrong?

```c
unsigned char x = 0x1FF;
```

The compiler treats `0x1FF` as an `int` (4 bytes) by default.

```
int:   0x000001FF  →  00000000 00000000 00000001 11111111
                                                  ^^^^^^^^
                                                  only this fits in 1 byte
unsigned char:       11111111  =  0xFF
```

`0x1FF` became `0xFF`. **Data lost. Compiler warns.**

> ⚠️ This is called **truncation** — the upper bytes are silently discarded.

### When is there NO warning?

```c
unsigned char x = 0x8A;   // 0x8A already fits in 1 byte → no loss → no warning
```

### The Rule

```
Larger type → Smaller type   ⚠️  possible data loss
Smaller type → Larger type   ✅  always safe
```

---

## 2. Explicit Casting

**You write the cast. You take responsibility.**

```c
x = (unsigned char)(0x87 + 0x89);
      ^^^^^^^^^^^^^
      You're telling the compiler: "I know. Do it anyway."
```

Since you decided, the compiler won't warn.

---

## The Classic Bug — Integer Division

```c
float result = 80 / 3;
```

Most people expect `26.6667`. They get `26.000000`.

**Why?**

```
80  →  int
3   →  int
─────────────
int / int = int   →   80 / 3 = 26   (fraction dropped)

Then: 26 (int) → 26.0 (float)   [implicit cast, but too late!]
```

The fraction was lost BEFORE the float conversion. Converting to float after can't bring it back.

### Fix — cast BEFORE dividing

```c
float result = (float)80 / 3;
```

Now:
```
(float)80  →  80.0f
80.0f / 3  →  compiler promotes 3 to float automatically
80.0 / 3.0 →  26.666666  ✅
```

> You only need to cast ONE operand. C automatically promotes the other one.

---

## Implicit vs Explicit — Side by Side

| | Implicit | Explicit |
|---|---|---|
| **Who does it** | Compiler | Programmer |
| **Syntax** | Nothing | `(type)` |
| **Control** | Compiler's rules | You decide |
| **Warning** | Possible (on data loss) | Usually none |
| **Example** | `float x = 10;` | `(float)10 / 3` |

---

## Real Embedded Example — ADC to Voltage

```c
uint16_t adc = 2048;

// WRONG — integer division
float voltage = adc / 4095 * 3.3;
// 2048 / 4095 = 0 (int division!) → voltage = 0.0  ❌

// CORRECT — cast first
float voltage = ((float)adc / 4095) * 3.3f;
// 2048.0 / 4095.0 = 0.5001 → × 3.3 = 1.65V  ✅
```

This exact bug kills real embedded projects. Always cast before integer division.

---

## Common Embedded Casts

```c
(float)adc_value         // ADC raw → voltage calculation
(uint8_t)data            // keep only low 8 bits for UART/SPI/I2C
(uint32_t)timer_ticks    // widen to prevent overflow
(int16_t)raw_sensor_data // interpret received bytes as signed
```

---

## Warnings Are Not Optional

The instructor says this multiple times:

> *"Warnings related to casting are very dangerous.  
> Most of the time you will lose information.  
> Always resolve casting warnings."*

If the compiler says `"conversion changes value"` — stop and check. It is telling you data is being lost.

---

## Revision Cheatsheet

| Situation | What happens | Fix |
|-----------|-------------|-----|
| `int → float` | Safe, value preserved | Nothing needed |
| `float → int` | Decimal part cut off | Cast explicitly if intentional |
| `int → char` | Upper bytes truncated | Cast explicitly + check value fits |
| `int / int` | Fraction discarded | Cast one operand to `float` first |
| `int literal 0xFF` | Compiler treats as `int` by default | Normal, just be aware |

---

## Interview Q&A

**Q: What is type casting?**  
Converting a value from one data type to another. Can be implicit (compiler) or explicit (programmer).

**Q: What is truncation?**  
When a larger type is stored in a smaller type, the extra (higher) bytes are discarded. Example: `int 0x1FF` → `unsigned char 0xFF`.

**Q: Why does `int / int` give an integer result?**  
C's rule: when both operands are integers, the result is an integer. The fractional part is simply thrown away.

**Q: How do you fix integer division?**  
Cast at least one operand to `float` BEFORE the division: `(float)a / b`.

**Q: Why cast `(long long)n1 * n2` instead of `(long long)(n1 * n2)`?**  
Because `n1 * n2` happens as `int * int` first (overflow possible), then gets cast — too late. Casting `n1` first makes the entire multiplication happen in 8 bytes.

**Q: Should you ignore casting warnings?**  
Never. They indicate real potential data loss or incorrect arithmetic, especially critical in embedded systems.
