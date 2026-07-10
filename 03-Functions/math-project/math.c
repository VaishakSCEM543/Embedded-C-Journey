/*
 * math.c — Lecture 04: Multi-file Project with Header Files
 * Function DEFINITIONS for arithmetic operations.
 *
 * Compile: gcc main.c math.c -o math.exe -Wall
 */

#include "math.h"

int math_add(int n1, int n2)
{
    return n1 + n2;
}

int math_sub(int n1, int n2)
{
    return n1 - n2;
}

long long int math_mul(int n1, int n2)
{
    /* EXPLICIT CAST: (long long int)n1 promotes to 8-byte BEFORE multiply */
    /* Without cast: int * int = int → upper 4 bytes LOST for large numbers */
    return (long long int)n1 * n2;
}

float math_div(int n1, int n2)
{
    /* EXPLICIT CAST: (float)n1 promotes to float BEFORE divide */
    /* Without cast: int / int = int → decimal part TRUNCATED (100/8 = 12, not 12.5) */
    return (float)n1 / n2;
}
