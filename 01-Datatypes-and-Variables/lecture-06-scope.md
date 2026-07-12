# Lecture 06 — Variable Scope (Local vs Global)

> **Course Lectures 47–48** | Kiran Nayak — Microcontroller Embedded C Programming

---

## 🎯 What This Lecture Covers

| Concept | Summary |
|---|---|
| What is scope? | The region of the program where a variable is accessible |
| Local variable | Exists only inside its `{}` block — destroyed when block exits |
| Global variable | Accessible from any function — lives for the whole program |
| Shadowing | Local variable hides a global with the same name |
| Block scope | Variables inside `{}` die at the closing brace |
| Uninitialized danger | Local vars hold garbage if not initialized — **critical in embedded** |

---

## 📖 Definition

> **Scope** = the region of the program in which a variable is accessible (visible to the compiler).

---

## 🔵 Local Variables

A **local variable** is declared inside a function or a `{}` block. It:
- Exists **only within that block**
- Is **allocated on the stack** when the block is entered
- Is **destroyed (freed)** when execution leaves the block
- Is **NOT accessible** from other functions

```c
void function_score1(void)
{
    int score = 20;         // local — only visible here
    printf("%d\n", score);  // OK
}

// score is DEAD here — out of scope
```

---

## 🟢 Global Variables

A **global variable** is declared **outside all functions**, usually at the top of the file. It:
- Is accessible from **any function** in the file
- Is stored in **RAM (.data or .bss section)** for the **entire program lifetime**
- Retains its value across function calls

```c
int score;   /* global — accessible everywhere below */

void function_score1(void) { score = 20; }
void function_score2(void) { score = 30; }

int main(void) {
    score = 10;
    function_score1();  // score → 20
    function_score2();  // score → 30
}
```

---

## 🔴 Shadowing — Local Hides Global

If a local variable has the **same name** as a global, the local **shadows** (hides) the global within its scope:

```c
int a = 2;        // global

int main(void) {
    int a = 5;    // local — shadows the global
    printf("%d", a);  // prints 5, NOT 2
}
```

The global `a` still exists and is unchanged — it's just temporarily invisible.

---

## 📦 Block Scope

Variables declared inside any `{}` block (not just functions) obey scope rules:

```c
int main(void)
{
    a = 25;   // global

    {
        int my_var = 45;
        printf("inside block: %d\n", my_var);  // 45 — OK
    }
    // my_var is DEAD here

    int my_var;              // NEW uninitialized local variable
    my_var = my_var + 10;   // ⚠️ UNDEFINED BEHAVIOR — garbage value!
    printf("after block: %d\n", my_var);   // unpredictable
}
```

> The two `my_var` variables are **completely different**. The second one is a fresh (uninitialized) variable. They just happen to share a name.

---

## ⚠️ The Uninitialized Variable Trap

```c
int my_var;              // declared but NOT initialized
my_var = my_var + 10;   // garbage + 10 = UNDEFINED
```

**Why this is dangerous:**
- A local variable holds **whatever bytes are currently on the stack** at that address
- This value changes every run (depends on previous function calls, OS, etc.)
- **In embedded:** can be leftover register or peripheral values → **hard-to-debug firmware bugs**

**Rule: Always initialize local variables at definition.**
```c
int my_var = 0;   // ✅ safe
// not
int my_var;       // ❌ dangerous
```

---

## 📊 Local vs Global — Quick Comparison

| Property | Local Variable | Global Variable |
|---|---|---|
| **Declared** | Inside `{}` block | Outside all functions |
| **Lifetime** | Until `}` is reached | Entire program |
| **Storage** | Stack | RAM (.data / .bss) |
| **Accessible from** | Own block only | All functions in file |
| **Default value** | ❌ Garbage (undefined) | ✅ Zero-initialized |
| **Embedded preference** | ✅ Preferred | ⚠️ Use sparingly |

---

## 🛠️ Embedded Perspective

> ⚠️ **Global variables waste RAM on small MCUs.**

On an **STM32F103** (Blue Pill) you have only **20 KB of RAM** total.

| Variable type | Stored in | Freed when? |
|---|---|---|
| Global | `.data` / `.bss` | **Never** — lives for entire program |
| Local | Stack | When function/block exits |

**Rule:** Use global variables **only when data must be shared across multiple functions**. Otherwise, keep variables local.

```c
// ✅ Embedded-correct style
void read_sensor(void)
{
    uint16_t raw_adc = ADC_read();   // local — freed after return
    process(raw_adc);
}

// ⚠️ Avoid this if raw_adc is only needed inside one function
uint16_t raw_adc;   // global — wastes RAM forever
```

---

## 🎓 Interview Questions

**Q1: What is the scope of a variable in C?**
> The scope of a variable is the region of the program where that variable is accessible. A variable declared inside a `{}` block is a local variable — accessible only within that block. A variable declared outside all functions is a global variable — accessible from any function.

**Q2: What happens to a local variable when the function returns?**
> The local variable is destroyed — its memory on the stack is freed. Any pointer to it becomes a dangling pointer (undefined behavior).

**Q3: What is variable shadowing?**
> When a local variable has the same name as a global variable, the local variable "shadows" (hides) the global within its scope. The compiler uses the innermost (most local) variable of that name.

**Q4: Why should global variables be avoided in embedded systems?**
> Global variables are stored in RAM for the entire program lifetime. On small MCUs (e.g., STM32 with 20 KB RAM), unnecessary globals directly reduce the available stack space and can cause stack overflow. Local variables should be preferred — they live only as long as needed.

**Q5: What does an uninitialized local variable contain?**
> It contains whatever garbage data was previously at that memory address on the stack. This is undefined behavior — the value is unpredictable and changes between runs. Always initialize local variables.
