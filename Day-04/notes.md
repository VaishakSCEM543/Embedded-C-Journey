# Day-04 — Variable Definition Exercise
**Date:** 2026-06-30
**Lecture:** Lecture-04 | Datatypes & Variables Section
**Status:** ✅ Complete

---

## 📋 Problem Statement
> Write a C program to calculate and print the total distance from point A to point C.
> - Distance from A to B = 160 km
> - Distance from B to C = 40 km

---

## 🧠 Concepts Practiced

### 1. Variable Definition
Defining a variable means:
- Giving it a **name**
- Giving it a **data type**
- Giving it a **value**

```c
unsigned char a_b = 160;  // name: a_b | type: unsigned char | value: 160
unsigned char b_c = 40;   // name: b_c | type: unsigned char | value: 40
```

### 2. `unsigned char` Data Type
| Property | Value |
|----------|-------|
| Size | 1 byte (8 bits) |
| Range | 0 to 255 |
| Signed? | No |

Used here because distances (160, 40) fit within 0–255.

### 3. Arithmetic in `printf`
```c
printf("Total distance = %d", a_b + b_c);
```
- Expression `a_b + b_c` is computed at runtime
- `%d` — format specifier for integer output

---

## 💻 Code Written

```c
#include <stdio.h>

int main()
{
    unsigned char a_b = 160;
    unsigned char b_c = 40;
    printf("The total distance from point A to point C is %d", a_b + b_c);

    return 0;
}
```

---

## ✅ Output
```
The total distance from point A to point C is 200
```

---

## ⚠️ Mistakes / Watch Out

| Mistake | Correct Approach |
|--------|-----------------|
| Using `int` for small values | Use `unsigned char` if value fits 0–255 (saves RAM) |
| Forgetting `%d` for integer print | Always match format specifier to data type |
| Overflow risk | `unsigned char` max is 255. If sum > 255, it wraps around (overflow) |

**Overflow Example (important!):**
```c
unsigned char x = 200;
unsigned char y = 100;
// x + y = 300 → OVERFLOW → stored as 300 - 256 = 44 ❌
```

---

## 🔑 Key Learnings

1. Always choose the **smallest data type** that fits your value
2. `unsigned char` = 1 byte = values 0 to 255
3. `printf` can compute expressions inline: `a + b`
4. Format specifiers must match data types

---

## 🔌 Embedded Relevance

This is NOT just a math exercise. In embedded systems:

| C Concept | Embedded Use |
|-----------|-------------|
| `unsigned char` (1 byte) | Storing **sensor readings** (e.g., temperature 0–255°C), **register values**, **GPIO states** |
| Variable definition | Every **peripheral register** is a variable in memory (e.g., `GPIOA->ODR = 0x01`) |
| Arithmetic | **ADC conversions**, **PWM duty cycle calculations**, **checksum computation** |
| `printf` | Replaced by **UART transmit** (`HAL_UART_Transmit()`) in real embedded systems |

### Real Embedded Example:
```c
// Microcontroller: Reading 2 ADC sensor values and summing them
unsigned char sensor_A = 160;  // ADC raw value from sensor A
unsigned char sensor_B = 40;   // ADC raw value from sensor B
unsigned char total = sensor_A + sensor_B;  // combined reading

// Send via UART instead of printf
HAL_UART_Transmit(&huart1, &total, 1, HAL_MAX_DELAY);
```

**Memory:** Both variables live in **RAM (SRAM)** on the microcontroller.
On STM32F103: SRAM = 20KB. Every byte matters.

---

## 📊 Streak
- Day 4 ✅
- No Zero Days: Active 🔥
