/*
 * math.h
 *
 * Function prototypes for math.c
 * Include this header in any file that needs to call these functions.
 *
 * Lecture 13 Exercise — Multi-file project + Typecasting
 */

#ifndef MATH_H_
#define MATH_H_

/* Add two integers — int + int = int (no overflow for small values) */
int add(int n1, int n2);

/* Subtract two integers */
int sub(int n1, int n2);

/*
 * Multiply two integers — result returned as long long int
 * because int * int can OVERFLOW for large numbers.
 * Explicit cast: (long long int)n1 * n2  → promotes before multiply
 */
long long int mul(int n1, int n2);

/*
 * Divide two integers — result returned as float
 * because int / int TRUNCATES the decimal part.
 * Explicit cast: (float)n1 / n2  → forces float division
 */
float divf(int n1, int n2);

#endif /* MATH_H_ */
