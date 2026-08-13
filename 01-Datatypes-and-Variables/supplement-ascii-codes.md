# Supplement: ASCII Codes and Character Representation

---

## 🎯 Learning Objectives

After this section, you will understand:

* What ASCII is and why it exists.
* How characters are stored in memory as numbers.
* How to use character literals (`'A'`) instead of ASCII codes directly.
* The `%c` vs `%d` format specifier distinction.
* How this connects to `char` arrays and strings.

---

## 1. What Is ASCII?

**ASCII** = American Standard Code for Information Interchange.

Developed by ANSI (the same organization that standardized C).

> ASCII encodes **128 different characters** using **7 bits**.
> Each character maps to a unique integer code.

---

## 2. Why Does ASCII Matter to a Computer?

A computer stores only numbers. It does not understand letters.

So when we want to store the word `Apple`:

```text
The machine stores:   65  112  112  108  101
Which represent:       A    p    p    l    e
```

Every character you type is stored as its ASCII code — an integer.

---

## 3. Key ASCII Values to Know

| Character | ASCII (Decimal) | Notes |
|:---------:|:---------------:|:------|
| `'A'` | 65 | Uppercase A |
| `'Z'` | 90 | Uppercase Z |
| `'a'` | 97 | Lowercase a |
| `'z'` | 122 | Lowercase z |
| `'0'` | 48 | Digit zero (not the number 0) |
| `'9'` | 57 | Digit nine |
| `' '` | 32 | Space |
| `'\n'` | 10 | Newline (Line Feed) |
| `'\t'` | 9 | Horizontal Tab |
| `'\r'` | 13 | Carriage Return |
| `'\0'` | 0 | Null terminator |

> [!TIP]
> You don't need to memorize all 128. Focus on: A=65, a=97, '0'=48, space=32, '\0'=0.
> Key pattern: `'a' - 'A' = 32` — lowercase is always 32 more than uppercase.

---

## 4. The Hard Way vs The Easy Way

### ❌ Hard Way — Using raw ASCII codes

```c
char a1 = 65;    /* A */
char a2 = 112;   /* p */
char a3 = 112;   /* p */
char a4 = 108;   /* l */
char a5 = 101;   /* e */
```

This requires you to look up the ASCII table for every character. Very tedious.

---

### ✅ Easy Way — Using character literals

```c
char a1 = 'A';
char a2 = 'p';
char a3 = 'p';
char a4 = 'l';
char a5 = 'e';
```

The compiler automatically replaces `'A'` with `65` at compile time.

> [!NOTE]
> `'A'` and `65` are **identical** to the compiler. The character literal is just a human-readable way of writing the ASCII code.

---

## 5. Printing Characters — `%c` vs `%d`

The same variable can be printed two ways:

```c
char a1 = 'A';

printf("%d", a1);   /* prints: 65  — the integer (ASCII code) */
printf("%c", a1);   /* prints: A   — the character */
```

- `%d` → treats the value as an integer, prints the number
- `%c` → treats the value as a character, prints the symbol

Both are reading the exact same memory. The **format specifier** changes how it's displayed.

---

## 6. Full Example — Printing "Apple"

```c
#include<stdio.h>

int main(void)
{
    char a1 = 'A';
    char a2 = 'p';
    char a3 = 'p';
    char a4 = 'l';
    char a5 = 'e';

    /* Print as characters */
    printf("%c%c%c%c%c\n", a1, a2, a3, a4, a5);   /* Apple */

    /* Print as integers */
    printf("%d %d %d %d %d\n", a1, a2, a3, a4, a5); /* 65 112 112 108 101 */

    return 0;
}
```

**Output:**
```
Apple
65 112 112 108 101
```

---

## 7. The Cleaner Way — Char Array (Preview)

All five lines can be replaced with one:

```c
char a[] = "Apple";
```

This stores `A p p l e \0` in memory — each character as its ASCII code, followed by the null terminator.

> This is what **strings in C** are: arrays of ASCII codes ending with `'\0'`.
> Full coverage in Module 05 — Strings.

---

## 8. Embedded C Connection

In embedded systems, UART communication sends/receives raw bytes.
When your firmware receives `0x41`, it received the character `'A'` (65 in hex = 0x41).

```c
uint8_t received_byte = 0x41;

if (received_byte == 'A')   /* 0x41 == 65 == 'A' — all the same */
{
    /* process command A */
}
```

ASCII is how serial communication, display drivers, and logging all interpret bytes as readable text.

---

## 📌 Quick Revision

```
ASCII = 128 characters, 7 bits each.

'A' == 65    'a' == 97    '0' == 48    ' ' == 32    '\0' == 0

char x = 'A';    /* compiler stores 65 — not the letter */
printf("%d", x); /* 65  — show the number  */
printf("%c", x); /* A   — show the symbol  */

'a' - 'A' = 32   ← difference between upper and lower case

char a[] = "Apple";  ← stores { 65, 112, 112, 108, 101, 0 }
```

> **Placement Tip:** `char` stores an integer (1 byte). `'A'` is just the number 65 written in a human-friendly way. This distinction is tested in output-based questions like:
> ```c
> char c = 'A' + 1;
> printf("%c", c);   /* B — because 65+1=66='B' */
> ```
