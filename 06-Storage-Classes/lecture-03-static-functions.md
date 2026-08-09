# Module: Storage Classes in C – Lecture 3

# `static` Functions — File-Level Privacy for Functions

---

## 🎯 What This Lecture Covers

Lecture 2 showed that `static` makes a **variable** private to a `.c` file.
Lecture 3 shows that `static` does the **exact same thing for functions**.

> This is not a new concept — it's the same idea applied to functions.

---

## 1. Normal Function — External Linkage by Default

```c
/* main.c */
void changeSystemClock(int clock)
{
    /* changes system clock */
}
```

Because this is a normal function, **any other `.c` file** can call it.

```c
/* file1.c */
void changeSystemClock(int);   /* declaration — extern is implied */

void file1_myFun1(void)
{
    changeSystemClock(0);      /* ✅ works — external linkage */
}
```

> [!NOTE]
> For functions, `extern` is **implied by default**. Writing:
> ```c
> extern void changeSystemClock(int);
> ```
> is equivalent to:
> ```c
> void changeSystemClock(int);
> ```
> Both are just declarations. The function definition lives elsewhere.

---

## 2. Making It Private — `static` Function

```c
/* main.c */
static void changeSystemClock(int clock)
{
    /* only main.c can call this */
}
```

Now `changeSystemClock()` has **internal linkage**.

```text
main.c
└── static changeSystemClock()
           │
           ├── main.c functions  →  ✅ Can call
           └── file1.c           →  ❌ Cannot call
```

If `file1.c` tries:

```c
void changeSystemClock(int);

void file1_myFun1(void)
{
    changeSystemClock(0);   /* ❌ linker error: undefined reference */
}
```

The linker cannot find it because `static` hides it from other translation units.

---

## 3. Why Is This Useful?

In any real embedded project:

```text
main.c
uart.c
spi.c
gpio.c
timer.c
```

Each `.c` file has:
- **Public functions** — the API for other modules to use
- **Private helpers** — internal functions that nobody else should call

```c
/* uart.c */

/* Private — internal helper, not for other modules */
static void configure_uart_clock(void)
{
    /* ... */
}

/* Public API — intentionally accessible to other files */
void UART_Init(void)
{
    configure_uart_clock();   /* ✅ same file — OK */
}
```

```c
/* spi.c — cannot call configure_uart_clock() */
configure_uart_clock();   /* ❌ linker error */
```

> [!TIP]
> This is C's version of **encapsulation** — the same concept as `private` in C++/Java, achieved with the `static` keyword.

---

## 4. The Complete `static` Picture

```text
                    static
                       │
          ┌────────────┴────────────┐
          │                         │
    Inside function            Outside function
          │                         │
          ↓                         ↓
  "Remember my value           "Keep me private
   between calls"               to this .c file"
   (Lecture 1)                  (Lectures 2 & 3)
```

---

## 5. All Three `static` Situations

### ① Normal local variable
```c
void fun(void)
{
    int count = 0;
}
```
- Scope: function | Lifetime: function call only | Value lost on return

---

### ② Static local variable
```c
void fun(void)
{
    static int count = 0;
}
```
- Scope: function | Lifetime: **entire program** | Value **persists between calls**

---

### ③ Static file-scope variable or function
```c
static int data = 0;

static void helper(void) { }
```
- Access: **this `.c` file only** | Lifetime: entire program | Internal linkage

---

## 6. `static` vs Normal — Side-by-Side

| Declaration | Linkage | Who Can Access |
|:-----------|:--------|:---------------|
| `void myFun(void);` | External | Any `.c` file via declaration |
| `static void myFun(void);` | **Internal** | **Only this `.c` file** |
| `int data;` (global) | External | Any `.c` file via `extern` |
| `static int data;` (global) | **Internal** | **Only this `.c` file** |

---

## 🎯 Interview Questions

**Q1. Can `static` be used with functions?**
Yes. A `static` function has internal linkage and can only be called from within the same `.c` file.

**Q2. What happens if another file tries to call a static function?**
The linker gives an "undefined reference" error — the function is invisible to other translation units.

**Q3. Is `extern` required when declaring a function from another file?**
No. For normal (externally linked) functions, `extern` is implicit. A plain prototype `void foo(void);` is enough.

**Q4. Can `extern` bypass a static function?**
No. `extern` cannot make a static function visible outside its source file. Static = internal linkage, period.

**Q5. Name a real embedded use case for static functions.**
Internal UART clock configuration, SPI CS toggle helpers, GPIO init helpers — any function that is an implementation detail of a module and not part of its public API.

---

## 📌 Quick Revision

```
static function  →  internal linkage  →  private to this .c file

Normal function  →  external linkage  →  any file can call via declaration

extern on normal function = optional (it's the default)
extern on static function = impossible (still can't access it)

Embedded pattern:
  static void helper()    ← private helper
  void Module_Init()      ← public API

Storage class summary:
  static inside function   →  persists between calls
  static outside function  →  private to .c file (variable OR function)
  extern                   →  "it's defined elsewhere, use it"
```

> **Placement Tip:** When asked "what are the uses of `static` in C?" — give all three:
> 1. Local variable — persists between calls
> 2. Global variable — file-private (internal linkage)
> 3. Function — file-private (internal linkage)
>
> Most candidates only know #1. Knowing all three puts you ahead.
