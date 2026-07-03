/*
 * Topic   : short int — range calculation, signed vs unsigned
 * Concept : short = 2 bytes = 16 bits. Signed uses 1 bit for sign,
 *           15 bits for magnitude. Always 2 bytes across all compilers.
 * Learned : When data exceeds 255 (e.g. 12-bit ADC: 0–4095), use
 *           unsigned short / uint16_t — char would overflow silently.
 */

#include <stdio.h>

int main(void)
{
    signed short   ss_max =  32767;
    signed short   ss_min = -32768;
    unsigned short us_max =  65535;

    printf("signed short   : %d to %d\n", ss_min, ss_max);
    printf("unsigned short : 0 to %u\n",  us_max);

    /* -25 in short = 0xFFE7 (2's complement, 16-bit wide) */
    signed short neg = -25;
    printf("-25 in hex     : 0x%X\n", (unsigned short)neg);   /* FFE7 */

    /* overflow demo */
    signed short overflow = 32767;
    overflow = overflow + 1;     /* wraps to -32768 */
    printf("32767 + 1      : %d  (overflow)\n", overflow);

    return 0;
}
