/*
 * Topic   : Variable Scope — local vs global
 * Concept : Scope defines where a variable is accessible. Local variables
 *           exist only within their block {}. Global variables are accessible
 *           across all functions. If both exist, local takes priority.
 * Learned : Prefer local variables in embedded — global variables stay in RAM
 *           for the entire program lifetime, wasting memory on small MCUs.
 */

#include <stdio.h>

/* global variable — accessible in all functions below */
int score;

void function_score1(void);
void function_score2(void);

int main(void)
{
    score = 10;
    printf("main        : score = %d\n", score);   /* 10 */
    function_score1();
    function_score2();
    return 0;
}

void function_score1(void)
{
    score = 20;
    printf("function_1  : score = %d\n", score);   /* 20 */
}

void function_score2(void)
{
    score = 30;
    printf("function_2  : score = %d\n", score);   /* 30 */
}

/*
 * LOCAL vs GLOBAL — SCOPE DEMO 2:
 *
 *   int a = 2;        // global
 *   int main(void) {
 *       int a = 5;    // local — shadows the global
 *       printf("%d",a);  // prints 5, not 2
 *   }
 *
 * EMBEDDED NOTE:
 *   Global variables → stored in .data / .bss section of RAM
 *   Local variables  → stored on the stack (freed when function exits)
 *   On STM32F103 (20KB RAM), unnecessary globals directly reduce available stack.
 *   Rule: use local unless data must be shared across multiple functions.
 */
