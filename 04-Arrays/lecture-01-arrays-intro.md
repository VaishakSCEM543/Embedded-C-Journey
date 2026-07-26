# Arrays in C - Lecture 1: Introduction to Arrays

> [!NOTE]
> **Difficulty:** 🟢 Beginner

## Learning Objectives

After completing this lecture, you should be able to:
* Understand why arrays are needed.
* Define an array in C using the correct syntax.
* Calculate the memory occupied by an array.
* Understand how arrays are stored in memory.
* Understand the relationship between an array name and its first element.
* Explain why contiguous memory storage makes arrays efficient.

---

## Why Do Arrays Exist?

Imagine you're writing a program to calculate the **average age of 100 students**. Without arrays, you would have to create 100 different variables:

```c
uint8_t age1;
uint8_t age2;
// ...
uint8_t age100;
```

**Problems with this approach:**
* Too many variables to manage.
* Difficult to read and modify.
* Not scalable.
* Easy to make mistakes.

As programmers, we need a way to store **multiple values of the same type** using **one name**. That solution is an **array**.

---

## What is an Array?

An **array** is a collection of elements of the **same data type** stored in **contiguous memory locations**.

```c
uint8_t studentsAge[100];
```
This creates storage for **100 unsigned 8-bit integers**. Instead of having 100 separate variable names, we now manage all values through **one array name**.

### Breaking Down the Declaration

| Part          | Meaning               |
| ------------- | --------------------- |
| `uint8_t`     | Type of every element |
| `studentsAge` | Name of the array     |
| `[100]`       | Number of elements    |

> [!IMPORTANT]
> **Why Must All Elements Have the Same Data Type?**
> An array stores identical types because the compiler needs to know how much memory to allocate, how far apart consecutive elements are, and how to compute the address of any element efficiently. If different-sized data types were mixed together, direct indexing would become impossible.

---

## Array Declaration Syntax

**General syntax:**
```c
data_type array_name[number_of_elements];
```

> [!WARNING]
> **Why Are Square Brackets Used?**
> Arrays in C always use square brackets. The following are incorrect and will cause compile errors:
> ```c
> int marks(50);    // ❌ Wrong
> int marks{50};    // ❌ Wrong
> int marks[50];    // ✅ Correct
> ```

---

## Memory Occupied by an Array

The total memory required by an array is:
**Total Memory = Number of Elements × Size of Each Element**

### Example 1
```c
uint8_t studentsAge[100];
```
Each `uint8_t` occupies **1 byte**. Therefore: `100 × 1 = 100 bytes`.

### Example 2
```c
uint32_t studentsAge[100];
```
Each `uint32_t` occupies **4 bytes**. Therefore: `100 × 4 = 400 bytes`.

### Using `sizeof()`
The `sizeof` operator returns the total size of the array in bytes.
```c
uint32_t studentsAge[100];
printf("%zu", sizeof(studentsAge)); // Output: 400
```

---

## How Are Arrays Stored in Memory?

This is one of the most important concepts in C. Arrays are stored in **contiguous memory locations**. This means that each element is stored immediately after the previous one with **no gaps**.

```text
Address      Value
1000         18
1001         20
1002         21
1003         19
```

> [!TIP]
> **Why Is Contiguous Memory Important?**
> If the first element starts at address **1000**, the compiler immediately knows the 2nd element is at 1001, the 3rd at 1002, etc. Because every element has the same size, the CPU can calculate any element's address directly. This makes array access extremely fast!

---

## The Array Name (Base Address)

The array name itself acts as a **base pointer** that holds the base address of the array. The base address is just the memory address of the very first element.

```c
uint8_t studentsAge[100];
printf("%p\n", (void *)studentsAge); // Output: e.g., 0x61ff10
```

```text
studentsAge
      │
      ▼
0x61ff10

Address      Value
0x61ff10     studentsAge[0]
0x61ff11     studentsAge[1]
0x61ff12     studentsAge[2]
```

Technically, the array name is **not a pointer variable itself**, but in most expressions, it automatically converts (or **decays**) into a pointer to its first element. So `studentsAge` behaves like `&studentsAge[0]`.

---

## Embedded Systems Perspective

Arrays are everywhere in microcontroller programming:

- **UART Receive Buffer:** `uint8_t rxBuffer[128];` (Stores incoming serial data).
- **ADC Samples:** `uint16_t adcValues[8];` (Stores analog readings from multiple pins).
- **Sensor Data:** `float temperatureHistory[60];` (Stores temperature values over time).

Without arrays, embedded software would be nearly impossible to write efficiently!

---

## Common Beginner Mistakes

1. **Using parentheses instead of brackets:** `int numbers(10);` ❌
2. **Mixing data types:** Assuming an array can hold an `int`, a `char`, and a `float` at the same time. Arrays can store only **one data type**.
3. **Misunderstanding the array name:** Thinking the array name is an integer variable, rather than a reference to the base address.

---

## Interview Questions

**Q1. What is an array?**
> An array is a collection of elements of the same data type stored in contiguous memory locations and accessed using a single name.

**Q2. Why are arrays stored contiguously?**
> Contiguous storage allows the CPU to calculate the address of any element directly via an offset, making memory access extremely fast.

**Q3. Is the array name a pointer?**
> Not exactly. An array name is not a pointer variable in memory, but in most expressions it "decays" and behaves exactly like a pointer to its first element.

---

## Practice Questions

### Conceptual
1. Why do we need arrays instead of creating many variables?
2. Why must all elements of an array have the same data type?
3. What is contiguous memory?
4. Why does `sizeof()` return the total byte size instead of the number of elements?

### Coding
1. Declare an array to store 20 floating-point values.
2. Declare an array of 50 `uint16_t` elements.
3. Write a program to print the total size of an array using `sizeof()`.
