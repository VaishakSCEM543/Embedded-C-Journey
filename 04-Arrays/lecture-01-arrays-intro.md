# Lecture 1 — Introduction to Arrays in C

## Why Arrays?

Imagine you need to store the age of 100 students. You could write:
```c
uint8_t student1Age = 20;
uint8_t student2Age = 21;
// ...
uint8_t student100Age = 19;
```
This is tedious and inefficient. Arrays allow you to group multiple data items of the **same type** under a single reference name.

```c
uint8_t studentsAge[100];
```
This creates 100 data items of type `uint8_t` in memory.

---

## Array Syntax & Rules

```c
uint8_t data[10];
```
- **Type (`uint8_t`)**: The data type of the items stored.
- **Name (`data`)**: The label given to this collection. It acts as a reference or a base pointer.
- **Size (`[10]`)**: The total number of items the array can hold. Must be enclosed in square brackets `[]` (not parentheses or curly braces).

---

## Memory Storage

Arrays are stored in **contiguous memory locations**. This means all items are placed right next to each other in RAM.
Because they are contiguous, if you know the base address, you can easily calculate the address of any item.

### Size of an Array
The total memory consumed by an array is:
`Number of elements * sizeof(data_type)`

For example:
```c
uint8_t arr1[100];   // 100 * 1 byte = 100 bytes
uint32_t arr2[100];  // 100 * 4 bytes = 400 bytes
```
You can use the `sizeof` operator to find the total bytes consumed:
```c
printf("Size: %lu bytes", (unsigned long)sizeof(arr2)); // prints 400
```

---

## The Base Address (Array Name)

The array name itself acts as a **base pointer** that holds the base address of the array. The base address is just the memory address of the very first element (index 0).

Because it acts as a pointer to the first item, its data type is a pointer to the array's data type.
For `uint8_t studentsAge[100];`:
- Data type of an item: `uint8_t`
- Data type of `studentsAge`: `uint8_t*`

You can print the base address using `%p`:
```c
printf("Base address: %p", (void*)studentsAge);
```
