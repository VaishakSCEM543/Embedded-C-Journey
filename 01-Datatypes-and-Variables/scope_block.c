/*
 * Topic   : Block scope and uninitialized variable behavior
 * Concept : Variables declared inside {} exist ONLY within that block.
 *           Once execution leaves the block, the variable dies.
 *           A new variable with the same name declared after the block is
 *           a completely different variable — uninitialized, holds garbage.
 * Learned : Always initialize variables. An uninitialized local variable
 *           holds whatever was in that memory — unpredictable in embedded.
 */

#include <stdio.h>

int a;   /* global — lives for entire program */

int main(void)
{
    a = 25;

    {
        /* this block creates its own local scope */
        int my_var = 45;
        printf("001 my_var (inside block) : %d\n", my_var);   /* 45 */
        printf("002 a (global)            : %d\n", a);         /* 25 */
    }
    /* my_var from above block is now DEAD — out of scope */

    int my_var;              /* NEW local variable, UNINITIALIZED */
    my_var = my_var + 10;   /* garbage value + 10 = unpredictable! */
    printf("003 my_var (uninitialized+10): %d\n", my_var);  /* undefined */

    return 0;
}

/*
 * OUTPUT (GCC, Windows x64):
 *   001 my_var (inside block) : 45
 *   002 a (global)            : 25
 *   003 my_var (uninitialized+10): <garbage>   ← changes every run
 *
 * EMBEDDED NOTE:
 *   On MCUs, uninitialized variables can contain leftover register/stack
 *   values from previous operations — causes hard-to-debug firmware bugs.
 *   Rule: ALWAYS initialize variables at definition.
 *     int my_var = 0;   not   int my_var;
 */


 /* So actually saying about Local variables and global
variables local variables are like for example you take up for for loop so where you define 
int I and that int I is actually limited to that particular loop whenever I come out of that
loop that I A variable that is known to the compiler out of when I come out of the loop But 
global variable is like if you want to use a variable multiple times in a function so instead
of defining it every time in a function I define Once in a global section so that I can use 
it whenever it is required     */