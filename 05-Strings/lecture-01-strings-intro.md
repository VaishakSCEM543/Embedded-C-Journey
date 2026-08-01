# Module: Strings in C – Lecture 1

# What is a String? Null Character, sizeof() vs strlen()

---

## 🎯 Learning Objectives

After this lecture, you should be able to:

* Define what a **string** is in C.
* Understand the critical role of the **null character (`'\0'`)**.
* Differentiate between how C stores strings vs other languages.
* Initialize character arrays correctly as strings.
* Understand the difference between `sizeof()` and `strlen()`.
* Distinguish a single **character** (`'A'`) from a **string** (`"A"`).

---

## 📖 What I Learned Today

### 1. What is a String?

A **string** is a **collection (sequence) of characters** that is **terminated by a null character (`'\0'`)**.

> [!IMPORTANT]
> **Definition:** String = Collection of characters + Null character (`'\0'`)
>
> Without the null character, C **cannot** determine where the string ends.

```
"Hello"  →  H | e | l | l | o | \0
```

---

### 2. Why is the Null Character Needed?

The null character marks the **end of the string**.

```c
'\0'      // Null character — ASCII value = 0
'\n'      // New line
'\t'      // Tab
```

Without `'\0'`, functions like `printf()`, `strlen()`, `strcpy()`, and `strcmp()` would never know where the string ends and keep reading garbage memory.

---

### 3. Strings in C — No Built-in Type

Unlike C++, Java, and Python, **C has no dedicated string data type.**

Instead, strings are stored using a **character array**.

```c
char message[] = "Hello";
```

The compiler automatically adds `'\0'` at the end.

---

### 4. How the Compiler Stores a String

```c
char message[] = "Hello";
```

Memory layout:

```
+----+----+----+----+----+----+
| H  | e  | l  | l  | o  |\0  |
+----+----+----+----+----+----+
1000  1001  1002  1003  1004  1005
```

> [!NOTE]
> `"Hello"` = 5 characters + 1 null character = **6 bytes**, not 5.

---

### 5. A Character Array Without `'\0'` is NOT a String

```c
// ❌ NOT a string — no null character
char message[] = {'H', 'e', 'l', 'l', 'o'};

// ✅ A proper string — null character added manually
char message[] = {'H', 'e', 'l', 'l', 'o', '\0'};

// ✅ Best practice — compiler adds '\0' automatically
char message[] = "Hello";
```

---

### 6. Fixed Size Array — Partial Initialization

```c
char message[10] = "Hello";
```

Memory layout:

```
+----+----+----+----+----+----+----+----+----+----+
| H  | e  | l  | l  | o  |\0  | 0  | 0  | 0  | 0  |
+----+----+----+----+----+----+----+----+----+----+
```

Unused elements are automatically zero-filled (which is `'\0'`).

---

### 7. `sizeof()` vs `strlen()` — Most Important Interview Topic

| Function | What It Returns | Includes `'\0'`? |
|:---------|:----------------|:-----------------|
| `sizeof()` | Total **allocated** memory | ✅ Yes |
| `strlen()` | Number of **characters** only | ❌ No |

```c
char message1[10] = "Hello";
char message2[]   = "Hello";

sizeof(message1) → 10   // entire allocated array
strlen(message1) → 5    // only 'H','e','l','l','o'

sizeof(message2) → 6    // 5 chars + '\0'
strlen(message2) → 5    // only 'H','e','l','l','o'
```

> [!TIP]
> `strlen()` requires `#include <string.h>`. It counts until the first `'\0'` — nothing more.

---

### 8. Character vs String — Easiest Mistake

| | Character | String |
|:--|:----------|:-------|
| Quotes | Single `'A'` | Double `"A"` |
| Memory | 1 byte | 2 bytes (`'A'` + `'\0'`) |
| Storage | `char` variable | `char` array |

```c
char ch  = 'A';     // 1 byte:  | A |
char str[] = "A";   // 2 bytes: | A | \0 |
```

> [!CAUTION]
> `'A'` and `"A"` are **NOT** the same. One is a character, the other is a 2-byte string.

---

## ⚠️ Common Mistakes

| Mistake | Why It's Wrong |
|:--------|:---------------|
| `char msg[] = {'H','e','l','l','o'};` | No `'\0'` — not a valid string |
| Thinking `"Hello"` is 5 bytes | It's **6 bytes** (5 chars + `'\0'`) |
| Using `sizeof()` to get string length | Returns full array size, not char count |
| Confusing `'A'` with `"A"` | Different memory size and type |

---

## 🎯 Interview Questions

**Q1. What is a string in C?**
A collection of characters stored in a character array, terminated by the null character `'\0'`.

**Q2. Does C have a built-in string data type?**
No. Strings in C are implemented as character arrays with a null terminator.

**Q3. Difference between `sizeof()` and `strlen()`?**
`sizeof()` returns the total allocated memory of the array (including `'\0'` and any unused bytes). `strlen()` counts only the printable characters before the first `'\0'`.

**Q4. How many bytes does `"Hello"` take?**
6 bytes — 5 characters plus the null terminator `'\0'`.

**Q5. Difference between `'A'` and `"A"`?**
`'A'` is a single character (1 byte). `"A"` is a string (2 bytes: `'A'` + `'\0'`).

---

## ⚡ 30-Second Revision

```
String = Characters + '\0'
C has no string type → use char array
char msg[] = "Hello"  → 6 bytes  (compiler adds '\0')
{'H','e','l','l','o'} → NOT a string (no '\0')

sizeof() → total allocated memory  (includes '\0')
strlen() → characters only         (stops at '\0')

'A' → 1 byte (character)
"A" → 2 bytes (string: A + \0)
```

> **Placement Tip:** The `sizeof()` vs `strlen()` difference and the `'A'` vs `"A"` distinction are extremely common interview questions. Always explain memory in bytes with diagrams — it shows depth.
