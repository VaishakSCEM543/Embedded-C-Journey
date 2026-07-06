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
