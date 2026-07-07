# Datatypes and Variables

This module covers the absolute basics of memory, variables, and data types in C, viewed through the lens of Embedded Systems.

## 📁 Source Code Index

Click any file to view the actual C implementation we wrote during this module:

| File | Concept Covered |
| :--- | :--- |
| [`datatypes.c`](datatypes.c) | Basic C data types, sizes, signed vs unsigned integers. |
| [`storage_sizes.c`](storage_sizes.c) | Using the `sizeof()` operator, variable ranges, and understanding integer overflow. |
| [`char_ascii.c`](char_ascii.c) | The `char` data type, ASCII encoding, and typecasting characters to integers. |
| [`distance_calc.c`](distance_calc.c) | A practical exercise on variable definition and math. |
| [`char_range.c`](char_range.c) | Signed vs unsigned `char` memory ranges and 2's complement representation. |
| [`short_range.c`](short_range.c) | `short int` memory range and 16-bit 2's complement representation. |
| [`sizeof_demo.c`](sizeof_demo.c) | Exploring `sizeof()` across all types and comparing GCC vs XC8 compiler outputs. |
| [`variables.c`](variables.c) | Variable definitions, initializations, and C naming rules. |
| [`scope.c`](scope.c) | Local vs global variable scope, variable shadowing, and memory impact. |
| [`scope_block.c`](scope_block.c) | Block scope (`{}`), variable lifetime, and the dangers of uninitialized variables. |

---

## 🧠 Key Concepts & Takeaways

### 1. Embedded Size Matters
In standard desktop C (like GCC on a 64-bit PC), an `int` is 4 bytes. However, on an 8-bit microcontroller (like AVR ATmega328 used in Arduino), an `int` is often just **2 bytes**. Always rely on `stdint.h` (`uint8_t`, `int32_t`) in real embedded code to guarantee sizes.

### 2. Variable Scope
- **Global Variables:** Declared outside of functions. They are allocated in RAM (data/bss sections) for the entire lifetime of the program. Use them sparingly in embedded systems to save RAM.
- **Local Variables:** Declared inside functions or blocks `{}`. They are allocated on the **Stack** and destroyed when the function/block ends.

### 3. The Uninitialized Variable Trap
If you declare a local variable but do not initialize it (e.g., `int x;`), it will contain whatever random garbage data was previously left at that memory address on the stack. **Always initialize your local variables.**

### 4. Shadowing
If a local variable has the same name as a global variable, the local variable "shadows" (hides) the global variable within its scope. The compiler will prioritize the local variable.
