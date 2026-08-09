# Module: Storage Classes in C – Lecture 2

# `static` Across Multiple Files — Internal Linkage and File-Level Privacy

---

## 🎯 Learning Objectives

After this lecture, you will understand:

* Why a normal global variable is accessible across all `.c` files.
* How `extern` lets one file use a variable defined in another.
* How `static` at file scope restricts access to **one `.c` file only**.
* The difference between **internal linkage** and **external linkage**.
* How `static` applies to **functions** too.
* Two separate mental models for `static`.

---

## 1. The Real Problem — Multi-File Projects

A real embedded C project looks like:

```text
Project/
├── main.c
├── uart.c
├── spi.c
├── gpio.c
└── timer.c
```

Different developers write different files. If a variable in `main.c` is a normal global, **any other file can modify it** — even if that was never intended.

---

## 2. Example Without `static`

### `main.c`
```c
#include<stdio.h>

int PrivateData = 100;

void file1_myFun1(void);

int main(void)
{
    printf("%d\n", PrivateData);   /* prints 100 */

    file1_myFun1();

    printf("%d\n", PrivateData);   /* prints 900 — corrupted! */

    return 0;
}
```

### `file1.c`
```c
extern int PrivateData;   /* "use the one defined in main.c" */

void file1_myFun1(void)
{
    PrivateData = 900;    /* silently modifies another file's data */
}
```

**Output:**
```
100
900
```

`file1.c` reached into `main.c` and changed `PrivateData`. This is the problem.

---

## 3. What `extern` Means

```c
extern int PrivateData;
```

> "Don't create a new `PrivateData`. One already exists somewhere else — use that."

### Definition vs Declaration

| | Code | Effect |
|:--|:-----|:-------|
| **Definition** | `int data = 100;` | Actually **creates** the variable in memory |
| **Declaration** | `extern int data;` | Tells the compiler "it exists elsewhere" — no memory allocated |

> [!IMPORTANT]
> A variable must be **defined exactly once**. It can be **declared** (via `extern`) in as many files as needed.

---

## 4. The Solution — `static` at File Scope

Change one line in `main.c`:

```c
// Before:
int PrivateData = 100;

// After:
static int PrivateData = 100;
```

Now `PrivateData` has **internal linkage** — it is invisible to all other source files.

```text
main.c
└── static int PrivateData   ← only main.c can see this

file1.c
└── extern int PrivateData   ← ❌ LINKER ERROR — not found
```

`file1.c` cannot find it. The linker will report an **undefined reference**.

---

## 5. Internal vs External Linkage

| Declaration | Linkage | Accessible from |
|:-----------|:--------|:----------------|
| `int x;` (global) | External | Any `.c` file via `extern` |
| `static int x;` (global) | **Internal** | **Only this `.c` file** |

> [!NOTE]
> "Internal linkage" is the technical term for this. It comes up in embedded and OS-level interviews.

---

## 6. The Two Meanings of `static` — Full Picture

This is the most important table in these two lectures:

| Declaration | Where | Effect |
|:-----------|:------|:-------|
| `int x;` inside function | Stack | Lives during function call only |
| `static int x;` inside function | Data segment | **Survives function calls** |
| `int x;` outside function | Data segment | Global — any file can access via `extern` |
| `static int x;` outside function | Data segment | **Private to this `.c` file** |

---

## 7. Mental Model — Two Separate Cases

### Case 1 — `static` inside a function

```c
void counter(void)
{
    static int count = 0;
}
```

Think: **"Remember my value between calls."**

---

### Case 2 — `static` outside a function

```c
static int uart_state = 0;
```

Think: **"Keep me private to this `.c` file."**

---

## 8. `static` Functions

`static` can also apply to functions:

```c
/* file1.c */
static void helperFunction(void)
{
    printf("I am private to file1.c\n");
}
```

`helperFunction()` **cannot be called from any other file**.

```text
static int data;         →  private variable
static void helper();    →  private function
```

Both restrict access to the current source file. Same concept, same keyword.

---

## 9. Real Embedded Example

```c
/* uart.c */

static uint8_t uart_rx_buffer[64];   /* private — nobody else should touch this */
static uint8_t uart_state = 0;       /* private state machine variable */

static void uart_process_byte(uint8_t byte);   /* private helper */

/* Public API — accessible from other files */
void UART_Init(void) { ... }
void UART_SendByte(uint8_t byte) { ... }
```

```c
/* main.c */
extern void UART_Init(void);     /* ✅ public function — accessible */
extern uint8_t uart_rx_buffer;   /* ❌ LINKER ERROR — it's static */
```

> [!TIP]
> In every professional embedded driver, you'll see `static` used exactly this way — to hide internal buffers, state variables, and helper functions from other modules. This is C's way of achieving **encapsulation**.

---

## ⚠️ Common Mistakes

| Mistake | Why It's Wrong |
|:--------|:---------------|
| Using `extern` to access a `static` global from another file | Linker error — internal linkage blocks it |
| Confusing `static` local and `static` global | Same keyword, **different effects** |
| Forgetting that `extern` only *declares*, not defines | Compiler won't allocate memory for `extern` |
| Making driver-internal variables global | Any module can accidentally corrupt them |

---

## 🎯 Interview Questions

**Q1. Why use `static` with a global variable?**
To give it internal linkage — restricting access to the current `.c` file and preventing other files from reaching it via `extern`.

**Q2. Can a `static` global variable be accessed from another `.c` file using `extern`?**
No. It has internal linkage. The linker will report "undefined reference."

**Q3. What does `extern` do?**
It declares that a variable or function is **defined elsewhere** (usually another `.c` file). It tells the compiler to not create a new definition — just use the existing one during linking.

**Q4. What is the difference between a definition and a declaration?**
A definition creates the variable and allocates memory (`int x = 5;`). A declaration just tells the compiler the variable exists elsewhere (`extern int x;`).

**Q5. Can `static` be used with functions?**
Yes. A `static` function has internal linkage — it can only be called from within the same `.c` file.

**Q6. What is internal linkage?**
When a symbol (variable or function) is restricted to its own translation unit (`.c` file). Achieved with the `static` keyword at file scope.

**Q7. Why is `static` heavily used in embedded drivers?**
To hide internal state, buffers, and helper functions from other modules. This prevents accidental corruption and provides a clean public API.

---

## 📌 Quick Revision

```
Three lines to remember:

static int count;      // INSIDE function  →  value survives function calls
static int data;       // OUTSIDE function →  private to this .c file
extern int data;       //                  →  use variable defined in another file

Key terminology:
  static global  →  internal linkage  →  file-private
  normal global  →  external linkage  →  accessible everywhere via extern

In embedded:
  static → encapsulation → clean module interfaces → professional code
```

> **Placement Tip:** "What is the difference between `static` inside and outside a function?" is a very common embedded viva question.
> Know both meanings cold: **persistence between calls** vs **file-level privacy**.
