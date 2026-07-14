# Lecture 2 — What is a Pointer?

## 1. Why Pointers Make C Powerful

Without pointers, you can only work with variables — you're always working *through* a name.

With pointers, you can work **directly with memory** — you tell the CPU exactly which address to read or write.

That is the reason C is called a **middle-level language**: it sits between high-level languages (which hide memory) and assembly (which is all memory).

---

## 2. Think of RAM as an Apartment Building

Every location in RAM has:
- a unique **address** (house number)
- some **data** stored there (the person living in that house)

```
Address        Data
---------------------
1000           25
1001           40
1002           89
1003           10
1004           65
```

Each row is **1 byte**.

---

## 3. What is a Pointer?

> **A pointer is a memory address.**

It is NOT the data itself. It is the **address where the data lives**.

```
Address        Data
-------------------
1000           10
1001           25       ← pointer 1001 "points" to value 25
1002           90
```

Visualise it as an arrow:

```
1001  ───────────────► 25
```

The address `1001` **points to** the data `25`. That's the whole concept.

---

## 4. Hotel Room Analogy

```
Room Number      Guest
----------------------
101              Rahul
102              Priya
103              Aman
```

- **Room number** → pointer (address)
- **Guest** → data (value stored at that address)

If someone asks *"Where is Rahul?"*, you answer: **Room 101**.

Similarly, if the CPU asks where the value `25` is, the answer is: **address 1001**.

> **Pointer tells you "where."**  
> **Data tells you "what."**

---

## 5. Why Does the CPU Need an Address?

Suppose you want to change `90` to `150` in memory.

```
Address       Data
1002          90   ← want to change this
```

The CPU cannot guess. It needs the **exact address** (`1002`) to know which byte to overwrite. That's why pointers are necessary for any direct memory manipulation.

---

## 6. Four Operations You Can Do with a Pointer

| Operation | What it does |
|:----------|:-------------|
| **Write** | Store a value at the address the pointer holds |
| **Read** | Retrieve the value stored at that address |
| **Increment** | Move the pointer forward to the next memory location |
| **Decrement** | Move the pointer backward to the previous location |

### Write through a pointer

```
Before:   Address 1000  →  10
Action:   Write 50 to address 1000
After:    Address 1000  →  50
```

### Read through a pointer

```
Address 1001  →  80
Reading via pointer 1001  →  gives you  80
```

### Increment a pointer

```
Pointer currently holds:  1000
After increment:          1001   ← now points to the next byte
```

### Decrement a pointer

```
Pointer currently holds:  1003
After decrement:          1002   ← now points to the previous byte
```

---

## 7. Why Embedded Systems Are Impossible Without Pointers

In a microcontroller, **hardware registers are just memory addresses**.

For example, imagine an LED is connected to a GPIO register at address `0x40021000`.

| Action | What to do |
|:-------|:-----------|
| Turn LED **ON** | Write `1` to address `0x40021000` |
| Turn LED **OFF** | Write `0` to address `0x40021000` |

How does your C program access that register?

**Using a pointer.**

The code (which you'll write in STM32 bare-metal chapters) looks like:

```c
*(unsigned int *)(0x40021000) = 1;   /* LED ON  */
*(unsigned int *)(0x40021000) = 0;   /* LED OFF */
```

This is **exactly** how every MCU driver, HAL library, and register-level operation works at its core.

---

## 8. Pointer Size Depends on the Processor

A pointer must be large enough to hold **any address** the CPU can generate. That size is fixed by the hardware, not by C.

| Architecture | Example MCU/CPU | Pointer Size |
|:-------------|:----------------|:-------------|
| **8-bit** | PIC18 | 2 bytes (16-bit address bus) |
| **32-bit** | STM32 (ARM Cortex-M) | 4 bytes |
| **64-bit** | Your Windows/Linux PC | 8 bytes |

---

## 9. Pointer Concept vs Pointer Variable in C

| Term | Meaning |
|:-----|:--------|
| **Pointer (concept)** | A memory address — e.g., `1001` or `0x40021000` |
| **Pointer variable (C code)** | A variable whose value *is* an address |

In C, a pointer variable is declared with `*`:

```c
int *p;   /* p is a pointer variable — it will store an address */
```

Whatever address you store in `p`, the CPU will use it to find the actual data.

You'll use `&` (address-of) and `*` (dereference) with pointer variables in the next lecture.

---

## 10. Common Beginner Mistake

> ❌ "A pointer is the data."

That is **wrong**.

Always keep this table in your head:

```
Address       Data
------------------
1000          25
```

- `1000` → **Pointer** (where)
- `25`   → **Data**    (what)

Confusing the two causes bugs that are extremely hard to find. Especially in embedded code where the wrong address means writing to the wrong register — and nothing works the way you expect.

---

## 💡 Embedded Takeaway

Every time you see something like this in STM32 code:

```c
#define GPIOA_ODR   *((volatile unsigned int *) 0x40010C0C)

GPIOA_ODR = 0x01;   /* Set pin 0 HIGH */
```

You are looking at a **pointer** in action.

The address `0x40010C0C` is a pointer to the GPIO Output Data Register. Writing to it physically changes the voltage on the pin.

This is not magic — this is exactly what you just learned. The CPU reads the address, goes to that memory location, and writes the value. That value controls real hardware.

Understanding the concept in this lecture is the foundation for understanding all of that.
