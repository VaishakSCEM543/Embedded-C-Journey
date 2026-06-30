# Day-02 — Storage Sizes and Ranges
**Date:** 2026-06-30
**Lecture:** Lecture-02 | Datatypes & Variables Section
**Status:** ✅ Complete

---

## 🧠 Concepts Learned

### 1. Storage Sizes of Integer Data Types

Every data type occupies a fixed number of **bytes** in memory. The compiler decides how many bytes to give each type.

```
1 byte = 8 bits
```

| Type | Size | Bits |
|------|------|------|
| `char` | 1 byte | 8 bits |
| `short` | 2 bytes | 16 bits |
| `int` | 2 or 4 bytes | 16 or 32 bits |
| `long` | 4 bytes | 32 bits |
| `long long` | 8 bytes | 64 bits |

---

### 2. Ranges — How They Are Calculated

For **N bits**:
- **Signed range:** `-2^(N-1)` to `2^(N-1) - 1`
- **Unsigned range:** `0` to `2^N - 1`

#### `char` (1 byte = 8 bits):
| Type | Calculation | Range |
|------|-------------|-------|
| `signed char` | -2^7 to 2^7-1 | **-128 to 127** |
| `unsigned char` | 0 to 2^8-1 | **0 to 255** |

#### `short` (2 bytes = 16 bits):
| Type | Range |
|------|-------|
| `signed short` | **-32,768 to 32,767** |
| `unsigned short` | **0 to 65,535** |

#### `int` (4 bytes = 32 bits on GCC):
| Type | Range |
|------|-------|
| `signed int` | **-2,147,483,648 to 2,147,483,647** |
| `unsigned int` | **0 to 4,294,967,295** |

#### `long long` (8 bytes = 64 bits):
| Type | Range |
|------|-------|
| `signed long long` | **-9.2 × 10^18 to 9.2 × 10^18** |
| `unsigned long long` | **0 to 1.8 × 10^19** |

---

### 3. Compiler-Dependent Sizes

**This is critical for embedded!** The size of `int` and `long` changes across compilers:

| Compiler | `int` size | `long` size | Used for |
|----------|-----------|------------|---------|
| **GCC** (your PC, Linux) | 4 bytes | 4 bytes | Desktop, Linux embedded |
| **XC8** (Microchip PIC) | 2 bytes | 4 bytes | PIC microcontrollers |
| **ARMCC** (Keil, STM32) | 4 bytes | 4 bytes | ARM Cortex-M (STM32, etc.) |

> ⚠️ **This is why you must NEVER assume `int` = 4 bytes in embedded code.** Use `uint32_t` instead.

---

### 4. C Standard Minimum Guarantees

The C standard only guarantees **minimum sizes**, not exact sizes:

| Type | Minimum size guaranteed |
|------|------------------------|
| `char` | ≥ 1 byte |
| `short` | ≥ 2 bytes |
| `int` | ≥ 2 bytes |
| `long` | ≥ 4 bytes |
| `long long` | ≥ 8 bytes |

The compiler can give more, but never less.

---

### 5. `sizeof()` Operator

`sizeof()` returns the **actual size in bytes** that your compiler assigns to a type.

```c
printf("%zu", sizeof(int));    // prints 4 on GCC (PC)
printf("%zu", sizeof(char));   // prints 1 always
```

Use `sizeof()` to write **portable, compiler-safe code**.

---

## 🔌 Embedded Relevance

### Why Sizes Matter in Embedded:

```
STM32F103C8T6:
  Flash (program memory) : 64 KB
  SRAM (RAM)             : 20 KB

Using int (4 bytes) where char (1 byte) is enough
→ wastes 3 bytes per variable
→ on a 20KB system, this adds up fast
```

### Solution — Fixed-Width Types (`<stdint.h>`):

| Fixed type | Guaranteed size | Replaces |
|------------|----------------|---------|
| `uint8_t` | exactly 1 byte | `unsigned char` |
| `int8_t` | exactly 1 byte | `signed char` |
| `uint16_t` | exactly 2 bytes | `unsigned short` |
| `int16_t` | exactly 2 bytes | `signed short` |
| `uint32_t` | exactly 4 bytes | `unsigned int` (on 32-bit) |
| `int32_t` | exactly 4 bytes | `signed int` (on 32-bit) |

These types have the **same size on every compiler** — GCC, ARMCC, XC8, all of them.

---

## 🔑 Key Learnings
1. `sizeof()` tells you the real size assigned by your compiler
2. `int` and `long` sizes are **not fixed** — they change per compiler
3. C standard only guarantees **minimums**
4. Signed range formula: `-2^(N-1)` to `2^(N-1) - 1`
5. In embedded, always use `uint8_t`, `uint16_t`, `uint32_t` from `<stdint.h>`

---

## 📊 Streak
- Day 2 ✅
- No Zero Days: Active 🔥
