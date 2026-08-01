# Module: Strings in C – Lecture 2

# String Literals (String Constants) vs Character Arrays

---

## 🎯 Learning Objectives

After this lecture, you should be able to:

* Understand what a **string literal (string constant)** is.
* Differentiate between a **character array** and a **character pointer**.
* Know where each is stored in memory (RAM vs ROM).
* Understand why one is modifiable and the other is not.
* Answer common placement and interview questions related to string storage.

---

## 📖 What I Learned Today

### 1. String Literals

A **string literal** is a string written directly inside double quotes `" "`.

```c
"Hello"
"Embedded C"
"How are you?"
```

These are created by the **compiler** and stored in **read-only memory (ROM / Flash)**.

---

### 2. Two Ways to Store a String

#### Method 1 — Character Array (RAM)

```c
char msg[] = "Hello";
```

- Compiler creates an **array** and **copies** every character into it.
- Stored in **RAM** → writable memory.
- You **own** the memory.

```
RAM
+----+----+----+----+----+----+
| H  | e  | l  | l  | o  |\0 |
+----+----+----+----+----+----+
```

---

#### Method 2 — Character Pointer (ROM)

```c
char *msg = "Hello";
```

- The string `"Hello"` is placed in `.rodata` (read-only section) by the compiler.
- `msg` is a **pointer** that stores only the **address** of the first character.
- Stored in **ROM/Flash** → read-only memory.

```
Pointer Variable (RAM)       ROM / Flash
+-----------+                +----+----+----+----+----+----+
|0x08001000 | ─────────────► | H  | e  | l  | l  | o  |\0 |
+-----------+                +----+----+----+----+----+----+
```

> [!IMPORTANT]
> `msg` stores only the **address**. The string itself lives in ROM. The pointer does **not** own the string.

---

### 3. The Critical Difference: Modifiability

#### ✅ Array — Can Modify

```c
char msg[] = "Hello";
msg[0] = 'S';
printf("%s", msg);  // Output: Sello
```

Works perfectly — the array lives in writable RAM.

---

#### ❌ Pointer — Cannot Modify

```c
char *msg = "Hello";
msg[0] = 'S';  // ⚠️ UNDEFINED BEHAVIOR
```

> [!CAUTION]
> Attempting to modify a string literal via a pointer causes **Segmentation Fault** or **Memory Access Violation** on most systems, and undefined behaviour in embedded. The string lives in read-only memory.

---

### 4. Printing Strings

```c
printf("%s", msg);
```

`%s` prints characters starting from the given address until it finds `'\0'`.

---

### 5. Embedded Systems Context

On an STM32 microcontroller:

| Declaration | Memory Region | Address Range |
|:-----------|:-------------|:-------------|
| `char msg[] = "Hello";` | RAM (SRAM) | `0x2000xxxx` |
| `char *msg = "Hello";` | Flash/ROM (`.rodata`) | `0x0800xxxx` |

The instructor demonstrated this using the **Variables Window** in the debugger — the base address `0x2001FFDC` confirms the array is in RAM.

---

## 📊 Full Comparison Table

| Feature | `char msg[] = "Hello";` | `char *msg = "Hello";` |
|:--------|:------------------------|:-----------------------|
| Type | Character Array | Character Pointer |
| Owns memory? | ✅ Yes | ❌ No |
| String stored in | RAM (writable) | ROM / `.rodata` (read-only) |
| Can modify characters? | ✅ Yes | ❌ No (undefined behaviour) |
| `'\0'` added? | ✅ Yes | ✅ Yes |
| Safe for editing | ✅ Yes | ❌ No |
| Best use | Mutable strings | Fixed, constant text |

---

## ✅ Best Practices

```c
// Mutable string → use an array
char name[] = "Vaishak";
name[0] = 'v';  // Safe ✅

// Read-only text → use const pointer (shows intent clearly)
const char *msg = "Hello";
// msg[0] = 'S';  // Compiler will warn/error ✅
```

> [!TIP]
> Always prefer `const char *` over `char *` when pointing to a string literal. The `const` keyword makes your intent explicit and lets the compiler catch accidental modifications.

---

## ⚠️ Common Mistakes

| Mistake | Why It's Wrong |
|:--------|:---------------|
| `char *msg = "Hello"; msg[0] = 'A';` | Modifying ROM — undefined behaviour |
| Thinking `char *msg` stores the string | It stores only the **address** |
| Treating `char[]` and `char *` as identical | Different memory, different mutability |

---

## 🎯 Interview Questions

**Q1. What is a string literal?**
A sequence of characters in double quotes. The compiler stores it in read-only memory (`.rodata`) and automatically adds `'\0'`.

**Q2. Difference between `char str[] = "Hello"` and `char *str = "Hello"`?**
The array copies the string into writable RAM and you can modify it. The pointer points to the string in read-only ROM — you must not modify it.

**Q3. Can you modify a string literal?**
No. String literals are in read-only memory. Modifying them causes undefined behaviour.

**Q4. What does `char *` actually store?**
The memory **address** of the first character. Not the string itself.

**Q5. Where are string literals stored in embedded systems?**
In **Flash/ROM** (the `.rodata` section). Writable character arrays go in **RAM/SRAM**.

---

## ⚡ 30-Second Revision

```
String Literal "Hello"  →  ROM / Read-only  →  Cannot modify
char msg[] = "Hello"    →  RAM              →  Can modify
char *msg = "Hello"     →  Pointer to ROM   →  Cannot modify
const char *msg         →  Best practice for read-only strings
printf("%s", msg)       →  Prints until '\0'
```

> **Placement Tip:** Interviewers frequently ask the difference between `char str[] = "Hello"` and `char *str = "Hello"`. Focus on three points: **memory location (RAM vs ROM), ownership (array vs pointer), and mutability.** Those three differences form a complete answer.
