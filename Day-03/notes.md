# Day-03 — Char Data Type in Detail
**Date:** 2026-06-30
**Lecture:** Lecture-03 | Datatypes & Variables Section
**Status:** ✅ Complete

---

## 🧠 Concepts Learned

### 1. `char` — What It Really Is

`char` is a **1-byte integer type** that can store:
- A **small number** (0–255 or -128 to 127)
- A **character** (via ASCII encoding)

> Internally, **every character is just a number**. The computer stores `'A'` as `65`.

---

### 2. Signed char vs Unsigned char

| Type | Size | Range | Use case |
|------|------|-------|----------|
| `signed char` | 1 byte | -128 to 127 | When you need negative small integers |
| `unsigned char` | 1 byte | 0 to 255 | When storing byte data, sensor values, ASCII |
| `char` (plain) | 1 byte | Compiler decides | Avoid in embedded — ambiguous |

> ⚠️ **`char` without signed/unsigned is compiler-dependent.** Always be explicit in embedded code.

---

### 3. ASCII — How Characters Are Stored

**ASCII (American Standard Code for Information Interchange)** maps characters to numbers:

| Character | ASCII Value |
|-----------|------------|
| `'A'` | 65 |
| `'B'` | 66 |
| `'Z'` | 90 |
| `'a'` | 97 |
| `'z'` | 122 |
| `'0'` | 48 |
| `'9'` | 57 |
| `' '` (space) | 32 |
| `'\n'` (newline) | 10 |
| `'\0'` (null) | 0 |

**Key insight:** `'A' + 1 = 'B'` works in C because they're just integers underneath.

---

### 4. Printing `char` — `%c` vs `%d`

The **same variable** can be printed two ways:

```c
char ch = 'A';
printf("%c", ch);   // prints: A       (as character)
printf("%d", ch);   // prints: 65      (as integer / ASCII value)
```

- `%c` → interprets the stored number as an ASCII character
- `%d` → prints the raw integer value

---

### 5. `char` Can Store Numbers Directly

```c
char x = 65;          // stores the number 65
printf("%c", x);       // prints: A   (65 is ASCII for 'A')
printf("%d", x);       // prints: 65
```

Both `char x = 65;` and `char x = 'A';` store **the exact same thing** in memory.

---

### 6. Typecasting Basics with `char`

**Typecasting** = explicitly converting one type to another.

```c
int num = 66;
char ch = (char) num;     // cast int to char
printf("%c", ch);          // prints: B  (ASCII 66 = 'B')
```

```c
char ch = 'C';
int num = (int) ch;       // cast char to int
printf("%d", num);         // prints: 67 (ASCII of 'C')
```

The **parentheses with a type** = typecast operator.

---

## 🔌 Embedded Relevance

### `char` / `uint8_t` is the most used type in embedded:

| Use Case | Example |
|----------|---------|
| **UART byte transmission** | Each byte sent over UART is a `uint8_t` |
| **Register value** | `uint8_t reg_val = 0x3A;` |
| **Buffers / Arrays** | `uint8_t rx_buffer[64];` |
| **ASCII command parsing** | `if(rx_byte == 'S') { start(); }` |
| **I2C / SPI data** | Protocol data is always 8-bit bytes |

### Real Example:
```c
// UART receive and check command
uint8_t received_byte = UART_ReadByte();

if(received_byte == 'S') {
    Start_Motor();
} else if(received_byte == 'X') {
    Stop_Motor();
}
// The byte 'S' is stored as 83 internally
```

### ASCII in Embedded Protocols:
```c
// Sending a number as ASCII over UART (common in AT commands)
uint8_t digit = 5;
uint8_t ascii_digit = digit + '0';   // 5 + 48 = 53 = ASCII '5'
UART_Transmit(ascii_digit);
```

---

## 🔑 Key Learnings
1. `char` is a 1-byte integer — it stores numbers, not literally characters
2. Characters are stored as **ASCII values** internally
3. `%c` prints the character, `%d` prints the ASCII number
4. Always use `signed char` or `unsigned char` explicitly in embedded
5. Typecasting converts between types — the bits in memory may change
6. `'A' = 65`, `'a' = 97`, `'0' = 48` — memorize these key ASCII values

---

## 📊 Streak
- Day 3 ✅
- No Zero Days: Active 🔥
