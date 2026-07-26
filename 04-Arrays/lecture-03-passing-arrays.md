# Arrays in C - Lecture 3: Passing Arrays to Functions

> [!NOTE]
> **Difficulty:** 🟢 Beginner

## Learning Objectives

After completing this lecture, you should be able to:
* Pass an array to a function.
* Understand what is actually passed to the function (Array Decay).
* Explain why the array size must also be passed.
* Use `const` correctly when passing arrays.
* Access array elements inside a function.
* Pass a pointer to any element of an array.
* Understand array slicing using pointers.
* Recognize common mistakes when working with arrays and functions.

---

## Why Do We Pass Arrays to Functions?

Imagine you have an array containing sensor readings:
```c
uint8_t sensorData[100];
```
Suppose you want to:
* Display the readings
* Find the maximum value
* Calculate the average
* Filter the data
* Sort the values

Should all this code be written inside `main()`? **No.**

Instead, we divide the program into **functions**, each responsible for one task.
This makes the program:
* Easier to read
* Easier to debug
* Easier to reuse
* Easier to maintain

---

## The Big Question

How do we pass an array to a function? Consider:
```c
uint8_t someData[10];
```
Do we pass all 10 elements one by one? **No.**

> [!IMPORTANT]
> **What Is Actually Passed?**
> When passing an array to a function, the function **does not receive a copy of the array**. It only receives the **address of the first element**. This automatic conversion of an array name to a pointer is known as **Array Decay**.

---

## Function Prototype

Because only an address is passed, the receiving parameter must be a pointer.

```c
void arrayDisplay(uint8_t *pArray) {
    // ...
}
```
Why? Because `pArray` stores an address. The type of that address is "Pointer to `uint8_t`".

> [!WARNING]
> **Problem: How Many Elements Are There?**
> If a function receives `uint8_t *pArray`, can it determine whether the array contains 5, 10, or 100 elements?
> **No.** It only knows the starting address. It has **no information about the array length**.

### Solution: Pass the Size Separately

```c
void arrayDisplay(uint8_t *pArray, uint32_t nItems) {
    // ...
}
```
Call it like:
```c
arrayDisplay(someData, 10);
```
Now the function knows where the array starts and exactly how many elements exist.

---

## Calculating Number of Elements

Instead of hardcoding `10`, we usually calculate the size.

**Formula:**
`Number of Elements = Total Array Size ÷ Size of One Element`

Example:
```c
uint32_t nItems = sizeof(someData) / sizeof(uint8_t);
```

> [!CAUTION]
> **Why Not Use `sizeof(pArray)` Inside the Function?**
> Many beginners think this works:
> ```c
> void display(uint8_t *pArray) {
>     printf("%d", sizeof(pArray)); // ❌ WRONG!
> }
> ```
> `pArray` is a **pointer**, not an array. `sizeof(pArray)` returns the **size of the pointer** (typically 4 bytes on 32-bit or 8 bytes on 64-bit systems), **not** the number of array elements. This is why the size must be passed as a separate argument.

---

## Displaying the Array

You can display the array inside the function using a loop:

```c
for(uint32_t i = 0; i < nItems; i++) {
    printf("%X\t", pArray[i]);
}
```

> [!TIP]
> **Array Indexing Shorthand**
> Writing `*(pArray + i)` and `pArray[i]` are identical. The compiler generates equivalent behavior, but `pArray[i]` is much easier to read!

---

## Why Use `const`?

If a function is only supposed to **read** the array (like a display function), it should **not modify** the data.

```c
void display(const uint8_t *pArray, uint32_t nItems)
```
Using `const` means: *"I promise not to modify the array."*
Now this becomes illegal and the compiler will throw an error:
```c
pArray[0] = 100; // ❌ Error!
```
Using `const` makes the code safer and documents your intent clearly.

---

## Passing Part of an Array (Subarray / Slicing)

You don't always have to pass the entire array.

Example:
```c
arrayDisplay(someData + 2, nItems - 2);
```
What is passed? The **address of element 2**.
Only the remaining portion of the array is displayed. This technique is often called **passing a subarray** (or a slice of the original array).

Another way to write this:
```c
arrayDisplay(&someData[2], nItems - 2);
```
These expressions are perfectly equivalent.

---

## Embedded Systems Perspective

Passing arrays by pointer is extremely common in embedded firmware:

* **UART Driver:** `UART_Send(txBuffer, length);`
* **SPI Driver:** `SPI_Transmit(data, length);`
* **ADC Driver:** `ADC_Read(samples, 16);`
* **DMA Transfer:** Controllers receive a starting memory address and a number of bytes.
* **Image Processing:** `processImage(image, width, height);`

The actual data is **not copied**, making the function calls extremely fast and memory-efficient!

---

## Common Beginner Mistakes

**Mistake 1: Assuming the whole array is copied.**
Actually, only the address of the first element is passed.

**Mistake 2: Trying to determine the array length inside the function using `sizeof(pArray)`.**
This only gives the pointer size.

**Mistake 3: Forgetting to pass the number of elements.**
Without it, the function doesn't know where the array ends.

**Mistake 4: Modifying an array accidentally inside a display function.**
Use `const` whenever the function should only read the array.

**Mistake 5: Passing `someData + 2` but forgetting to reduce `nItems`.**
This may lead to accessing elements beyond the valid range (undefined behavior).

---

## Interview Questions

**Q1. What is actually passed when an array is passed to a function?**
> The address of the first element (a pointer), not the entire array.

**Q2. Why must the array size be passed separately?**
> Because once the array decays to a pointer, the function has no information about how many elements the original array contained.

**Q3. Why is `const` used when passing an array?**
> It prevents accidental modification of the array and clearly indicates that the function is read-only.

**Q4. Are `pArray[i]` and `*(pArray+i)` equivalent?**
> Yes. They access the same array element.

**Q5. What is the difference between `someData` and `&someData[0]`?**
> In most expressions, they evaluate to the same address (the address of the first element). However, they have different types in the C language, a distinction that becomes important in advanced topics.

---

## Glossary

| Term | Meaning |
| ---- | ------- |
| **Array Decay** | The automatic conversion of an array name to a pointer to its first element. |
| **Pointer Parameter** | A function parameter that stores the address of the first element of an array. |
| **`const` Pointer Parameter** | A pointer through which the data cannot be modified. |
| **Subarray** | A portion of an array passed by providing the address of one of its elements. |
| **Pointer Arithmetic** | Computing the address of another element by adding an offset to a pointer. |

---

## Practice Questions

### Conceptual
1. Why is only the address of the first element passed instead of copying the whole array?
2. Why can't a function determine the array length from the pointer?
3. Why is `const` recommended for display functions?
4. Explain the difference between `sizeof(array)` and `sizeof(pointer)`.
5. Why are `someData + 2` and `&someData[2]` equivalent?

### Coding
1. Write a function that prints all elements of an integer array.
2. Write a function that calculates the sum of an array.
3. Write a function that finds the maximum value in an array.
4. Modify the display function so it prints the array in reverse order.
5. Complete the instructor's exercise by writing a function that swaps the contents of two arrays, correctly handling arrays of different lengths.
