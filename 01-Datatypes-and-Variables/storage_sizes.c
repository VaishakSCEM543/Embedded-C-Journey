/*
 * Topic   : Storage sizes, ranges, and integer overflow
 * Concept : sizeof() reveals compiler-assigned sizes; sizes vary across
 *           GCC / ARMCC / XC8 — use <stdint.h> types in embedded code
 * Learned : Overflow wraps silently — a counter overflow in a timer ISR can cause incorrect system behaviour
 */

#include <stdio.h>
#include <limits.h>

int main(void)
{
    /* sizes */
    printf("char      : %zu byte(s)\n", sizeof(char));
    printf("short     : %zu byte(s)\n", sizeof(short));
    printf("int       : %zu byte(s)\n", sizeof(int));
    printf("long      : %zu byte(s)\n", sizeof(long));
    printf("long long : %zu byte(s)\n", sizeof(long long));

    /* ranges */
    printf("\nsigned char   : %d to %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char : 0 to %u\n",   UCHAR_MAX);
    printf("signed int    : %d to %d\n",  INT_MIN,   INT_MAX);

    /* overflow wraps around — dangerous in embedded timers/counters */
    unsigned char x = 255;
    x = x + 1;
    printf("\nuchar 255 + 1 = %u  (overflow)\n", x);

    signed char y = 127;
    y = y + 1;
    printf("schar 127 + 1 = %d  (overflow)\n", y);

    return 0;
}

/*
 * OUTPUT (GCC, Windows x64):
 *   char      : 1 byte(s)
 *   short     : 2 byte(s)
 *   int       : 4 byte(s)
 *   long      : 4 byte(s)
 *   long long : 8 byte(s)
 *
 *   signed char   : -128 to 127
 *   unsigned char : 0 to 255
 *   signed int    : -2147483648 to 2147483647
 *
 *   uchar 255 + 1 = 0  (overflow)
 *   schar 127 + 1 = -128  (overflow)
 */
