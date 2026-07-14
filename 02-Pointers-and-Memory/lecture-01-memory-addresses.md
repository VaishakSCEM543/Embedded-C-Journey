# Lecture 1 - Memory Addresses & Introduction to Pointers

## 1. What is a Memory Address?
When you create a variable (e.g., `char a1 = 'A';`), the computer stores the value (`'A'` or `0x41`) in a physical location in your RAM. 
* Every location in RAM has a unique **address**.
* You can think of RAM as a massive street of houses, and the address is the house number where your data lives.

## 2. How to get the Address? (The `&` Operator)
To find out *where* a variable is stored in memory, you use the **Ampersand (`&`)** symbol, also known as the "Address-of" operator.

```c
char myData = 'A';
// myData gives the value ('A')
// &myData gives the memory address (e.g., 0x0061FF1F)
```

## 3. Printing an Address (`%p`)
Addresses are usually printed in **Hexadecimal** format because it's easier to read for humans than long strings of binary or decimal.
* The format specifier to print a memory address is **`%p`** (stands for "pointer").

```c
printf("Address of a1 is: %p \n", &a1);
```

## 4. Size of a Memory Address (Architecture Dependent!)
This is a **critical concept for Embedded Engineers:** The size of a memory address changes depending on the processor you are coding for.

| Architecture | Example MCU/CPU | Address Size (Pointer Size) |
| :--- | :--- | :--- |
| **8-bit** | Arduino Uno (AVR ATmega328) | **2 bytes** (16 bits) |
| **32-bit** | STM32 (ARM Cortex-M) | **4 bytes** (32 bits) |
| **64-bit** | Your Windows PC / Linux | **8 bytes** (64 bits) |

Because you ran the code on your 64-bit PC, the address printed was 8 bytes long.

## 5. Storing an Address in a Variable (The Compiler Warning)
If you try to save an address inside a normal integer variable, the compiler will get angry and throw a warning:

```c
// WARNING: initialization makes integer from pointer without a cast
unsigned long int addressOfa1 = &a1; 
```
**Why the warning?**
Because `&a1` is not just a number, it is a **Pointer** (specifically, a `char *`). A pointer and a normal integer are entirely different data types to the compiler, even if they both look like numbers to us.

## 6. The Fix: Typecasting
To force the compiler to treat the pointer as a standard integer, you must **Typecast** it. Typecasting tells the compiler: *"I know what I'm doing, temporarily treat this data as this specific type."*

On a 64-bit machine, because the address is 8 bytes, you must use a data type that is also 8 bytes long (like `unsigned long long int`).

```c
// Correct way to store an address as a raw number on a 64-bit machine
unsigned long long int addressOfa1 = (unsigned long long int) &a1;

// Printing it in hex format (Using %I64X for MinGW Windows, or %llx for Linux)
printf("Address in hex: %I64X \n", addressOfa1); 
```

## 7. Stack Layout Observation (What `address.c` Actually Reveals)

When you run `address.c`, you'll see something like this:

```
Address of a: 000000000061FE1F
Address of b: 000000000061FE1E
Address of c: 000000000061FE1D
Address of d: 000000000061FE1C
Address of e: 000000000061FE1B
Address of f: 000000000061FE1A
```

Two things to notice:

**1. Each address is exactly 1 less than the previous one.**
- `char` is 1 byte, so each variable takes up exactly 1 address slot.
- If you used `int` variables instead, you'd see addresses differ by **4** (since `int` = 4 bytes).

**2. Addresses are going DOWN (decreasing), not up.**
- The stack on x86/x64 grows **downward** in memory.
- The first variable declared (`a`) gets the highest address; the last (`f`) gets the lowest.
- This is a hardware design decision — the stack starts at a high address and grows toward lower addresses.

> This is exactly why in embedded systems, stack overflow means the stack has grown so large it crashes into the heap or other memory regions from above.

---

### 💡 Embedded Takeaway
In bare-metal embedded programming (like STM32), you will constantly deal with memory addresses. Hardware peripherals (like GPIO pins, UART, Timers) are controlled by writing data to specific physical memory addresses given to you in the microcontroller's datasheet. Understanding that **addresses can be cast to raw numbers** (and vice-versa) is how you eventually learn to write your own driver code!
