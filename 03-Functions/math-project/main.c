/*
 * main.c — Lecture 04: Multi-file Project with Header Files
 * Tests all arithmetic functions from math.c.
 * main.c is the CALLER. It only needs math.h — not math.c internals.
 *
 * Compile: gcc main.c math.c -o math.exe -Wall
 */

#include <stdio.h>
#include "math.h"   /* user-defined header → DOUBLE QUOTES (not angle brackets) */

int main(void)
{
    /* 0x0FFF1111 = 268,369,169 decimal */
    printf("Add : %d\n",    math_add(0x0FFF1111, 0x0FFF1111));
    printf("Sub : %d\n",    math_sub(0x0FFF1111, 0x000F1111));

    /* Windows MinGW: %I64X  |  Linux GCC: %llX */
    printf("Mul : %I64X\n", math_mul(0x0FFF1111, 0x0FFF1111));

    /* 100 / 8 → 12 without cast, 12.500000 with (float) cast */
    printf("Div : %f\n",    math_div(100, 8));

    return 0;
}
