/*
 * Topic   : What is a Pointer? — Lecture 2
 * Concept : A pointer is a memory address, not the data itself.
 *           This file demonstrates the four operations you can
 *           perform using a pointer variable:
 *
 *             1. Read  — read the value at an address
 *             2. Write — write a value to an address
 *             3. Increment — move the pointer to the next memory location
 *             4. Decrement — move the pointer to the previous location
 *
 * Analogy : Address = house number (where)
 *           Data    = person living there (what)
 *
 * Compile : gcc pointer_demo.c -o pointer_demo
 * Run     : pointer_demo.exe
 */

#include <stdio.h>

int main(void)
{
    /* -----------------------------------------------------------
     * Setup: declare a variable and a pointer that stores its address
     * ----------------------------------------------------------- */
    int data = 25;

    /* int *p  means: p is a variable that stores the address of an int */
    int *p = &data;   /* p now POINTS TO data — p holds data's address */

    printf("=== Pointer Basics ===\n");
    printf("Value of data         : %d\n",  data);   /* the actual value */
    printf("Address of data (&data): %p\n", &data);  /* where it lives   */
    printf("Value of p (the addr) : %p\n",  p);      /* same address     */
    printf("Pointer size on this machine: %u bytes\n\n", (unsigned int)sizeof(p));

    /* -----------------------------------------------------------
     * Operation 1: READ through a pointer  (dereference with *)
     * *p  means: "go to the address stored in p, and read the value there"
     * ----------------------------------------------------------- */
    printf("=== Operation 1: READ via pointer ===\n");
    int readValue = *p;          /* dereference — go to address, get value */
    printf("*p = %d  (reading value at address %p)\n\n", readValue, p);

    /* -----------------------------------------------------------
     * Operation 2: WRITE through a pointer
     * *p = newValue  means: "go to the address in p, write newValue there"
     * ----------------------------------------------------------- */
    printf("=== Operation 2: WRITE via pointer ===\n");
    printf("data before write : %d\n", data);
    *p = 100;                    /* write 100 directly to data's address */
    printf("data after  write : %d  (changed via pointer, not by name)\n\n", data);

    /* -----------------------------------------------------------
     * Operation 3: INCREMENT the pointer
     * p++  moves p forward by sizeof(int) bytes — to the NEXT int slot
     * On most systems: int = 4 bytes, so address increases by 4
     *
     * WARNING: We only look at the address here, NOT dereference,
     *          because we haven't allocated memory at the next location.
     * ----------------------------------------------------------- */
    printf("=== Operation 3: INCREMENT the pointer ===\n");
    printf("Address before increment: %p\n", p);
    p++;                         /* move pointer to next int-sized slot */
    printf("Address after  increment: %p\n", p);
    printf("Difference = %u byte(s) — equals sizeof(int)\n\n", (unsigned int)sizeof(int));

    /* Reset p back to &data for the decrement demo */
    p = &data;

    /* -----------------------------------------------------------
     * Operation 4: DECREMENT the pointer
     * p--  moves p backward by sizeof(int) bytes
     * ----------------------------------------------------------- */
    printf("=== Operation 4: DECREMENT the pointer ===\n");
    printf("Address before decrement: %p\n", p);
    p--;                         /* move pointer to previous int-sized slot */
    printf("Address after  decrement: %p\n", p);
    printf("Difference = %u byte(s) — equals sizeof(int)\n\n", (unsigned int)sizeof(int));

    /* Reset p back to &data */
    p = &data;

    /* -----------------------------------------------------------
     * Embedded Context Demo (simulation only — not real hardware)
     * In a real STM32 project you would write:
     *
     *   #define RCC_AHB1ENR   *((volatile unsigned int *) 0x40023830)
     *   #define GPIOA_MODER   *((volatile unsigned int *) 0x40020000)
     *   #define GPIOA_ODR     *((volatile unsigned int *) 0x40020014)
     *
     *   RCC_AHB1ENR |= (1 << 0);   // Enable GPIOA clock
     *   GPIOA_MODER |= (1 << 10);  // Set PA5 as output
     *   GPIOA_ODR   |= (1 << 5);   // PA5 HIGH → LED ON
     *
     * All of that is pointer arithmetic on fixed hardware addresses.
     * This is EXACTLY what you learned today.
     * ----------------------------------------------------------- */
    printf("=== Embedded Reality Check ===\n");
    printf("Pointer p holds address : %p\n",  p);
    printf("Pointer p points to     : %d\n", *p);
    printf("This is how STM32 drivers work:\n");
    printf("  Write to an address → control hardware.\n");
    printf("  The address IS the register.\n");

    return 0;
}
