# Array Read and Write Operations

## 1. Array Initialization Rules
- **Full Initialization:** `uint8_t arr[3] = {0xff, 0xff, 0xff};`
- **Partial Initialization:** `uint8_t arr[10] = {0xff, 0xff, 0xff};`
  - If you partially initialize an array, the compiler automatically initializes all the **remaining elements to zero**.
- **Omitted Size:** `uint8_t arr[] = {1, 2, 3};`
  - The compiler automatically calculates the array size based on the initialization list (in this case, size = 3).
- **Uninitialized Size Error:** `uint8_t arr[];`
  - Without a size or initialization list, the compiler throws an error because it cannot allocate the required memory.

## 2. Variable Length Arrays (VLA)
Introduced in the **C99 standard**, you can use a variable to define the length of an array.
```c
int len = 10;
uint8_t arr[len]; // Variable Length Array
```
> [!WARNING]
> This will throw a warning/error if compiled using the older **C90 (ANSI C)** standard. VLAs are strictly a C99+ feature.

## 3. Pointer Manipulation vs Shorthand Indexing
Array elements are stored in contiguous memory locations. You can navigate through them by incrementing the base pointer.

### Pointer Manipulation (The actual background process)
The array name holds the base address. To access the 2nd element (index 1), you increment the pointer by 1 and dereference it:
```c
*(someData + 1) = 0x09; // Write 0x09 to the 2nd element
```

### Array Indexing (The Shorthand)
Array indexing using square brackets `[]` is just syntax sugar provided by the compiler.
```c
someData[1] = 0x09; // This is internally converted to *(someData + 1) by the compiler
```
This is the **real reason array indexing starts at 0**. 
- `someData[0]` is identical to `*(someData + 0)`. The 0th element is located at an offset of 0 from the base address!

## 4. Traversing an Array
Using a loop is the most efficient way to read, write, or initialize all elements in an array.
```c
for(uint32_t i = 0; i < 10; i++) {
    someData[i] = 0x33;      // Write to array
    printf("%x\n", someData[i]); // Read from array
}
```
