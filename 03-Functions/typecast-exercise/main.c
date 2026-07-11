/*
 * main.c
 *
 * Tests the arithmetic functions from math.c
 * Demonstrates IMPLICIT and EXPLICIT typecasting.
 *
 * Lecture 13 Exercise — Multi-file project + Typecasting
 *
 * Compile: gcc main.c math.c -o math
 * Run:     math.exe  (Windows)
 */

#include <stdio.h>
#include "math.h"   /* user-defined header → double quotes, NOT angle brackets */

int main()
{
    /* ---------------------------------------------------------------
     * 1. ADDITION — int + int = int
     *    0x0fff1111 + 0x0fff1110 = 0x1ffe2221
     *    Result EXCEEDS int range? No — still fits. Printed as hex.
     * --------------------------------------------------------------- */
    printf("ADD : %x\n", add(0x0fff1111, 0x0fff1110));

    /* ---------------------------------------------------------------
     * 2. SUBTRACTION — int - int = int
     * --------------------------------------------------------------- */
    printf("SUB : %d\n", sub(0x0fff1111, 0x000f1111));

    /* ---------------------------------------------------------------
     * 3. MULTIPLICATION — with EXPLICIT cast to long long int
     *    Without cast: int * int = int → OVERFLOW for big numbers
     *    With cast:    (long long int)n1 * n2 → 8-byte result, no loss
     *
     *    Windows GCC format specifier for long long: %I64X (hex)
     *    Linux GCC format specifier:                 %llX
     * --------------------------------------------------------------- */
    printf("MUL : %I64X\n", mul(0x0fff1111, 0x0fff1111));

    /* ---------------------------------------------------------------
     * 4. DIVISION — with EXPLICIT cast to float
     *    Without cast: int / int = int → 80/3 = 26 (decimal LOST)
     *    With cast:    (float)n1 / n2  → 80/3 = 26.666... (decimal preserved)
     * --------------------------------------------------------------- */
    printf("DIV : %f\n", divf(80, 3));

    /* ---------------------------------------------------------------
     * 5. IMPLICIT CASTING DEMO (from lecture)
     *    Compiler treats integer constants as 'int' (4 bytes) by default.
     *    Storing int into unsigned char → compiler TRUNCATES to 1 byte.
     *    This causes a warning — implicit casting with info loss!
     * --------------------------------------------------------------- */
    unsigned char data = (unsigned char)(0x87 + 0x65);  /* explicit cast → no warning */
    printf("IMPLICIT CAST (unsigned char): 0x%X\n", data);

    return 0;
}