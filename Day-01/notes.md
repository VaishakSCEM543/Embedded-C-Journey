# Day-01 — Data Types and Variables
**Date:** 2026-06-30
**Lecture:** Lecture-01 | Datatypes & Variables Section
**Status:** ✅ Complete

---

## 🧠 Concepts Learned

### 1. What is a Data Type?
A **data type** tells the compiler:
- What **kind of data** a variable will hold
- How much **memory** to allocate for it
- What **operations** are valid on it

> Without data types, the compiler doesn't know how many bytes to reserve in memory.

---

### 2. Why Are Data Types Needed?
- Memory in a computer/microcontroller is finite
- Different data needs different amounts of space
- The compiler needs to know the size to allocate RAM correctly

**Embedded Relevance:** On an STM32 with only 20KB of SRAM, every byte matters. Choosing the wrong type wastes memory.

---

### 3. Categories of Data Types in C

#### 🔢 Integer Data Types
Store whole numbers (no decimal point).

| Type | Size (typical) | Signed Range | Unsigned Range |
|------|---------------|-------------|----------------|
| `char` | 1 byte | -128 to 127 | 0 to 255 |
| `short` | 2 bytes | -32,768 to 32,767 | 0 to 65,535 |
| `int` | 2 or 4 bytes | depends on compiler | depends on compiler |
| `long` | 4 bytes | -2,147,483,648 to 2,147,483,647 | 0 to 4,294,967,295 |
| `long long` | 8 bytes | very large range | very large range |

#### 🔣 Float Data Types
Store numbers with decimal points.

| Type | Size | Precision |
|------|------|-----------|
| `float` | 4 bytes | ~6-7 decimal digits |
| `double` | 8 bytes | ~15-16 decimal digits |

#### 🔤 Character Data Type
- `char` stores a **single character**
- Internally stored as an **ASCII integer value**
- Example: `'A'` is stored as `65`

#### 📝 Strings
- A **string** is a collection of characters
- In C, strings are character arrays ending with `'\0'` (null terminator)
- Example: `"Hello"` = `{'H','e','l','l','o','\0'}`

---

### 4. Signed vs Unsigned

| | Signed | Unsigned |
|--|--------|----------|
| Can store | Negative & Positive | Only Positive (0 and above) |
| 1 bit used for | Sign (+ or -) | More range |
| Example | `signed char`: -128 to 127 | `unsigned char`: 0 to 255 |

**Rule of thumb:**
- Use `unsigned` when values are always ≥ 0 (e.g., sensor readings, counts, distances)
- Use `signed` when values can go negative (e.g., temperature below zero)

---

### 5. Integer Type Categories

```
char       → 1 byte  (smallest integer type)
short      → 2 bytes
int        → 2 or 4 bytes (compiler dependent)
long       → 4 bytes
long long  → 8 bytes (largest standard integer)
```

---

## 🔌 Embedded Relevance

| C Concept | Embedded Systems |
|-----------|-----------------|
| `char` (1 byte) | Reading 8-bit peripheral registers, GPIO states |
| `short` (2 bytes) | 12-bit ADC readings, timer values |
| `int` (4 bytes) | General computation, loop counters |
| `unsigned` types | Sensor values, addresses, bit masks |
| `float` | Sensor calibration, PID control |
| Strings | UART messages, display output |

**Key Insight:** In embedded C (STM32, ESP32), you'll often see:
```c
uint8_t   // = unsigned char  (8-bit)
uint16_t  // = unsigned short (16-bit)
uint32_t  // = unsigned int   (32-bit)
```
These are **fixed-width types** from `<stdint.h>` — preferred in embedded because sizes don't change across compilers.

---

## 🔑 Key Learnings
1. Data types define size + valid operations
2. Always choose the **smallest type** that fits your data
3. `char` can store both numbers and characters (ASCII)
4. Signed vs unsigned changes the usable range
5. In embedded, prefer `uint8_t`, `uint16_t` over `char`, `int`

---

## 📊 Streak
- Day 1 ✅
- No Zero Days: Active 🔥
