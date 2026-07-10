# Lecture 1 - Functions in C (Embedded Perspective)

---

# What is a Function?

Imagine you're working in a company.

Instead of one person doing everything,

you divide work among specialists.

```
CEO
 │
 ├── Accountant
 ├── Engineer
 ├── Designer
 └── HR
```

Each person performs one specific task.

A C function is exactly the same.

It performs **one specific task**.

Example

```
calculateSalary()

readTemperature()

turnOnLED()

sendDataUART()

displayMenu()
```

Every function should ideally have **one responsibility**.

---

# Why do we use functions?

Suppose you want to calculate the average of three numbers.

Without functions

```c
sum = a+b+c;
avg = sum/3;

...

sum = x+y+z;
avg = sum/3;

...

sum = p+q+r;
avg = sum/3;
```

Same code repeated again and again.

This is called

> Code Redundancy

---

Using functions

```c
calculateAverage(a,b,c);

calculateAverage(x,y,z);

calculateAverage(p,q,r);
```

Now the code exists only once.

Much cleaner.

---

# Advantages of Functions

### 1. Code Reuse

Write once.

Use many times.

---

### 2. Easier Debugging

If there is a bug

You only fix one function.

Not every place.

---

### 3. Modular Programming

Instead of

```
1000 lines inside main()
```

you get

```
main()

↓

readSensor()

↓

filterData()

↓

display()

↓

sendUART()
```

Much easier to understand.

---

### 4. Smaller Program

Instead of copying code

You simply call the function.

---

### 5. Abstraction

You use

```c
printf()
```

Do you know how printf works internally?

No.

You simply use it.

That is abstraction.

---

# Every executable statement must be inside a function

Legal

```c
int main()
{
    printf("Hello");
}
```

Illegal

```c
printf("Hello");
```

Compiler error.

Because executable statements must always be inside a function.

---

# What CAN exist outside functions?

Variable definitions

Example

```c
int count;
```

or

```c
int count = 10;
```

These are called

Global variables.

Perfectly legal.

---

# General Structure of a Function

```c
return_type function_name(parameters)
{
    statements;
}
```

Example

```c
void blinkLED()
{
    printf("LED ON");
}
```

Let's understand every part.

---

## Return Type

Tells what the function gives back.

Example

```c
int
```

returns an integer.

Example

```c
float
```

returns decimal.

Example

```c
char
```

returns a character.

Example

```c
void
```

returns nothing.

---

## Function Name

Choose meaningful names.

Good

```c
calculateSum()

readSensor()

displayMenu()
```

Bad

```c
abc()

fun1()

temp2()
```

---

## Parentheses

These hold the inputs.

Example

```c
add(int a,int b)
```

Inputs

```
a
b
```

---

## Curly Braces

Contain executable statements.

Everything the function does happens inside

```c
{

}
```

---

# main() is also a Function

Many beginners think

main is special.

Actually

```
main()
```

is simply another function.

It also has

Return type

Name

Parameters

Body

Exactly like every other function.

---

# Two Standard Ways to Write main()

### Method 1

```c
int main(void)
{

}
```

No inputs.

Mostly used in Embedded Systems.

---

### Method 2

```c
int main(int argc,char *argv[])
{

}
```

Used in desktop applications.

These are called

Command-line arguments.

Embedded systems rarely use them.

---

# Why int main()?

Because main returns a status code to the Operating System.

```
Application

↓

Operating System
```

After the program finishes

it returns

```
0
```

means

Success.

Anything else

```
1

2

-1

etc.
```

means

Some error.

---

# Example Function

```c
void function_add_numbers(int a,int b,int c)
{
    int sum;

    sum = a+b+c;

    printf("%d",sum);
}
```

Let's understand every part.

---

Return type

```c
void
```

Returns nothing.

---

Function name

```c
function_add_numbers
```

---

Parameters

```c
int a

int b

int c
```

Inputs received.

---

Body

```c
{
    int sum;

    sum=a+b+c;

    printf(...);
}
```

Actual work happens here.

---

# What are Parameters?

These

```c
int a

int b

int c
```

are called

Parameters

or

Formal Parameters.

They are simply local variables.

Memory is created only when the function runs.

---

# Calling a Function

Function definition

```c
void add(int a,int b,int c)
{

}
```

Calling

```c
add(10,20,30);
```

The values go inside

```
10 → a

20 → b

30 → c
```

Function executes.

---

# You Can Pass Variables Too

```c
int x=90;
int y=70;

add(x,y,50);
```

Compiler does

```
a = 90

b = 70

c = 50
```

Perfectly legal.

---

# You Can Mix Variables and Numbers

```c
int x=20;

add(x,40,100);
```

Also legal.

---

# The Compiler Warning

Suppose

```c
int main()
{
    add(10,20,30);
}
```

Later

```c
void add(int a,int b,int c)
{

}
```

Compiler complains

```
Implicit declaration of function add
```

Why?

Because when compiler reaches

```c
add(...)
```

It has never seen this function before.

It reads code from **top to bottom**.

```
Compiler

↓

main()

↓

add()

↓

end
```

When compiler reaches

```c
add()
```

it asks

> "What is add?"

It hasn't seen it yet.

So warning.

---

# Solution

Tell the compiler beforehand.

This is called

Function Prototype

or

Function Declaration.

Example

```c
void add(int,int,int);

int main()
{
    add(10,20,30);
}

void add(int a,int b,int c)
{

}
```

Now compiler already knows

```
There exists a function

named add

returns void

takes three integers
```

No warning.

---

# Function Prototype vs Function Definition

Prototype

Only tells the compiler the function exists.

```c
void add(int,int,int);
```

No body.

Only information.

---

Definition

Contains the actual implementation.

```c
void add(int a,int b,int c)
{
    printf("Hello");
}
```

---

# Real Embedded Example

Instead of writing

```c
GPIO_SetBits(...);

Delay();

GPIO_ResetBits(...);

Delay();

GPIO_SetBits(...);

Delay();
```

many times,

you write

```c
void blinkLED()
{
    GPIO_SetBits(...);

    Delay();

    GPIO_ResetBits(...);

    Delay();
}
```

Now whenever needed

```c
blinkLED();

blinkLED();

blinkLED();
```

Much cleaner.

This is exactly how STM32 HAL libraries and embedded drivers are designed.

---

# Summary (Interview Revision)

* A **function** is a reusable block of code that performs one specific task.
* Every executable statement in C must be inside a function.
* `main()` is the entry point of every C program and is itself a function.
* A function consists of a **return type**, **function name**, **parameter list**, and **body**.
* `void` means the function does not return a value.
* Parameters (formal parameters) receive input values and behave like local variables.
* A function is executed by **calling** it with appropriate arguments.
* To call a function before its definition, you should provide a **function prototype (declaration)** so the compiler knows its signature.
* Using functions improves **code reuse, modularity, readability, debugging, and maintainability**, which is why embedded software is heavily function-based.

---

## Embedded Engineer Note

This lecture is the foundation for almost everything you'll write later. STM32 HAL functions like:

```c
HAL_GPIO_WritePin();
HAL_UART_Transmit();
HAL_TIM_PWM_Start();
HAL_I2C_Master_Transmit();
```

are all just C functions. Once you're comfortable defining, declaring, and calling functions, understanding embedded libraries becomes much easier.
