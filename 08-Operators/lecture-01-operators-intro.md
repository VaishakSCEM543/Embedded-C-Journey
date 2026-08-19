# Module: Operators in C – Lecture 1

# Operators, Precedence, and Associativity

---

## 🎯 Learning Objectives

After this lecture, you will understand:

* What an operator is and what operands are.
* The three types of operators: unary, binary, ternary.
* The major operator categories in C.
* What **operator precedence** means and why it matters.
* What **associativity** resolves and when it kicks in.
* How parentheses override both.

---

## 1. What Is an Operator?

> An **operator** is a symbol that tells the compiler to perform some operation on one or more **operands**.

```c
a + b
```

- `a`, `b` → **operands**
- `+` → **operator**

---

## 2. Types Based on Number of Operands

| Type | Operands | Example | Also called |
|:-----|:--------:|:--------|:------------|
| **Unary** | 1 | `++a` | Increment/Decrement |
| **Binary** | 2 | `a + b` | Arithmetic, Relational, Logical... |
| **Ternary** | 3 | `a ? b : c` | **Conditional operator** |

> [!IMPORTANT]
> The ternary operator `? :` is also called the **conditional operator**. This is a guaranteed interview terminology question.

---

## 3. Major Operator Categories in C

1. Arithmetic operators
2. Increment / Decrement operators
3. Relational operators
4. Logical operators
5. Bitwise operators
6. Assignment operators
7. Conditional (ternary) operator

We cover them one by one across lectures.

---

## 4. Arithmetic Operators

| Operator | Operation | Example | Result |
|:--------:|:----------|:--------|:------:|
| `+` | Addition | `3 + 4` | `7` |
| `-` | Subtraction | `10 - 3` | `7` |
| `*` | Multiplication | `3 * 4` | `12` |
| `/` | Division | `14 / 4` | `3` ⚠️ |
| `%` | Modulus (remainder) | `14 % 4` | `2` |

> [!WARNING]
> Integer division truncates — `14 / 4` gives `3`, NOT `3.5`. Both operands must be `float`/`double` to get a decimal result.

### Modulus — `%`
```c
int a = 14, b = 4;
printf("%d", a % b);   /* 2 — remainder of 14/4 */
```

Modulus is extremely useful in embedded C for:
- Ring buffer index wrapping: `index = (index + 1) % BUFFER_SIZE`
- Even/odd check: `n % 2 == 0`

---

## 5. Operator Precedence

> **Precedence decides which operator gets priority when grouping an expression.**

```c
2 + 3 * 4
```

A beginner reads left-to-right: `(2+3)*4 = 20` ❌

C uses precedence: `*` > `+`, so:

```
2 + (3 * 4)
= 2 + 12
= 14   ✅
```

---

## 6. Parentheses Override Precedence

```c
2 + 3 * 4      →  14    (multiplication first)
(2 + 3) * 4    →  20    (parentheses force addition first)
```

> [!TIP]
> **Practical rule:** Don't try to memorize the full precedence table. In embedded C, when expressions involve registers, masks, and shifts — use parentheses explicitly. They make intent clear and prevent bugs.

---

## 7. Associativity — When Precedence Isn't Enough

Associativity matters when **two operators have the same precedence**.

### Example
```c
20 / 2 * 5
```

`/` and `*` have **equal precedence**. Precedence alone can't decide the order.

**Associativity for `*` and `/`:** Left → Right

```
(20 / 2) * 5
= 10 * 5
= 50   ✅
```

NOT:
```
20 / (2 * 5) = 2   ❌
```

### Another example
```c
10 - 3 + 2
```

`+` and `-` have equal precedence, Left → Right associativity:

```
(10 - 3) + 2
= 7 + 2
= 9   ✅
```

---

## 8. The Evaluation Order Mental Model

```
① Parentheses         →  explicit grouping, always first
        ↓
② Precedence          →  which operator binds tighter?
        ↓
③ Associativity       →  left-to-right or right-to-left?
        ↓
④ Result
```

---

## 9. Precedence vs Associativity — Side by Side

| Concept | Question it answers | Example |
|:--------|:--------------------|:--------|
| **Precedence** | Which operator has priority? | `*` before `+` in `2 + 3 * 4` |
| **Associativity** | How to group same-precedence operators? | `(20/2)*5` not `20/(2*5)` |
| **Parentheses** | How to override everything? | `(2+3)*4 = 20` |

---

## 10. ⚠️ Important Nuance for Interviews

> **Precedence determines grouping, NOT necessarily the order of execution.**

For simple arithmetic this distinction doesn't matter. But it becomes critical when you study:
- `&&` and `||` (short-circuit evaluation)
- `++` / `--` (side effects)
- Function call arguments
- `volatile` variables

**Precedence and actual evaluation order are not always the same thing in C.**

---

## ⚠️ Common Mistakes

| Mistake | Reality |
|:--------|:--------|
| `2 + 3 * 4 = 20` | ❌ Correct answer is 14 (`*` before `+`) |
| `14 / 4 = 3.5` | ❌ Integer division → 3 (truncated) |
| `20 / 2 * 5 = 2` | ❌ Left-to-right → `(20/2)*5 = 50` |
| "Precedence = execution order" | ❌ Precedence = grouping, not always execution order |

---

## 🎯 Interview Questions

**Q1. What is an operator in C?**
A symbol that tells the compiler to perform an operation on one or more operands.

**Q2. What is the difference between unary and binary operators?**
Unary needs 1 operand (`++a`). Binary needs 2 operands (`a + b`).

**Q3. What is the ternary operator? Another name for it?**
`condition ? expr1 : expr2`. Also called the **conditional operator**.

**Q4. What is `2 + 3 * 4` in C?**
`14`. Multiplication has higher precedence than addition — evaluated as `2 + (3*4)`.

**Q5. What does associativity resolve?**
When two operators have the same precedence, associativity determines the grouping direction (left-to-right or right-to-left).

**Q6. What is `20 / 2 * 5`?**
`50`. `/` and `*` have equal precedence and left-to-right associativity → `(20/2)*5`.

**Q7. How do you override normal precedence?**
Use parentheses. `(2 + 3) * 4 = 20`.

---

## 📌 Quick Revision

```
Operator    →  symbol performing an operation
Unary       →  1 operand    ++a
Binary      →  2 operands   a + b
Ternary     →  3 operands   a ? b : c  (also: conditional operator)

Precedence  →  which operator binds tighter?  (* > +)
Associativity →  same-precedence grouping direction (/ * → left to right)
Parentheses →  override everything

2 + 3 * 4       =  14   (* before +)
(2 + 3) * 4     =  20   (parentheses first)
20 / 2 * 5      =  50   (left to right)
14 / 4          =  3    (integer division truncates)
14 % 4          =  2    (remainder)
```

> **Placement Tip:** Output-based questions on precedence and associativity are extremely common.
> Always ask yourself: "What is the grouping here?" before computing.
