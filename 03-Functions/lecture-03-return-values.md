# Lecture 3 – Returning Values from Functions

---

# Until Now

Previously, your function looked like this:

```c
void function_add_numbers(int a, int b, int c)
{
    int sum = a + b + c;

    printf("%d", sum);
}
```

Notice something?

The function itself prints the answer.

```
Function

↓

Calculate

↓

Print
```

So whoever calls the function cannot use that value for anything else.

---

# New Approach

Instead of printing inside the function,

the function should only do its job.

```
Calculate

↓

Return answer

↓

Caller decides what to do
```

Maybe print it.

Maybe store it.

Maybe compare it.

Maybe send it over UART.

This makes the function much more useful.

---

# Step 1

Remove

```c
printf("%d", sum);
```

Now the function only calculates.

---

# Step 2

Return the value

```c
return sum;
```

Think of `return` as saying

> "I'm done. Here's the result."

As soon as `return` executes,

the function immediately ends and control goes back to the caller.

---

# Step 3

Change the Return Type

Earlier

```c
void function_add_numbers(...)
```

`void` means

```
Returns Nothing
```

But now

```c
return sum;
```

returns an integer.

So the function must become

```c
int function_add_numbers(...)
```

Now the compiler knows

> This function returns an integer.

---

# Complete Function

```c
int function_add_numbers(int a, int b, int c)
{
    int sum;

    sum = a + b + c;

    return sum;
}
```

Simple.

No printing.

Only calculation.

---

# Who Receives the Returned Value?

Imagine this code.

```c
int main()
{
    int returnValue;

    returnValue = function_add_numbers(10,20,30);

    printf("%d", returnValue);
}
```

Let's see what happens.

---

## Step 1

Execution starts in

```c
main()
```

---

## Step 2

Compiler reaches

```c
function_add_numbers(10,20,30);
```

Control jumps to

```
function_add_numbers()
```

---

## Step 3

Parameters receive values

```
a = 10

b = 20

c = 30
```

---

## Step 4

Function calculates

```
sum = 60
```

---

## Step 5

Compiler sees

```c
return sum;
```

So

```
60
```

is sent back.

Control immediately returns to

```c
main()
```

---

## Step 6

This line

```c
returnValue = function_add_numbers(...);
```

becomes

```c
returnValue = 60;
```

Now

```
returnValue = 60
```

---

## Step 7

Finally

```c
printf("%d", returnValue);
```

prints

```
60
```

---

# Visual Flow

```
main()

↓

function_add_numbers(10,20,30)

↓

sum = 60

↓

return 60

↓

main()

↓

returnValue = 60

↓

printf()
```

Notice

The function doesn't print anything.

It simply returns the answer.

---

# What is Caller?

The function that makes the function call.

Example

```c
main()
{
    function_add_numbers();
}
```

Here

```
main()
```

is the **Caller**.

---

# What is Callee?

The function being called.

```
function_add_numbers()
```

is the **Callee**.

Visual

```
main()

↓

calls

↓

function_add_numbers()
```

---

# Why is Returning Better Than Printing?

Suppose later you need

```
Average
```

You need the sum first.

```c
sum = function_add_numbers(a,b,c);

average = sum / 3;
```

Impossible if the function only prints.

Returning makes functions reusable.

---

# Embedded Systems Example

Imagine reading a temperature sensor.

Bad

```c
void readTemperature()
{
    printf("32");
}
```

The temperature is only printed.

You can't use it.

---

Better

```c
int readTemperature()
{
    return 32;
}
```

Now

```c
temperature = readTemperature();
```

You can

* Display it
* Compare it
* Send it over UART
* Save it in memory
* Upload it to the cloud

All because the function returned the value.

---

# What Can a Function Return?

Almost any data type.

### Integer

```c
int
```

---

### Character

```c
char
```

---

### Float

```c
float
```

---

### Long

```c
long
```

---

### Pointer

```c
int *
```

---

### Structure

```c
struct Student
```

(You'll learn this later.)

---

### Nothing

```c
void
```

---

# Important Rule

The return type must match the value you return.

Correct

```c
int add()
{
    return 10;
}
```

Correct

```c
char getLetter()
{
    return 'A';
}
```

Correct

```c
void blinkLED()
{
}
```

Incorrect

```c
void add()
{
    return 10;
}
```

❌ `void` functions cannot return a value.

---

# Updating the Function Prototype

Earlier

```c
void function_add_numbers(int, int, int);
```

Now the function returns an integer.

So the prototype must also change.

```c
int function_add_numbers(int, int, int);
```

The declaration and definition must always agree.

---

# Interview Summary

* `return` sends a value back to the caller and immediately ends the function.
* If a function returns a value, its **return type** must match that value (e.g., `int`, `char`, `float`).
* `void` functions do not return any value.
* The **caller** is the function that invokes another function; the **callee** is the function being invoked.
* Returned values can be stored in variables, used in expressions, or passed to other functions.
* Returning values makes functions reusable and keeps them focused on a single responsibility.

---

## Embedded Engineer Note

You'll see this pattern everywhere in embedded development. Functions such as:

```c
HAL_GPIO_ReadPin();      // returns pin state
HAL_ADC_GetValue();      // returns ADC reading
HAL_UART_GetState();     // returns UART status
```

don't print their results—they **return** them. Your application decides what to do with those returned values, whether it's making a decision, displaying data, or controlling hardware. This separation of responsibilities is a key principle of well-designed embedded software.
