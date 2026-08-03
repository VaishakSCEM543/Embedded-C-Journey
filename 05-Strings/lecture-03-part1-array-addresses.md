# Module: Strings in C – Lecture 3, Part 1

# Understanding Array Addresses in Memory

---

## 🎯 Learning Objectives

After this part, you should be able to:

* Print the address of an array and its first element.
* Explain why `msg1`, `&msg1`, and `&msg1[0]` print the **same address**.
* Understand what "array decay" means.
* Know why an **array name is not a variable**.
* Describe the memory layout of a character array.

---

## 📖 What I Learned Today

### 1. Setting Up — Printing an Array's Address

Consider:

```c
char msg1[] = "Hello";

printf("msg1     = %p\n", msg1);        // array name (decays to pointer)
printf("&msg1    = %p\n", &msg1);       // address of the array itself
printf("&msg1[0] = %p\n", &msg1[0]);   // address of the first element
```

**Output (example):**

```
msg1     = 0x2001FFDA
&msg1    = 0x2001FFDA
&msg1[0] = 0x2001FFDA
```

All three print **the same address**. This confuses most beginners.

---

### 2. Why Do All Three Print the Same Address?

#### `msg1` — Array Name (Decay)

In most expressions, the **array name decays into a pointer** to its first element.

```
msg1  →  pointer to  →  msg1[0]  →  address = 0x2001FFDA
```

The array name `msg1` **itself is not stored anywhere** in memory. It is not a variable. The compiler replaces it with the address of the first element.

---

#### `&msg1[0]` — Address of First Element

This is the most explicit form.

```c
&msg1[0]  →  address of the element at index 0  →  0x2001FFDA
```

This is identical to what `msg1` decays to.

---

#### `&msg1` — Address of the Array Object

This takes the address of the **entire array** as a single object.

```
&msg1  →  address of the whole array  →  0x2001FFDA
```

An array starts at its first byte, so the address is **numerically the same**.

> [!IMPORTANT]
> **All three are numerically equal — but they are NOT the same type.**
>
> | Expression | Type | Meaning |
> |:-----------|:-----|:--------|
> | `msg1` | `char *` | Pointer to first element |
> | `&msg1[0]` | `char *` | Pointer to first element (explicit) |
> | `&msg1` | `char (*)[6]` | Pointer to the whole array |
>
> The difference shows up in pointer arithmetic: `&msg1 + 1` jumps by the **entire array size**, not by 1 byte.

---

### 3. Memory Layout of `char msg1[] = "Hello"`

```
Address       Content
─────────────────────
0x2001FFDA  │  'H'  │  ← msg1 / &msg1 / &msg1[0]  (all point here)
0x2001FFDB  │  'e'  │
0x2001FFDC  │  'l'  │
0x2001FFDD  │  'l'  │
0x2001FFDE  │  'o'  │
0x2001FFDF  │  '\0' │
─────────────────────
```

6 consecutive bytes in RAM. No gaps.

---

### 4. Array Name is NOT a Variable

> [!CAUTION]
> You **cannot** assign to an array name.
>
> ```c
> char msg1[] = "Hello";
> char msg2[] = "World";
>
> msg1 = msg2;   // ❌ ERROR — array name is not an l-value
> ```
>
> Unlike a pointer, `msg1` has no storage of its own. It is a **compile-time constant** representing the starting address of the array.

A pointer, by contrast, IS a variable:

```c
char *ptr = msg1;   // ✅ OK — ptr stores the address
ptr = msg2;         // ✅ OK — ptr can point to something else
```

---

### 5. Array Decay — When and Where

Array decay (array → pointer to first element) happens in:

| Situation | Example |
|:----------|:--------|
| Passing to a function | `printStr(msg1)` |
| Assigning to a pointer | `char *p = msg1` |
| Using in an expression | `msg1 + 2` |

Array decay does **NOT** happen with:

| Situation | Example |
|:----------|:--------|
| `sizeof` operator | `sizeof(msg1)` returns **6**, not pointer size |
| `&` operator | `&msg1` gives pointer-to-array type |

---

## ⚠️ Common Mistakes

| Mistake | Why It's Wrong |
|:--------|:---------------|
| Thinking `&msg1` and `msg1` are identical types | Same value, **different types** |
| `msg1 = msg2` | Array name is not assignable |
| `sizeof(msg1)` returns pointer size | It returns the full array size (6 bytes) |
| Thinking `&msg1 + 1` moves by 1 byte | It moves by `sizeof(msg1)` = 6 bytes |

---

## 🎯 Interview Questions

**Q1. What does `msg1` represent when used in an expression?**
The address of its first element (`&msg1[0]`). The array name decays to a pointer to its first element.

**Q2. Are `msg1`, `&msg1`, and `&msg1[0]` the same?**
Numerically yes — they print the same address. But their **types** are different. `msg1` and `&msg1[0]` are `char *`. `&msg1` is `char (*)[6]` — a pointer to the whole array.

**Q3. What happens when you do `&msg1 + 1`?**
The pointer advances by the size of the entire array (6 bytes for `"Hello"`), not by 1 byte.

**Q4. Can you assign a new value to an array name?**
No. Array names are not l-values. They cannot appear on the left side of an assignment.

**Q5. When does array decay NOT happen?**
When used with `sizeof()` or the `&` operator.

**Q6. What is the type of `&msg1`?**
`char (*)[6]` — a pointer to an array of 6 characters.

---

## ⚡ Quick Revision

```
char msg1[] = "Hello";

msg1       →  char *        →  address of first element
&msg1[0]   →  char *        →  address of first element (explicit)
&msg1      →  char (*)[6]   →  address of the whole array object

All three = same numeric value = 0x2001FFDA (example)

Array name is NOT a variable — cannot assign to it.

sizeof(msg1) = 6   (full array, not pointer size — decay does NOT happen)
&msg1 + 1 jumps by 6 bytes (whole array), not 1 byte
```

> **Placement Tip:** The question "What is the difference between `arr`, `&arr`, and `&arr[0]`?" is a classic C interview trap. The answer always comes down to **types**, not values.
