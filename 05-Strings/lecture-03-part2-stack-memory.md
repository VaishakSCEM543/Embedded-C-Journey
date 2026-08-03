# Module: Strings in C – Lecture 3, Part 2

# Where Does a Local Array Actually Live? (Stack Memory)

---

## 🎯 Learning Objectives

After this part, you should be able to:

* Explain what **stack memory** is and where it lives in RAM.
* Understand why a **local array is temporary**.
* Describe the **function call lifecycle** and its effect on stack memory.
* Explain how the **stack pointer** moves during a function call.
* Know what happens to a local array after the function returns.

---

## 📖 What I Learned Today

### 1. Local Variables and Where They Live

Any variable declared inside a function is a **local variable**.

```c
void printGreeting(void) {
    char msg[] = "Hello";   // local array
    printf("%s\n", msg);
}   // msg is GONE after this line
```

`msg` is a **local array**. It lives in **Stack Memory**.

---

### 2. What is Stack Memory?

RAM in a microcontroller (or PC) is divided into segments:

```
RAM Layout (Simplified)
─────────────────────────────
│  Global / Static Variables │  ← .data / .bss section
├────────────────────────────┤
│         Heap               │  ← dynamic allocation (malloc)
├────────────────────────────┤
│                            │
│          Stack             │  ← local variables, function calls
│       (grows down)         │
─────────────────────────────
```

The **stack** is the region of RAM used for:
- Local variables
- Function parameters
- Return addresses
- Saved registers

> [!NOTE]
> On most architectures (ARM Cortex-M, x86), the stack **grows downward** — from a higher address toward a lower address.

---

### 3. The Stack Pointer

The **stack pointer (SP)** is a CPU register that always points to the **top of the stack** (current free position).

```
Before function call:
SP → 0x20002000

After calling printGreeting():
SP → 0x20001FFA   (moved down by 6 bytes for "Hello\0")
```

The stack pointer **decrements** when memory is allocated for locals, and **increments** when the function returns.

---

### 4. Function Call Lifecycle

```
Step 1 — main() calls printGreeting()
─────────────────────────────────────
CPU saves return address on the stack.
SP moves down.

Step 2 — Inside printGreeting()
────────────────────────────────
char msg[] = "Hello" is allocated on the stack.
SP moves down by 6 bytes.
"Hello\0" is written into those 6 bytes.

     Stack
     ──────────────────────
SP → │ H │ e │ l │ l │ o │\0│   ← msg[]
     ──────────────────────

Step 3 — printGreeting() returns
──────────────────────────────────
SP moves back UP.
The 6 bytes are no longer "owned" by anyone.
The data may still be there physically, but it's considered GONE.
```

> [!CAUTION]
> **Never return a pointer to a local array.**
>
> ```c
> char *getBadPointer(void) {
>     char msg[] = "Hello";
>     return msg;   // ❌ UNDEFINED BEHAVIOUR — stack memory reclaimed
> }
> ```
>
> After the function returns, `msg` no longer exists. The pointer is now **dangling** — pointing to memory that may be overwritten at any moment.

---

### 5. Why Local Arrays Are Temporary

| Property | Local Array | Global Array |
|:---------|:------------|:-------------|
| Memory region | Stack (RAM) | Data segment (RAM) |
| Lifetime | During function call only | Entire program duration |
| Created when | Function is called | Program starts |
| Destroyed when | Function returns | Program ends |
| Automatic? | ✅ Yes | ✅ Yes |

---

### 6. Stack Diagram — Full Picture

```
High Address
┌─────────────────────────────────┐
│          main() frame           │
│   int x = 5;                   │
│   ...                           │
├─────────────────────────────────┤
│       printGreeting() frame     │
│   char msg[] = "Hello\0"        │  ← 6 bytes
│   (return address saved here)   │
├─────────────────────────────────┤  ← SP points here while inside function
│         (free stack space)      │
└─────────────────────────────────┘
Low Address
```

When `printGreeting()` returns, the SP moves back up — the frame is gone.

---

### 7. Embedded Perspective

On an **STM32** microcontroller:
- RAM starts at `0x20000000`
- The stack typically starts at the **top of RAM** (e.g., `0x20020000`)
- Local arrays are allocated on the stack at runtime

You can watch the SP move in the **Registers view** of the STM32CubeIDE debugger while stepping through function calls.

> [!TIP]
> Stack size is **fixed and limited** in embedded systems (often 1–8 KB). A large local array can cause a **stack overflow** — one of the most dangerous bugs in embedded C. Prefer global or static arrays for large buffers.

---

## ⚠️ Common Mistakes

| Mistake | Why It's Dangerous |
|:--------|:-------------------|
| Returning pointer to local array | Dangling pointer → undefined behaviour |
| Declaring a huge array locally | Stack overflow → crash or silent corruption |
| Assuming local array data persists after return | Stack is reclaimed — data is invalid |

---

## 🎯 Interview Questions

**Q1. Where are local variables stored?**
On the **stack** — a region of RAM managed automatically by the CPU using the stack pointer.

**Q2. What happens to a local array after a function returns?**
The stack pointer moves back and the memory is reclaimed. The array no longer exists. Any pointer to it becomes a **dangling pointer**.

**Q3. Why does the stack grow downward?**
This is an architectural convention (used in ARM, x86). The stack starts at a high address and grows toward lower addresses as more items are pushed.

**Q4. What is a stack overflow?**
When local variable allocations exceed the available stack space. This overwrites adjacent memory — usually causing a crash or silent data corruption.

**Q5. Is it safe to return a local array from a function?**
No. The array lives on the stack and is destroyed when the function returns. Return a `static` array or pass in a buffer from the caller instead.

**Q6. What is the stack pointer?**
A CPU register (SP) that tracks the current top of the stack. It decrements when locals are allocated and increments when a function returns.

---

## ⚡ Quick Revision

```
Local array → Stack memory → Temporary
─────────────────────────────────────────
Stack grows downward (high → low address)
SP (stack pointer) tracks top of stack

Function called   → SP decrements (space allocated)
Function returns  → SP increments (space reclaimed)

❌ Never return a pointer to a local array → dangling pointer
⚠️ Large local arrays → stack overflow risk in embedded

Global array → .data / .bss → persists entire program
Local array  → stack         → exists only during function call
```

> **Placement Tip:** "Can you return a local array from a function?" is a guaranteed viva question. The answer is **no** — because the stack frame is destroyed on return. Always mention **dangling pointer** and **undefined behaviour** in your answer.
