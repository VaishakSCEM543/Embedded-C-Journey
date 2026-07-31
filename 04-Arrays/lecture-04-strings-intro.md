# Arrays in C - Lecture 4: Strings in C (Character Arrays)

> [!NOTE]
> **Difficulty:** 🟢 Beginner

## Learning Objectives

After completing this lecture, you should be able to:
* Define what a string is in C.
* Understand the critical role of the **null character (`'\0'`)**.
* Differentiate between how C stores strings vs other languages.
* Initialize character arrays correctly as strings.
* Understand the difference between `sizeof()` and `strlen()`.
* Distinguish a single character from a string literal.

---

## 1. What is a String?

A **string** is a **collection (sequence) of characters** that **ends with a null character (`'\0'`)**.

> [!IMPORTANT]
> **Definition:**
> A string = Characters + `'\0'`

The **null character** tells the compiler where the string ends.
* Null character representation: `'\0'`
* ASCII value of `'\0'` = **0**

Example:
```c
"Hello"
```
This is a string because it automatically ends with `'\0'`.

---

## 2. Why Do We Need a Null Character?

Without a null character, the compiler doesn't know where the string ends.

Example:
```text
Hello??????
```
How many letters belong to the string? The compiler cannot know without a marker.

With a null character:
```text
H e l l o \0
```
Now the compiler knows the string ends exactly after **o**.

---

## 3. Strings in C

Unlike C++, Java, or Python...
**C has NO built-in string data type.**

Instead, C stores strings using a **character array**.
Example:
```c
char msg[] = "Hello";
```
Here:
* `char` → data type
* `msg` → array name
* `"Hello"` → string literal

---

## 4. How a String is Stored in Memory

```c
char msg[] = "Hello";
```

**Memory Representation:**
```text
Address     Value
1000        'H'
1001        'e'
1002        'l'
1003        'l'
1004        'o'
1005        '\0'
```

Notice that there are **5 characters**, but memory uses **6 bytes**. The extra byte is allocated for the `'\0'`.

---

## 5. The Compiler Automatically Adds `'\0'`

When writing:
```c
char msg[] = "Hello";
```
The compiler actually stores: `H e l l o '\0'`

> [!TIP]
> You **do not** write the null character yourself when using double quotes. The compiler inserts it automatically!

---

## 6. Manual Initialization (The Wrong Way)

Instead of double quotes, you could write:
```c
char msg[] = { 'H', 'e', 'l', 'l', 'o' };
```
> [!WARNING]
> This is **NOT** a string! Why? Because there is no `'\0'`. 
> C treats it as **just an array of characters**. If you try to print it using `%s`, it will print garbage values until it accidentally hits a `0` in memory.

---

## 7. Correct Manual Initialization

If you initialize manually, you must add the null terminator:
```c
char msg[] = { 'H', 'e', 'l', 'l', 'o', '\0' };
```
Now it becomes a proper string.

---

## 8. Fixed Size Character Array

Example:
```c
char msg[10] = "Hello";
```

**Memory:**
```text
+---+---+---+---+---+----+---+---+---+---+
| H | e | l | l | o | \0 | 0 | 0 | 0 | 0 |
+---+---+---+---+---+----+---+---+---+---+
```
Only the first 6 bytes are used. The remaining bytes are initialized to **0** (which happens to be `'\0'`). This is called **partial initialization**.

---

## 9. Dynamic Array Size

Instead of writing `char msg[10] = "Hello";`, we usually write:
```c
char msg[] = "Hello";
```
The compiler automatically counts characters.
`Hello = 5 letters + '\0' = Total 6 bytes`. So the compiler creates `char msg[6];` internally.

---

## 10. `sizeof()` vs `strlen()`

Example:
```c
char msg1[10] = "Hello";
char msg2[] = "Hello";
```

### `sizeof()`
* `sizeof(msg1)` → **10** (Because the array size is explicitly 10).
* `sizeof(msg2)` → **6** (Because compiler created `Hello + '\0'`).

### `strlen()`
* `strlen(msg1)` → **5** (Counts only characters).
* `strlen(msg2)` → **5** (Still counts only characters, ignoring `'\0'`).

| Function | What it Counts |
| -------- | -------------- |
| `sizeof()` | Entire allocated memory size in bytes |
| `strlen()` | Only characters before the `'\0'` |

---

## 11. String Library

To use `strlen()`, you must include `<string.h>`:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char msg[] = "Hello";
    printf("%d", strlen(msg)); // Output: 5
    return 0;
}
```

---

## 12. Character vs String (Crucial Difference)

This is one of the most important concepts for beginners to grasp.

### Character (`'A'`)
* Uses **single quotes**
* Stores only one character
* Occupies **1 byte**
```text
+---+
| A |
+---+
```

### String (`"A"`)
* Uses **double quotes**
* Stores `A` + `'\0'`
* Occupies **2 bytes**
```text
+---+----+
| A | \0 |
+---+----+
```

> [!CAUTION]
> Never mix them up! `'A'` is an integer value representing ASCII 65. `"A"` is a memory address pointing to a character array.

---

## Important Interview Points

**Q1. What is a string?**
> A string is a sequence of characters terminated by a null character (`'\0'`).

**Q2. Why is `'\0'` necessary?**
> It marks the end of the string so C functions know where to stop reading.

**Q3. Does `"Hello"` occupy 5 bytes?**
> No. It occupies **6 bytes** (`H e l l o \0`).

**Q4. Which is a string?**
> `"A"` ✔ String (Double quotes)
> `'A'` ✘ Character (Single quotes)

**Q5. Which header contains `strlen()`?**
> `#include <string.h>`

**Q6. Difference between `sizeof()` and `strlen()`?**
> * `sizeof()` → Total allocated memory (including `'\0'` and unused bytes in the array).
> * `strlen()` → Number of characters before `'\0'`.

---

## Key Takeaways

* A string is a sequence of characters ending with `'\0'`.
* C stores strings using **character arrays**.
* The compiler automatically appends `'\0'` when using string literals (`"..."`).
* Manual character array initialization must include `'\0'` to be treated as a string.
* `sizeof()` returns allocated memory size, while `strlen()` returns only the number of characters.
* `'A'` is a **character** (single quotes, 1 byte); `"A"` is a **string** (double quotes, 2 bytes including `'\0'`).
