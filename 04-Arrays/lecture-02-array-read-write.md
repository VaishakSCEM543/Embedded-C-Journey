# Arrays in C - Lecture 2: Reading, Writing, and Initialization

> [!NOTE]
> **Difficulty:** 🟢 Beginner

## Learning Objectives

After completing this lecture, you should be able to:
* Initialize arrays fully or partially at declaration.
* Understand what happens to uninitialized elements in a partially initialized array.
* Declare Variable Length Arrays (VLAs) and understand their standard requirements.
* Read and write to array elements using pointer manipulation.
* Use array indexing shorthand and explain why indices start at zero.
* Traverse an entire array using a loop.

---

## 1. Array Initialization Rules

You can initialize an array at the exact moment you define it using curly braces `{}`.

### Full Initialization
```c
uint8_t someData[3] = {0xff, 0xff, 0xff};
```
This perfectly initializes all 3 elements.

### Partial Initialization
```c
uint8_t someData[10] = {0xff, 0xff, 0xff};
```
Here, we only provided 3 values for an array of size 10. 
> [!IMPORTANT]
> **The Zero-Fill Rule:** If you partially initialize an array, the compiler automatically initializes all the **remaining elements to zero**.

### Omitted Size Initialization
```c
uint8_t someData[] = {1, 2, 3};
```
By providing an initialization list, you give the compiler enough information to automatically calculate the size of the array. The compiler will size this array to exactly 3 elements.

### Missing Size Error
```c
uint8_t someOtherData[]; // ❌ Error!
```
If you do not provide a size *and* you do not provide an initialization list, the compiler will throw an error because it cannot determine how much memory to allocate.

---

## 2. Variable Length Arrays (VLA)

Normally, the size of an array is fixed at compile-time. However, C allows you to use a variable to dictate the size.

```c
int len = 10;
uint8_t arr[len]; // Variable Length Array
```

> [!WARNING]
> **Standard Compliance:** This syntax is known as a **Variable Length Array (VLA)**. It was introduced in the **C99 standard**. If you compile this code using the older C90 (ANSI C) standard with strict warnings enabled, the compiler will throw an error: `ISO C90 forbids variable length array`.

---

## 3. Pointer Manipulation vs Shorthand Indexing

How do you read or write a new value to a specific array element? Because array elements are stored in contiguous memory locations, we can find any element by simply adding an offset to the base pointer.

### The Background Process (Pointer Manipulation)
The array name holds the base address. To access the 2nd element (which is 1 step away from the start), you increment the pointer by 1 and dereference it:

```c
*(someData + 1) = 0x09; // Write 0x09 to the 2nd element
```

### The Shorthand (Array Indexing)
Writing `*(someData + 1)` every time is tedious. C provides a shorthand using square brackets `[]`:

```c
someData[1] = 0x09; // Shorthand for writing to the 2nd element
```

> [!TIP]
> **Why Array Indexing Starts at 0:**
> The syntax `someData[index]` is strictly converted by the compiler into `*(someData + index)`. 
> If you want to access the **very first element**, you need to offset the base address by zero!
> `someData[0]` translates exactly to `*(someData + 0)`.

---

## 4. Traversing an Array

If you need to read or write to every element in an array, doing it line-by-line is inefficient. The standard approach is to use a `for` loop to step through the offsets `0` through `9`.

```c
// Initializing all 10 elements to 0x33
for(uint32_t i = 0; i < 10; i++) {
    someData[i] = 0x33;      
}

// Printing all 10 elements
for(uint32_t i = 0; i < 10; i++) {
    printf("%x\t", someData[i]); 
}
```

---

## Common Beginner Mistakes

1. **Forgetting zero-based indexing:** Trying to access the 10th element of a 10-element array using `someData[10]`. The valid indices are `0` through `9`. `someData[10]` writes out of bounds into unknown memory!
2. **Using VLAs in strict older codebases:** Using `int arr[len]` in a project that enforces C90 strict compliance.

---

## Interview Questions

**Q1. What happens to the uninitialized elements if you only initialize the first two elements of a 100-element array?**
> The compiler automatically initializes the remaining 98 elements to zero.

**Q2. Why does array indexing start at zero in C?**
> Because array indexing is just shorthand for pointer arithmetic. The index represents the offset from the base address. The first element is at an offset of 0 from the start, so it is accessed via `array[0]`, which the compiler translates to `*(array + 0)`.

---

## Practice Questions

### Conceptual
1. Is `uint32_t arr[];` a valid C statement? Why or why not?
2. What is the equivalent pointer manipulation syntax for `myArray[5] = 10;`?

### Coding
1. Write a program that creates an array of 5 integers, partially initializes the first element to `1`, and then prints all 5 elements to verify the zero-fill rule.
2. Prompt the user for a length, create a VLA of that length, and fill it with values using a `for` loop.
