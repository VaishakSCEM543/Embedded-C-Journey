# Module: Storage Classes in C – Lecture 1

# Static Variables — Scope, Visibility, and Lifetime

---

## 🎯 Learning Objectives

After this lecture, you will understand:

* What a **storage class** is and what it controls.
* The three properties: **scope**, **visibility**, and **lifetime**.
* Why a local variable **loses its value** between calls.
* Why a global variable **retains its value** but is dangerous.
* How `static` solves both problems at once.
* Where `static` is used in embedded systems.

---

## 1. What Are Storage Classes?

A **storage class** tells the compiler how a variable or function should behave.

It controls three things:

| Property | Question It Answers |
|:---------|:--------------------|
| **Scope** | Where can I use this variable? |
| **Visibility** | Which functions can access it? |
| **Lifetime** | How long does it stay alive in memory? |

---

## 2. The Three Properties Explained

### Scope

```c
void fun()
{
    int x = 10;   // x exists only inside fun()
}

printf("%d", x);  // ❌ ERROR — x is out of scope
```

---

### Visibility

```c
int count;   // global — visible to everyone

void A() { count++; }   // ✅
void B() { count = 0; } // ✅ — any function can change it
```

---

### Lifetime

```c
void fun()
{
    int x = 10;
}   // x is DESTROYED here — lifetime ends with the function
```

---

## 3. The Problem Statement

> *"How many times has this function been called?"*

```c
int main()
{
    myFun1();
    myFun1();
    myFun1();
    myFun1();
}
```

Expected output:
```
1
2
3
4
```

---

## 4. First Attempt — Local Variable

```c
void myFun1()
{
    int count = 0;
    count++;
    printf("%d\n", count);
}
```

**Output:**
```
1
1
1
1
```

**Why?** Every function call creates a **brand new `count`** starting from `0`.

```text
Call 1:  count created → count=0 → count++ → print 1 → DESTROYED
Call 2:  count created → count=0 → count++ → print 1 → DESTROYED
Call 3:  count created → count=0 → count++ → print 1 → DESTROYED
```

---

## 5. Second Attempt — Global Variable

```c
int count = 0;

void myFun1()
{
    count++;
    printf("%d\n", count);
}
```

**Output:**
```
1
2
3
4
```

✅ Works — but creates a new problem.

**Problem:** `count` is now visible to **every function** in every source file.

```c
void reset()  { count = 0; }     // any function can corrupt it
void hack()   { count = -999; }  // accidental or intentional damage
```

---

## 6. What We Actually Need

```
✅ Value should persist across function calls  →  like a global
✅ Nobody else should be able to access it    →  like a local
```

That combination is exactly what `static` provides.

---

## 7. The Solution — `static` Local Variable

```c
void myFun1()
{
    static int count = 0;   // only ONE word added
    count++;
    printf("%d\n", count);
}
```

**Output:**
```
1
2
3
4
```

✅ Correct output AND nobody outside can touch `count`.

---

## 8. How `static` Works — Step by Step

```text
Program starts
      ↓
count created ONCE and set to 0
      ↓
Call 1: count=0 → count++ → print 1 → function ends → count SURVIVES
      ↓
Call 2: count=1 → count++ → print 2 → function ends → count SURVIVES
      ↓
Call 3: count=2 → count++ → print 3 → function ends → count SURVIVES
      ↓
Call 4: count=3 → count++ → print 4 → function ends → count SURVIVES
      ↓
Program ends → count destroyed (finally)
```

> [!IMPORTANT]
> The line `static int count = 0;` runs **only once** — at program start.
> On every subsequent call, the initialization is **skipped**.
> The variable retains whatever value it had from the previous call.

---

## 9. Memory Location of a `static` Variable

A `static` local variable does **not** live on the stack.

It lives in the **data segment** (RAM) — same region as global variables.

```text
RAM Layout

+---------------------------+
| Global Variables          |
| Static Local Variables    |  ← count lives here
+---------------------------+
| Heap                      |
+---------------------------+
| Stack                     |  ← normal local variables
+---------------------------+
```

This is why it survives function returns — the stack is cleared, but the data segment is not.

---

## 10. Comparison Table

| Property | Local Variable | Global Variable | `static` Local Variable |
|:---------|:--------------:|:---------------:|:-----------------------:|
| Scope | Function only | Entire program | Function only |
| Visibility | Function only | All functions | **Function only** ✅ |
| Lifetime | During call | Entire program | **Entire program** ✅ |
| Value retained? | ❌ No | ✅ Yes | ✅ Yes |
| Safe from outside? | ✅ Yes | ❌ No | ✅ Yes |

---

## 11. Real-Life Analogy

### Local Variable → Classroom Whiteboard
Teacher writes on the board. Class ends. Board is erased. Next class starts blank.

### Global Variable → Notice Board Outside
Everyone can read it. Everyone can write on it. Anyone can erase it.

### Static Local Variable → Teacher's Personal Notebook
Only the teacher can use it. Even after class ends, the notebook still has previous notes. Perfectly private and persistent.

---

## 12. Where Is `static` Used in Embedded Systems?

`static` local variables are **everywhere** in embedded C:

```c
// Debounce counter — persists between ISR calls
void BUTTON_ISR(void)
{
    static uint32_t debounce_count = 0;
    debounce_count++;
    if(debounce_count > 50)
    {
        toggle_LED();
        debounce_count = 0;
    }
}

// State machine — current state persists
void process_uart(void)
{
    static uint8_t state = STATE_IDLE;
    // state is remembered between calls
}
```

> [!TIP]
> In embedded drivers and state machines, **almost every persistent variable** that belongs to a function is declared `static`. It's the professional way to maintain state without polluting global scope.

---

## ⚠️ Common Mistakes

| Mistake | Why It's Wrong |
|:--------|:---------------|
| Expecting local variable to retain value | It's destroyed on every return |
| Using global to retain state | Dangerous — any function can corrupt it |
| Thinking `static int x = 0` reinitializes every call | ❌ It initializes **only once** |
| Forgetting `static` in a state machine function | Causes state reset on every call |

---

## 🎯 Interview Questions

**Q1. What does a storage class specify?**
It specifies the **scope**, **visibility**, and **lifetime** of a variable or function.

**Q2. Why does a local variable lose its value between function calls?**
Because local variables are stored on the stack and destroyed when the function returns.

**Q3. Why does a global variable retain its value?**
Because it lives in the data segment (RAM), which persists for the entire program duration.

**Q4. Why use `static` inside a function?**
To preserve the variable's value across calls while keeping it private (inaccessible) to other functions.

**Q5. Does a static local variable get re-initialized on every call?**
No. It is initialized **only once** at program start. The initialization line is skipped on all subsequent calls.

**Q6. Where in memory does a static local variable live?**
In the **data segment** (same as global variables), not on the stack.

**Q7. Name two embedded use cases for static local variables.**
Debounce counters in ISRs and state variables in state machines/protocol parsers.

---

## 📌 Quick Revision

```
Storage class → controls Scope + Visibility + Lifetime

Local variable  → stack → destroyed on return → no persistence
Global variable → data segment → persists → but visible everywhere (dangerous)
static local    → data segment → persists → visible only inside function ✅

static int x = 0;  →  initialized ONCE only
                   →  value survives every function return
                   →  nobody outside can access x

Embedded use: ISR debounce, state machines, driver state tracking
```

> **Placement Tip:** "What is the difference between a local and a static local variable?" is a guaranteed embedded viva question.
> Key answer points: **lifetime** (stack vs data segment) + **persistence** + **initialization once only**.
