/*
 * math.c
 *
 * Function DEFINITIONS for arithmetic operations.
 *
 * Lecture 13 Exercise — Multi-file project + Typecasting
 *
 * Key typecasting concepts:
 *  - int * int = int  (OVERFLOW risk for large numbers)
 *  - (long long int)n1 * n2 → explicit cast BEFORE multiply prevents overflow
 *  - int / int = int  (decimal part TRUNCATED)
 *  - (float)n1 / n2  → explicit cast forces float division, preserves decimals
 */

#include "math.h"   /* include own header to keep prototypes in sync */

/* ------------------------------------------------------------------ */
int add(int n1, int n2)
{
    /* int + int = int — safe for normal ranges */
    return n1 + n2;
}

/* ------------------------------------------------------------------ */
int sub(int n1, int n2)
{
    return n1 - n2;
}

/* ------------------------------------------------------------------ */
long long int mul(int n1, int n2)
{
    /*
     * WITHOUT cast: n1 * n2 → int * int = int (4 bytes) — OVERFLOWS for big numbers
     * WITH cast:   (long long int)n1 * n2
     *              n1 is promoted to 8-byte FIRST, then multiplied.
     *              long long int * int = long long int → no data loss.
     */
    return (long long int)n1 * n2;
}

/* ------------------------------------------------------------------ */
float divf(int n1, int n2)
{
    /*
     * WITHOUT cast: n1 / n2 → int / int = int — decimal TRUNCATED
     *               80 / 3 = 26 (not 26.666...)
     * WITH cast:   (float)n1 / n2
     *              n1 promoted to float FIRST, then divided.
     *              float / int → compiler implicitly promotes n2 to float.
     *              Result: float → decimal preserved.
     */
    return (float)n1 / n2;
}