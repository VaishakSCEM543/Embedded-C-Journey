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
| [**01 — Datatypes & Variables**](01-Datatypes-and-Variables/) | C data types, memory ranges, sizeof, scope | 12 files |
| [**02 — Pointers and Memory**](02-Pointers-and-Memory/) | Memory addresses, pointers, dereferencing, pointer types, arithmetic | 11 files |
| [**03 — Functions**](03-Functions/) | Function definitions, prototypes, return values, multi-file projects, typecasting | 8 files |

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
| 📝 [`lecture-06-scope.md`](01-Datatypes-and-Variables/lecture-06-scope.md) | Full scope notes — local/global, shadowing, block scope, embedded RAM impact |
| 📝 [`lecture-07-typecasting-practice.md`](01-Datatypes-and-Variables/lecture-07-typecasting-practice.md) | Typecasting practice notes — implicit vs explicit, overflow, truncation, multi-file exercise |

### 🔹 02 — Pointers and Memory

| File | Core Concept |
|:-----|:-------------|
| 📝 [`lecture-01-memory-addresses.md`](02-Pointers-and-Memory/lecture-01-memory-addresses.md) | Memory addresses, `%p` format specifier, stack layout, pointer typecasting |
| 📄 [`address.c`](02-Pointers-and-Memory/address.c) | `&` operator, `%p`, stack layout — consecutive chars differ by 1 byte |
| 📝 [`lecture-02-pointer-concept.md`](02-Pointers-and-Memory/lecture-02-pointer-concept.md) | What is a pointer — address vs data, 4 pointer operations, embedded register access, pointer size |
| 📄 [`pointer_demo.c`](02-Pointers-and-Memory/pointer_demo.c) | All 4 pointer ops in code — read, write, increment, decrement + embedded GPIO simulation |
| 📝 [`lecture-03-dereferencing.md`](02-Pointers-and-Memory/lecture-03-dereferencing.md) | Dereferencing (`*ptr`), pointer arithmetic, safe reset pattern, embedded GPIO register write |
| 📄 [`deref_exercise.c`](02-Pointers-and-Memory/deref_exercise.c) | Lecture 16 exercise — `char` pointer, read via `*ptr`, write via `*ptr = 65`, verified output |
| 📄 [`pointer_exercise_lec17.c`](02-Pointers-and-Memory/pointer_exercise_lec17.c) | Lecture 17 exercise — 7-step pointer exercise, `char *pAddress`, read and write via deref, output noted |
| 📝 [`lecture-04-pointer-types.md`](02-Pointers-and-Memory/lecture-04-pointer-types.md) | Pointer type effect on read size — `char*`=1B, `short*`=2B, `int*`=4B, `long long*`=8B, typecasting, syntax styles |
| 📄 [`pointer_types_demo.c`](02-Pointers-and-Memory/pointer_types_demo.c) | Lecture 18 demo — same address, 4 pointer types, each fetches different byte count, output verified |
| 📝 [`lecture-05-pointer-arithmetic.md`](02-Pointers-and-Memory/lecture-05-pointer-arithmetic.md) | Pointer arithmetic — `+1` moves by `sizeof(type)`, verified for char/short/int, embedded register stepping |
| 📄 [`pointer_arithmetic_demo.c`](02-Pointers-and-Memory/pointer_arithmetic_demo.c) | Lecture 19 demo — char*/short*/int* arithmetic, address offset confirmed in output |

### 🔹 03 — Functions

| File | Core Concept |
|:-----|:-------------|
| 📄 [`function_add.c`](03-Functions/function_add.c) | Calling functions — raw numbers, variables, mixed arguments |
| 📝 [`lecture-03-return-values.md`](03-Functions/lecture-03-return-values.md) | Return values — `return`, return types, caller vs callee |
| 📄 [`function_return.c`](03-Functions/function_return.c) | Returning values — store, calculate, embedded sensor analogy |
| 📝 [`lecture-04-multifile-header.md`](03-Functions/lecture-04-multifile-header.md) | Multi-file projects, header files, include guards, explicit typecasting |
| 📁 [`math-project/`](03-Functions/math-project/) | `math.h` + `math.c` + `main.c` — full multi-file arithmetic project |
| 📝 [`lecture-05-typecasting.md`](03-Functions/lecture-05-typecasting.md) | Implicit vs explicit casting, data truncation, warnings in embedded |
| 📁 [`typecast-exercise/`](03-Functions/typecast-exercise/) | Exercise: `add`, `sub`, `mul`, `divf` — all casting rules applied |
| 📁 [`lecture-07-multifile-typecast-exercise/`](03-Functions/lecture-07-multifile-typecast-exercise/) | Revised multi-file exercise: `main.c` + `math.c` + `math.h` with full inline cast comments |

---

## 🗺️ Learning Roadmap

- [x] **01 — Datatypes and Variables** *(Completed)*
- [x] **03 — Functions** *(Completed — definitions, return values, multi-file, typecasting)*
- → **02 — Pointers and Memory** *(In Progress — foundation done, more lectures ahead)*
- [ ] ⏳ **04 — Bitwise Operations**
- [ ] ⏳ **05 — Structures and Unions**
- [ ] ⏳ **06 — STM32 Bare Metal**
- [ ] ⏳ **07 — Communication Protocols (UART, SPI, I2C)**
- [ ] ⏳ **08 — RTOS**

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
| **10 Jul** | **Multi-file projects** — `math.h`/`math.c`/`main.c`, include guards, explicit typecasting (`long long`, `float`) |
| **11 Jul** | **Typecasting (Lec 51)** — implicit vs explicit casting, data truncation, casting warnings in embedded; typecasting exercise project |
| **12 Jul** | **Review & polish** — scope (local/global, shadowing, block scope, uninitialized trap); memory addresses (`&`, `%p`, stack layout); embedded RAM impact of globals |
| **13 Jul** | **Typecasting deep-dive** — implicit vs explicit, overflow in `mul`, truncation in `divf`, multi-file exercise (`main.c` + `math.c` + `math.h`), casting promotion rules |
| **14 Jul** | **Pointers (Concept)** — pointer = memory address (not data), RAM as apartment model, 4 pointer ops (read/write/inc/dec), pointer size vs architecture, embedded GPIO register access via pointer |
| **15 Jul** | **Dereferencing & Pointer Arithmetic** — `*ptr` vs `ptr`, writing through pointer (`*ptr = 365`), pointer arithmetic steps by `sizeof(type)`, unsafe memory after `ptr+1`, safe reset pattern (`ptr = &a`) |
| **17 Jul** | **Dereferencing Exercise (Lec 16)** — `char *ptr`, read op (`data = *ptr`), write op (`*ptr = 65`), verified `var` changed without touching it by name, output noted in comments |
| **19 Jul** | **Pointer Exercise (Lec 17)** — 7-step exercise, `char data`, `char *pAddress`, read and write via dereference, confirmed `pAddress == &data`, `data` changed 100→65 via pointer |
| **20 Jul** | **Pointer Types Effect (Lec 18)** — `char*` reads 1B, `short*` 2B, `int*` 4B, `long long*` 8B from same address; typecasting LHS/RHS types, two pointer declaration styles |
| **21 Jul** | **Pointer Arithmetic (Lec 19)** — `ptr + 1` moves by `sizeof(type)`: char*=+1, short*=+2, int*=+4; verified with hex output; embedded register stepping use case |

---
*Consistency is the key to mastering Embedded Systems. 🛠️*
