# Arrays in C - Lecture 2: Array Initialization, Reading & Writing Elements

> [!NOTE]
> **Difficulty:** 🟢 Beginner

## Learning Objectives

After completing this lecture, you should be able to:
* Initialize arrays in different ways.
* Understand partial array initialization.
* Let the compiler automatically determine the array size.
* Understand Variable Length Arrays (VLAs).
* Read and modify array elements.
* Understand array indexing.
* Explain why array indexing starts from **0**.
* Understand the relationship between array indexing and pointer arithmetic.
* Traverse an array using loops.

---

## Why Do We Need to Read and Write Array Elements?

Creating an array is only the first step. Once an array is created, we need to store values in it, read values from it, modify existing values, and process all elements efficiently.

For example in embedded systems:
* Store sensor readings.
* Update ADC samples.
* Receive UART data.
* Process image pixels.
* Store IMU measurements.

Without reading and writing array elements, arrays would simply be blocks of unused memory.

---

## Array Initialization

### Method 1: Initialize During Declaration

```c
#include <stdint.h>

uint8_t someData[10] = { 0xFF, 0xFF, 0xFF };
```

**What happens here?**
The array has **10 elements**, but only the **first 3** are initialized. Memory becomes:

| Index | Value |
| ----: | ----: |
|     0 |  0xFF |
|     1 |  0xFF |
|     2 |  0xFF |
|     3 |  0x00 |
|     4 |  0x00 |
|     5 |  0x00 |
|     6 |  0x00 |
|     7 |  0x00 |
|     8 |  0x00 |
|     9 |  0x00 |

> [!IMPORTANT]
> **The Zero-Fill Rule**
> If fewer values are provided than the array size, **all remaining elements are automatically initialized to zero.** This behavior is guaranteed by the C language.

---

## Compiler Can Determine Array Size

Instead of writing:
```c
int numbers[3] = {10,20,30};
```
you can simply write:
```c
int numbers[] = {10,20,30};
```
The compiler counts the initializer values. Since there are **3 values**, it creates an array of **3 elements**. This is perfectly valid.

> [!WARNING]
> **When Is This Not Allowed?**
> The following is **illegal**:
> ```c
> int numbers[];
> ```
> Why? Because no size is specified, and no initializer is provided. The compiler has no information about how much memory should be allocated. Therefore it produces an error.

---

## Variable Length Arrays (VLA)

Normally we write:
```c
int numbers[10];
```
Here, `10` is a constant. But C99 introduced **Variable Length Arrays**.

Example:
```c
int len = 10;
int numbers[len];
```
Now the array size depends on a variable. This is called a **Variable Length Array (VLA).**

**Why Were VLAs Introduced?**
Sometimes we don't know the required size until the program is running.
*Example:* User enters `75` for number of students. Then `int marks[75];` can be created. Without VLAs, this flexibility wasn't available in standard C.

> [!CAUTION]
> **Important Note on Standards & Embedded Systems**
> VLAs are supported from **C99** onwards, but they are **not supported by C90 (ANSI C)**. 
> Also note that many embedded projects disable VLAs because they use stack memory, whose size is often extremely limited on microcontrollers.

---

## Reading and Writing Array Elements

Suppose `uint8_t someData[10];` exists. How do we modify an element? The easiest method is array indexing.

Example:
```c
someData[1] = 0x09;
```
This changes the **second element**.

**Why Second Element?**
Because array indexing starts from **0**.

| Index | Element |
| ----: | ------- |
|     0 | First   |
|     1 | Second  |
|     2 | Third   |
|     3 | Fourth  |

This is one of the most important rules in C.

---

## Why Does Array Indexing Start from 0?

Many beginners memorize this. Instead, understand **why**.

Suppose `uint8_t someData[10];`. Assume the first element begins at address `1000`.

```text
Address      Element
1000         someData[0]
1001         someData[1]
1002         someData[2]
1003         someData[3]
```

The address of an element is calculated as:
**`Base Address + Index × Size of Element`**

For a `uint8_t` array (Size = 1 byte):
**`Address = Base + Index`**

Therefore:
* For the first element: `Base + 0`
* Second element: `Base + 1`
* Third element: `Base + 2`

That is exactly why indexing starts at **0**. It isn't an arbitrary language rule—it naturally follows from how addresses are calculated.

---

## Pointer Arithmetic Behind the Scenes

```c
*(someData + 1) = 0x09;
```
This means:
1. Start at the beginning of the array.
2. Move one element forward.
3. Dereference the address.
4. Store `0x09`.

> [!TIP]
> **Array Indexing Is Just a Shortcut**
> The following statements are perfectly equivalent:
> ```c
> *(someData + 1) = 0x09;
> someData[1] = 0x09;
> ```
> Similarly, `*(someData + i)` is equivalent to `someData[i]`. The square-bracket notation is simply syntax sugar that is easier for humans to read.

---

## Traversing and Modifying an Array Using a Loop

Instead of writing:
```c
printf("%X", someData[0]);
printf("%X", someData[1]);
// ...
```
We use a loop. This prints every element:
```c
for(uint32_t i = 0; i < 10; i++) {
    printf("%X\t", someData[i]);
}
```

**Modifying Every Element:**
```c
for(uint32_t i = 0; i < 10; i++) {
    someData[i] = 0x33;
}
```
Result:
* **Before:** `FF FF FF FF FF FF FF FF FF FF`
* **After:** `33 33 33 33 33 33 33 33 33 33`

Instead of modifying one element, the loop updates all elements. This technique is used constantly in embedded programming.

---

## Embedded Systems Perspective

Arrays are used almost everywhere in firmware.

* **UART Receive Buffer:** `uint8_t rxBuffer[128];` (Each received byte is stored in the next array element).
* **ADC Readings:** `uint16_t adcValues[8];` (Each ADC channel stores its reading in one element).
* **IMU Sensor Samples:** `int16_t accelX[100];` (Stores 100 acceleration measurements).
* **LED Control:** `uint8_t ledState[16];` (Each element stores the ON/OFF state of one LED).
* **Audio Buffer:** `int16_t audioSamples[1024];` (Stores microphone samples before processing).

---

## Common Beginner Mistakes

**Mistake 1: Thinking the first element is Index 1**
Correct: First element → Index 0.

**Mistake 2: Accessing outside the array**
```c
int numbers[5];
numbers[10] = 50;
```
This is **undefined behavior** and will corrupt your memory.

**Mistake 3: Confusing array size with the highest index**
For `int numbers[10];`, the highest valid index is `9`, not `10`.

**Mistake 4: Thinking array indexing and pointer arithmetic are unrelated**
Actually, `array[i]` is simply another way of writing `*(array + i)`.

---

## Interview Questions

**Q1. Why does array indexing start from 0?**
> Because the address of an element is calculated using: `Base Address + Index × Size of Element`. The first element is at an offset of **0** from the base address.

**Q2. What happens if only some elements are initialized?**
> The remaining elements are automatically initialized to zero.

**Q3. Can the compiler determine the size of an array automatically?**
> Yes. If an initializer list is provided (`int numbers[] = {1,2,3};`), the compiler counts the initializer values.

**Q4. What is a Variable Length Array?**
> A Variable Length Array (VLA) is an array whose size is determined at runtime using a variable. VLAs were introduced in the C99 standard.

**Q5. Are `array[i]` and `*(array+i)` different?**
> No. They access the same element. Array indexing is simply syntactic sugar for pointer arithmetic.

---

## Practice Questions

### Conceptual
1. Why are uninitialized elements automatically set to zero during partial initialization?
2. Why does C use zero-based indexing instead of one-based indexing?
3. Explain why `array[i]` and `*(array + i)` are equivalent.
4. What is the difference between a fixed-size array and a Variable Length Array?
5. Why are loops preferred for processing arrays?

### Coding
1. Declare an array of 20 integers and initialize all elements to zero.
2. Write a program to print all elements of an array using a `for` loop.
3. Write a program to change every element of an array to `0x55`.
4. Create a VLA whose size is entered by the user.
5. Print an array twice: once using `array[i]` and once using pointer arithmetic.
