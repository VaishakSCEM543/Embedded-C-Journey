/*
 * Topic   : char and unsigned char — range calculation
 * Concept : signed char uses 1 bit for sign (MSB), 7 bits for magnitude in
 *           2's complement → range -128 to 127.
 *           unsigned char uses all 8 bits for magnitude → range 0 to 255.
 * Learned : Negative numbers are NOT stored directly — they are stored in
 *           2's complement form. e.g. -25 = 0xE7 in memory.
 */

#include <stdio.h>

int main(void)
{
    /* signed char: MSB is sign bit, 7 bits for magnitude */
    signed char sc_max =  127;   /* 0 111 1111 — highest positive */
    signed char sc_min = -128;   /* 1 000 0000 — lowest negative  */

    /* unsigned char: all 8 bits for magnitude, no sign bit */
    unsigned char uc_max = 255;  /* 1111 1111 */
    unsigned char uc_min = 0;    /* 0000 0000 */

    printf("signed char   : %d to %d\n", sc_min, sc_max);
    printf("unsigned char : %u to %u\n", uc_min, uc_max);

    /* 2's complement demo: -25 stored as 0xE7 */
    signed char neg = -25;
    printf("-25 in hex    : 0x%X\n", (unsigned char)neg);   /* prints E7 */

    /* what happens at the boundary */
    signed char overflow = 127;
    overflow = overflow + 1;     /* wraps to -128 */
    printf("127 + 1       : %d  (overflow)\n", overflow);

    return 0;
}

/*
 * OUTPUT (GCC, Windows x64):
 *   signed char   : -128 to 127
 *   unsigned char : 0 to 255
 *   -25 in hex    : 0xE7
 *   127 + 1       : -128  (overflow)
 */
