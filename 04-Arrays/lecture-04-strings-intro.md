# Arrays in C - Lecture 4: Strings in C (Complete Notes)

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

A **string** is a **collection (sequence) of characters** that is **terminated by a null character (`'\0'`)**.

> [!IMPORTANT]
> **Definition**
> A string = Collection of characters + Null character (`'\0'`)

The **null character** tells the compiler where the string ends.
Without the null character, C cannot determine the end of the string.

### Example
```c
"Hello"
```
This is a string because the compiler stores it as:
```text
H e l l o \0
```

---

## 2. Why is the Null Character Needed?

The null character marks the **end of the string**.
It is represented as: `'\0'`
Its ASCII value is: `0`

Just like:
* `'\n'` → New line
* `'\t'` → Tab

Similarly:
* `'\0'` → Null Character (End of String)

Without this character, string functions such as `printf()`, `strlen()`, `strcpy()`, and `strcmp()` would never know where the string ends.

---

## 3. Strings in C

Unlike C++, Java, or Python, **C does not have a dedicated string data type.**

Instead, **Strings are stored using a character array.**

```text
Character Array
        ↓
     Stores
        ↓
      String
```

---

## 4. Declaring a String

The easiest and most common way is:
```c
char message[] = "Hello";
```

### Explanation
* `char` → Data type
* `message` → Array name
* `[]` → Compiler automatically decides the array size
* `"Hello"` → String

---

## 5. How the Compiler Stores a String

When you write:
```c
char message[] = "Hello";
```
Compiler automatically stores:

| Address | Stored Value |
| ------- | ------------ |
| 1000    | H            |
| 1001    | e            |
| 1002    | l            |
| 1003    | l            |
| 1004    | o            |
| 1005    | \0           |

**Memory representation:**
```text
message
   │
   ▼
+----+----+----+----+----+----+
| H  | e  | l  | l  | o  |\0  |
+----+----+----+----+----+----+
```

Notice there are **5 characters + 1 null character = 6 bytes**.
Therefore `"Hello"` occupies **6 bytes**, NOT 5 bytes.

> [!TIP]
> **Important Point**
> You **do NOT** write the null character when using double quotes. The compiler automatically appends it.

---

## 6. Another Way to Initialize a String

You can also initialize character arrays manually.
Example:
```c
char message[] = { 'H', 'e', 'l', 'l', 'o' };
```
Looks similar... But **this is NOT a string.**

Why? Because there is **no null character**.
Memory becomes: `H e l l o` (No ending marker exists).
Therefore, this is simply a **character array**, NOT a string.

---

## 7. Making It a Proper String

To make the previous example a string, you must manually add the null character:
```c
char message[] = { 'H', 'e', 'l', 'l', 'o', '\0' };
```
Now memory becomes: `H e l l o \0` and it is a proper string.

> [!CAUTION]
> **Best Practice**
> ❌ **Avoid:** `char msg[] = {'H','e','l','l','o','\0'};`
> ✅ **Prefer:** `char msg[] = "Hello";`
> **Reasons:** Cleaner, easier, less chance of mistakes, and the compiler automatically adds `'\0'`.

---

## 8. Fixed Size Character Array

Suppose:
```c
char message[10] = "Hello";
```
* Array size = 10
* Characters stored = 5
* Null character = 1
* Remaining bytes = 4

**Memory:**
```text
+----+----+----+----+----+----+----+----+----+----+
| H  | e  | l  | l  | o  |\0  | 0  | 0  | 0  | 0  |
+----+----+----+----+----+----+----+----+----+----+
```
Unused elements become `0`, which is `'\0'`. This is called **Partial Initialization**.

---

## 9. Dynamic Array Size

If you write:
```c
char message[] = "Hello";
```
The compiler automatically calculates the required size.
`Hello` requires 5 characters + 1 null character = **6 bytes**.
Compiler creates `char message[6];` internally.

---

## 10. `sizeof()` vs `strlen()`

This is one of the most important interview questions.

### Example 1
```c
char message1[10] = "Hello";
```
* `sizeof(message1)` returns **10** because `sizeof()` returns the **total allocated memory.**
* `strlen(message1)` returns **5** because `strlen()` counts only `Hello`. It ignores `'\0'` and all remaining empty bytes.

### Example 2
```c
char message2[] = "Hello";
```
Compiler creates 6 bytes.
* `sizeof(message2)` returns **6**.
* `strlen(message2)` returns **5**.

### Comparison Table
| Expression | Returns | Reason |
| ---------- | ------- | ------ |
| `sizeof(message1)` | 10 | Entire allocated array |
| `strlen(message1)` | 5 | Characters only |
| `sizeof(message2)` | 6 | 5 characters + `'\0'` |
| `strlen(message2)` | 5 | Only actual text |

> [!WARNING]
> **Remember:**
> `sizeof()` → Counts everything including `'\0'` and unused memory.
> `strlen()` → Counts only characters before `'\0'`.

---

## 11. Where Does `strlen()` Come From?

`strlen()` is a library function. You must include the `<string.h>` header file.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char msg[] = "Hello";
    printf("%lu", (unsigned long)strlen(msg)); // Output: 5
    return 0;
}
```

---

## 12. Character vs String

One of the most confusing concepts for beginners.

### Character
* Uses **Single Quotes**: `'A'`
* Stores: Only one character.
* Consumes: **1 byte**
```text
+----+
| A  |
+----+
```

### String
* Uses **Double Quotes**: `"A"`
* Stores: `A` + `'\0'`
* Consumes: **2 bytes**
```text
+----+----+
| A  |\0  |
+----+----+
```

### Comparison
| Character | String |
| --------- | ------ |
| `'A'` | `"A"` |
| Single quotes | Double quotes |
| Single character | Collection of characters |
| 1 byte | Characters + `'\0'` |
| Stored in char variable | Stored in char array |

---

## Visual Summary

**Character:** `'A'` → 1 Byte
```text
+----+
| A  |
+----+
```

**String:** `"A"` → 2 Bytes
```text
+----+----+
| A  |\0  |
+----+----+
```

---

## Key Takeaways

* A **string** is a collection of characters terminated by the **null character (`'\0'`)**.
* C has **no built-in string data type**; strings are stored using **character arrays**.
* The compiler **automatically appends `'\0'`** when a string is initialized with double quotes.
* A character array without `'\0'` is **not a valid string**.
* Prefer `char str[] = "Hello";` over manually initializing each character.
* `sizeof()` returns the **total allocated memory**, while `strlen()` returns **only the number of characters before `'\0'`**.
* Use **single quotes (`'A'`)** for a character and **double quotes (`"A"`)** for a string.
* `"A"` occupies **2 bytes** (`'A'` + `'\0'`), whereas `'A'` occupies **1 byte**.

---

## Quick Revision (30 Seconds)

```text
String
↓
Collection of characters + '\0'

Stored using
↓
char array

Correct
char str[] = "Hello";

Wrong (Not a string)
char str[] = {'H','e','l','l','o'};

Correct
char str[] = {'H','e','l','l','o','\0'};

sizeof()
→ Total memory

strlen()
→ Characters only

'A'
→ Character (1 byte)

"A"
→ String (2 bytes: A + '\0')
```
