# Module: Strings in C – Lecture 3, Part 3

# Behind the Scenes: How the Compiler Copies Strings from Flash to RAM

---

## 🎯 Learning Objectives

After studying this chapter, you will understand:

* Why the string `"Hello"` exists in Flash memory.
* Why another copy of the string appears in RAM.
* What happens during program execution.
* Difference between **compile time**, **startup time**, and **runtime**.
* Difference between **global variable initialization** and **local variable initialization**.
* Why local arrays require copying.

---

## 1. The Important Question

Consider the following code:

```c
int main()
{
    char msg1[] = "Hello";

    printf("%s", msg1);
}
```

A beginner usually thinks:

> "The compiler simply stores `Hello` inside `msg1`."

But that is **not what actually happens** in an embedded system.

---

## 2. Step 1 – Compilation

When the compiler compiles your program, it creates a binary file.
This binary is stored inside the microcontroller's **Flash memory**.

Inside Flash, the string `"Hello"` already exists.

```text
FLASH (Permanent Memory)

+----------------------------+
| Program Instructions       |
|                            |
| "Hello"                    |
|                            |
+----------------------------+
```

At this stage, the string is **only in Flash**.

---

## 3. Why Flash?

Flash memory stores:

* Program instructions
* Constant data
* String literals
* Initial values for initialized variables

Flash is **non-volatile** — its contents remain even after power is removed.

---

## 4. But `msg1` is a Local Array

```c
char msg1[] = "Hello";
```

From Part 2, we know that `msg1` is a **local array** — it must live in the **Stack**, which is inside **RAM**.

So we have a conflict:
- String is in **Flash**
- Array must exist in **RAM**

How does that happen?

---

## 5. The Compiler Creates Two Copies

This is the key idea of this lecture.

There are **two copies** of the string.

### Copy 1 — Flash
```text
FLASH

+------------------+
| Hello\0          |
+------------------+
```

### Copy 2 — RAM (Stack)
```text
RAM (Stack)

+------------------+
| Hello\0          |
+------------------+
```

### Diagram

```text
FLASH
+------------------+
| Hello\0          |  ← permanent, read-only
+------------------+
         |
         |  copied at runtime
         ↓
RAM (Stack)
+------------------+
| Hello\0          |  ← temporary, writable
+------------------+
```

---

## 6. When Does This Copy Happen?

> **During function execution (runtime)** — NOT at compile time or startup.

```text
Program starts
      ↓
main() called
      ↓
Stack memory allocated
      ↓
Characters copied from Flash → Stack
      ↓
msg1 becomes ready to use
```

---

## 7. Why Doesn't Startup Code Do This?

Earlier in the course, you learned that **startup code** copies initialized **global** variables from Flash to RAM.

> [!IMPORTANT]
> This does **NOT** apply to local variables.

**Reason:** Local variables don't exist before their function starts.
Startup code cannot initialize something that doesn't exist yet.

Instead, the copy happens when the function executes at runtime.

---

## 8. Global Initialization vs Local Initialization

### Global Variable

```c
char globalMsg[] = "Hello";
```

```text
Startup Code (before main)
      ↓
Flash → Global Data Section (RAM)
```

---

### Local Variable

```c
int main()
{
    char msg1[] = "Hello";
}
```

```text
main() starts
      ↓
Stack allocated
      ↓
Flash → Stack (Runtime copy)
```

---

## 9. Execution Flow

Conceptually, the CPU does this:

```text
Function starts
      ↓
Reserve stack space for msg1
      ↓
Read "Hello\0" from Flash
      ↓
Write each character into msg1 on the stack
      ↓
Continue execution with msg1 ready
```

The CPU is actually copying each character into RAM **before your code begins using the array**.

---

## 10. Why Is This Necessary?

Because:

```c
msg1[0] = 'B';   // This must be legal!
```

If the array remained in Flash, this write would fail — Flash is read-only during normal execution.

Therefore, the compiler always creates a **writable copy in RAM**.

---

## 11. Memory Diagram (Full Lifecycle)

### Before `main()` starts:
```text
FLASH           RAM (Stack)
+----------+    (empty)
| Hello\0  |
+----------+
```

### While inside `main()`:
```text
FLASH           RAM (Stack)
+----------+    +----------+
| Hello\0  | →  | Hello\0  |
+----------+    +----------+
(permanent)     (writable copy)
```

### After `main()` returns:
```text
FLASH           RAM (Stack)
+----------+    (empty again)
| Hello\0  |
+----------+
```

> [!NOTE]
> The Flash copy **always remains**. The RAM copy **disappears** when the function ends.

---

## 12. What Happens When We Modify the Array?

```c
msg1[0] = 'B';
```

Only the RAM copy changes:

```text
FLASH       → Hello\0   (unchanged)
RAM (Stack) → Bello\0   (modified)
```

Flash remains untouched.

---

## 13. Embedded Systems Perspective — STM32 Memory Map

```text
FLASH:  0x08000000  →  Program + String Literals + Constants
RAM:    0x20000000  →  Stack + Heap + Global Variables
```

In the STM32CubeIDE debugger:
- Address starting with `0x0800....` → **Flash**
- Address starting with `0x2000....` → **RAM**

This helps identify exactly where your data lives during debugging.

---

## ⚠️ Common Misconceptions

| Misconception | Reality |
|:-------------|:--------|
| "Only one copy of the string exists" | ❌ Two copies: one in Flash, one in RAM (Stack) |
| "Startup code initializes local variables" | ❌ Startup code handles globals/statics only |
| "The RAM copy exists forever" | ❌ It exists only while the function is active |

---

## ⭐ Important Points

* Every compiled program resides in Flash.
* String literals used for initialization are stored in Flash.
* Local arrays live in the Stack (RAM).
* Local array initialization copies data from Flash → RAM at **runtime**.
* This copy happens during function execution, **not** before `main()`.
* After the function returns, the RAM copy is destroyed.
* The Flash copy always remains.

---

## 🎯 Interview Questions

**Q1. Why are there two copies of `"Hello"`?**
One copy is in Flash as part of the compiled program. When a local array is initialized, a writable copy is created in the stack (RAM) during function execution.

**Q2. Why can't the local array directly use the Flash copy?**
Because local arrays are writable. Flash is read-only during normal execution, so a writable copy must exist in RAM.

**Q3. When does the Flash-to-RAM copy occur for a local array?**
During function execution (runtime), after the function starts and stack space is allocated.

**Q4. Does startup code initialize local variables?**
No. Startup code initializes global/static initialized variables. Local variables are initialized when their function executes.

**Q5. What happens to the RAM copy after the function returns?**
The stack frame is removed and the RAM copy is destroyed.

**Q6. Why is understanding Flash-to-RAM copying important in embedded?**
It explains RAM usage, execution overhead, and why initializing large local arrays increases stack usage and runtime cost.

**Q7. How do you identify Flash vs RAM addresses in an STM32 debugger?**
Flash addresses begin around `0x0800xxxx`, RAM addresses begin around `0x2000xxxx`.

---

## 📌 Quick Revision

```text
Compile time:  "Hello" stored in Flash (inside binary)
               ↓
main() starts: Stack allocated for msg1
               ↓
Runtime:       Compiler-generated code copies Flash → Stack
               ↓
msg1 is ready: writable RAM copy
               ↓
Function ends: RAM copy destroyed
               ↓
Always:        Flash copy remains forever
```

> **Placement Tip:** "What happens internally when you write `char msg[] = "Hello";`?" is a guaranteed embedded interview question.
>
> Strong answer = Flash copy + Stack (RAM) copy + runtime copy + temporary lifetime.
