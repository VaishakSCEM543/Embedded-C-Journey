<div align="center">
  <h1>🚀 Embedded C Journey</h1>
  <p><i>Learning embedded C systematically — one concept at a time, committed consistently.</i></p>
  
  ![C](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
  ![GCC](https://img.shields.io/badge/Compiler-GCC-F34F29?style=for-the-badge&logo=gnu&logoColor=white)
  ![STM32](https://img.shields.io/badge/Target-STM32-03234B?style=for-the-badge&logo=stmicroelectronics&logoColor=white)
  ![ESP32](https://img.shields.io/badge/Target-ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white)
</div>

> **Note:** This repository contains my personal notes, code, and exercises while learning Embedded C. Inspired by Kiran Nayak's excellent Udemy course: [Microcontroller Embedded C Programming: Absolute Beginners](https://www.udemy.com/course/microcontroller-embedded-c-programming/).

---

## 📂 Repository Structure

| 📁 Section | 🎯 Topic Focus | 📄 Contents |
|:---------|:-------------|:----------|
| [**01 — Datatypes & Variables**](01-Datatypes-and-Variables/) | C data types, memory ranges, sizeof, scope | 10 files |
| [**02 — Pointers and Memory**](02-Pointers-and-Memory/) | Memory addresses, pointers, typecasting | 1 file |
| [**03 — Functions**](03-Functions/) | Function definitions, prototypes, return values, embedded use-cases | 3 files |

---

## 📚 Topics Covered

### 🔹 01 — Datatypes and Variables

| File | Core Concept |
|:-----|:-------------|
| 📄 [`datatypes.c`](01-Datatypes-and-Variables/datatypes.c) | All C data types — size, signed vs unsigned |
| 📄 [`storage_sizes.c`](01-Datatypes-and-Variables/storage_sizes.c) | `sizeof()`, ranges, overflow behaviour |
| 📄 [`char_ascii.c`](01-Datatypes-and-Variables/char_ascii.c) | `char`, ASCII encoding, typecasting |
| 📄 [`distance_calc.c`](01-Datatypes-and-Variables/distance_calc.c) | Variable definition exercise |
| 📄 [`char_range.c`](01-Datatypes-and-Variables/char_range.c) | signed/unsigned char range, 2's complement |
| 📄 [`short_range.c`](01-Datatypes-and-Variables/short_range.c) | `short int` range, 16-bit 2's complement |
| 📄 [`sizeof_demo.c`](01-Datatypes-and-Variables/sizeof_demo.c) | `sizeof()` across all types — GCC vs XC8 comparison |
| 📄 [`variables.c`](01-Datatypes-and-Variables/variables.c) | Variable definition, initialization, naming rules |
| 📄 [`scope.c`](01-Datatypes-and-Variables/scope.c) | Local vs global scope, shadowing, embedded memory impact |
| 📄 [`scope_block.c`](01-Datatypes-and-Variables/scope_block.c) | Block scope, variable lifetime, uninitialized variable danger |

### 🔹 02 — Pointers and Memory

| File | Core Concept |
|:-----|:-------------|
| 📝 [`lecture-01-memory-addresses.md`](02-Pointers-and-Memory/lecture-01-memory-addresses.md) | Memory addresses, `%p` format specifier, pointers, typecasting |

### 🔹 03 — Functions

| File | Core Concept |
|:-----|:-------------|
| 📝 [`lecture-01-functions.md`](03-Functions/lecture-01-functions.md) | Functions in C (Embedded Perspective), Prototypes, `main()` |
| 📄 [`function_add.c`](03-Functions/function_add.c) | Calling functions — raw numbers, variables, mixed arguments |
| 📝 [`lecture-03-return-values.md`](03-Functions/lecture-03-return-values.md) | Return values — `return`, return types, caller vs callee |
| 📄 [`function_return.c`](03-Functions/function_return.c) | Returning values — store, calculate, embedded sensor analogy |

---

## 🗺️ Learning Roadmap

- [x] **01 — Datatypes and Variables** *(Completed)*
- [x] **02 — Pointers and Memory** *(Completed)*
- [ ] 🔄 **03 — Functions** *(In Progress)*
- [ ] ⏳ **03 — Bitwise Operations**
- [ ] ⏳ **04 — Structures and Unions**
- [ ] ⏳ **05 — STM32 Bare Metal**
- [ ] ⏳ **06 — Communication Protocols (UART, SPI, I2C)**
- [ ] ⏳ **07 — RTOS**

---

## ⏳ Progress Log

| Date | 🎯 Topics Mastered |
|:---:|:---|
| **30 Jun** | Data types, storage sizes, char & ASCII, variable definition exercise |
| **04 Jul** | `char` range & 2's complement, `short int` range, `sizeof()` operator |
| **05 Jul** | Variable definition vs declaration, naming rules, scope (local vs global) |
| **06 Jul** | Block scope, variable lifetime, uninitialized variable behavior |
| **07 Jul** | **Functions** (definition, prototype, embedded perspective) & Memory Addresses (`%p`) |
| **08 Jul** | **Return values** — `return` keyword, return types, caller/callee, embedded sensor pattern |

---
*Consistency is the key to mastering Embedded Systems. 🛠️*
