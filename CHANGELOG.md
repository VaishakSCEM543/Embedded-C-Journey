# Changelog

All notable changes to this repository are documented here.
Follows [Keep a Changelog](https://keepachangelog.com/) conventions.

---

## [Unreleased]

---

## [0.8.0] — 2026-08-19

### Added
- **Module 08 — Operators** (`08-Operators/`)
  - Lec 1: Unary / Binary / Ternary operator types
  - Arithmetic operators (`+`, `-`, `*`, `/`, `%`) with integer division trap
  - Operator precedence (`*` before `+`) and associativity (left-to-right for `*`/`/`)
  - Parentheses as explicit grouping override
  - Key insight: precedence ≠ evaluation order (important for `++`/`--`, `&&`/`||`)
  - `operators_demo.c` — live demo of all concepts

### Fixed
- **CI Workflow** — Added missing build steps for Modules 06, 07, and 08
  - Module 06 multi-file static demo now compiled correctly (`main.c` + `file1.c`)
  - All 8 modules now verified on every push to `main`

---

## [0.7.0] — 2026-08-11

### Added
- **Module 07 — Bitwise Operators** (`07-Bitwise-Operators/`)
  - Complete notes covering Lectures 104–110: AND, OR, XOR, NOT operators
  - TEST / SET / CLEAR / TOGGLE patterns with full mask derivation
  - Six core bitwise identities (`X & 0 = 0`, `X | 1 = 1`, `X ^ 1 = ~X`, etc.)
  - GPIO register programming patterns (`|=`, `&=~`, `^=`)
  - Output-based and embedded interview questions
  - `bitwise_demo.c` — live demo of all four operations with binary print helper

---

## [0.6.2] — 2026-08-13

### Added
- **Storage Classes Lec 4 — `extern`** (`06-Storage-Classes/lecture-04-extern.md`)
  - extern vs static contrast (restrict vs extend)
  - extern implied for functions, required for variables
  - Definition vs declaration final summary
  - Multi-file project complete example
- **ASCII Codes Supplement** (`01-Datatypes-and-Variables/supplement-ascii-codes.md`)
  - Character literals vs raw ASCII codes
  - `%c` vs `%d` format specifier distinction
  - Key ASCII values table (A=65, a=97, '0'=48, `\0`=0)
  - Embedded UART byte-to-character connection

---

## [0.6.1] — 2026-08-09

### Added
- **Storage Classes Lec 3 — `static` Functions** (`06-Storage-Classes/lecture-03-static-functions.md`)
  - Static function = file-private function (internal linkage)
  - Embedded driver encapsulation pattern
  - Complete two-meaning mental model for `static`

---

## [0.6.0] — 2026-08-09

### Added
- **Storage Classes Lec 2 — `static` File Scope** (`06-Storage-Classes/lecture-02-static-file-scope.md`)
  - Internal vs external linkage
  - `extern` keyword introduced
  - `static` global variable = file-private
  - Multi-file demo: `static_file_scope_main.c` + `static_file_scope_file1.c`

---

## [0.5.0] — 2026-08-08

### Added
- **Module 06 — Storage Classes** (`06-Storage-Classes/`)
  - Lec 1: `static` local variable — scope, visibility, lifetime
  - Three properties explained: scope / visibility / lifetime
  - Local vs global vs static comparison table
  - Embedded use cases: ISR debounce counters, state machines
  - `static_demo.c` — `myFun1()` called 4 times, count persists

---

## [0.5.3] — 2026-08-05

### Added
- **Strings Lec 3 Part 3 — Flash-to-RAM Copy** (`05-Strings/lecture-03-part3-flash-to-ram.md`)
  - Two copies of string: Flash (permanent) + Stack/RAM (temporary)
  - Compile time vs startup time vs runtime distinction
  - Global vs local variable initialization difference
  - STM32 memory map (`0x0800xxxx` Flash, `0x2000xxxx` RAM)

---

## [0.5.2] — 2026-08-04 (earlier)

### Added
- **Strings Lec 3 Part 1 & 2** — Array addresses, stack memory diagrams

---

## [0.5.1] — 2026-08-03

### Added
- **CI/CD Infrastructure**
  - Root `Makefile` — `make all` builds all 5+ modules
  - `.github/workflows/build.yml` — GitHub Actions auto-compiles all C files on push
  - Build status badge in README header

---

## [0.4.0] — 2026-07-29 to 2026-07-30

### Added
- **Module 05 — Strings** (`05-Strings/`)
  - Lec 1: Character arrays, null terminator, `sizeof` vs `strlen`
  - Lec 2: String literals vs char arrays, RAM vs ROM, `const char *`
  - Custom implementations of `strlen`, `strcpy`, `strcmp`
  - `string_literals_demo.c` — char array modification vs read-only pointer

---

## [0.3.0] — 2026-07-24 to 2026-07-29

### Added
- **Module 04 — Arrays** (`04-Arrays/`)
  - Array basics, initialization, partial init zero-filling
  - C99 VLA, array decay, `arr[i] == *(arr + i)`
  - Passing arrays to functions, `const` pointer safety, subarray slicing
  - Array exercises: sum, max, reverse print, swap algorithms
  - Module-level `Makefile`

---

## [0.2.0] — 2026-07-20 to 2026-07-21

### Added
- **Module 02 — Pointers and Memory** (`02-Pointers-and-Memory/`)
  - Pointer basics: address-of `&`, dereference `*`
  - Pointer types and their effect on byte access
  - Pointer arithmetic: `ptr + 1` moves by `sizeof(type)`
  - Demos aligned with instructor's style (hex output, `uint8_t`)

---

## [0.1.0] — 2026-06-30 to 2026-07-19

### Added
- **Module 01 — Datatypes and Variables** (`01-Datatypes-and-Variables/`)
  - C data types, storage sizes, `sizeof`, `char` & ASCII
  - Signed vs unsigned ranges, overflow behavior
  - Variable scope, declaration vs definition

- **Module 03 — Functions** (`03-Functions/`)
  - Function definitions, prototypes, return values
  - Multi-file projects: math-project, typecast-exercise
  - Typecasting between integer types

- Repository structure, `.gitignore`, initial `README.md`
