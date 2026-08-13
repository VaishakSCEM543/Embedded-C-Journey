# Module: Storage Classes in C – Lecture 4

# `extern` — Extending Visibility Across Files

---

## 🎯 What This Lecture Covers

`extern` is the final storage class specifier to understand after `static`.
Where `static` **restricts** visibility to one file, `extern` **extends** visibility across files.

---

## 1. What `extern` Does

> `extern` is used to access a global variable (or function) that is **defined in another file**.

```c
/* main.c — defines the variable */
int globalData = 100;

/* file1.c — accesses it from another file */
extern int globalData;
```

`extern` tells the compiler:

> "Don't create a new `globalData`. One already exists somewhere else — use that."

---

## 2. `extern` and Functions

When calling a function defined in another file, `extern` is **implied by default**.

```c
/* Both of these are equivalent declarations */
extern void myFunction(void);   /* explicit extern */
void myFunction(void);          /* extern is implied — same thing */
```

> [!NOTE]
> For functions, you don't need to write `extern` — the compiler assumes it. This is unlike variables where you must explicitly write `extern` to reference an external definition.

---

## 3. When Is `extern` Relevant?

`extern` only makes sense in **multi-file projects**.

```text
Single file project   →  extern is never needed
Multi-file project    →  extern lets one file use another's globals
```

```text
main.c         file1.c         file2.c
  │               │               │
  │  int count    │               │
  │    = 0;       │               │
  │               │  extern int   │  extern int
  │               │  count;       │  count;
  │               │               │
  └───────────────┴───────────────┘
         all three share one `count`
```

---

## 4. `extern` vs `static` — The Contrast

This is the key insight connecting Lectures 2, 3, and 4:

| Keyword | Effect | Direction |
|:--------|:-------|:----------|
| `static` (global) | Restricts to current file only | **Inward** — hides from others |
| `extern` | Extends access from another file | **Outward** — exposes to others |

```c
/* uart.c */
static int uart_state;          /* private  — only uart.c can use */
int uart_tx_count;              /* public   — other files can use via extern */
```

```c
/* main.c */
extern int uart_tx_count;       /* ✅ works — it has external linkage */
extern int uart_state;          /* ❌ linker error — it's static */
```

---

## 5. `extern` Extends Visibility

> "`extern` is used to **extend the visibility** of a function or variable."

Normal global variable:

```c
int count = 0;    /* external linkage by default */
```

This is already visible to other files — they just need to declare it with `extern`.

`static` global variable:

```c
static int count = 0;    /* internal linkage — extern can't reach this */
```

`extern` cannot bypass `static`. Internal linkage is final.

---

## 6. Complete Multi-File Example

### `main.c`
```c
#include <stdio.h>

int sharedCount = 0;          /* defined here — external linkage */

void file1_increment(void);   /* declared — extern is implied */

int main(void)
{
    printf("Before: %d\n", sharedCount);   /* 0 */
    file1_increment();
    printf("After : %d\n", sharedCount);   /* 1 */
    return 0;
}
```

### `file1.c`
```c
extern int sharedCount;       /* use the one from main.c */

void file1_increment(void)
{
    sharedCount++;
}
```

**Output:**
```
Before: 0
After : 1
```

---

## 7. Definition vs Declaration — Final Summary

| | Code | Memory allocated? |
|:--|:-----|:-----------------:|
| **Definition** | `int count = 0;` | ✅ Yes |
| **Declaration** | `extern int count;` | ❌ No |

> [!IMPORTANT]
> A variable must be **defined exactly once** across all files. It can be **declared** with `extern` in as many files as needed.
>
> If you write `extern int count;` in 10 files but never define `int count;` anywhere, the linker gives "undefined reference."

---

## 8. Complete `static` vs `extern` Summary

Your storage class picture is now complete:

```
static int x;         inside function  →  persists between calls
static int x;         outside function →  private to this .c file
static void f(void);  outside function →  private to this .c file

extern int x;         outside function →  use x defined in another file
extern void f(void);  outside function →  use f defined in another file (optional for functions)
```

---

## 🎯 Interview Questions

**Q1. What does `extern` do?**
It declares that a variable or function is defined in another translation unit (source file), allowing the current file to access it.

**Q2. Is `extern` required when calling a function from another file?**
No. For functions, external linkage is the default. A plain prototype (`void foo(void);`) is sufficient.

**Q3. When does `extern` make sense?**
Only in multi-file projects. In a single-file program, `extern` is never needed.

**Q4. Can `extern` access a `static` global from another file?**
No. `static` gives internal linkage — `extern` cannot bypass that. The linker will give "undefined reference."

**Q5. What is the difference between `extern` and `static` at file scope?**
`static` restricts visibility to the current file (internal linkage). `extern` extends visibility — it lets another file access a variable/function defined elsewhere (external linkage).

---

## 📌 Quick Revision

```
extern
  ↓
"This is defined somewhere else — let me use it."

Relevant only in multi-file projects.

For variables   → must write extern explicitly
For functions   → extern is implied (optional)

extern cannot bypass static (internal linkage is final).

Storage class summary — complete:
  auto          →  default for local variables
  static local  →  persists between calls
  static global →  file-private (internal linkage)
  extern        →  cross-file access (external linkage)
```
