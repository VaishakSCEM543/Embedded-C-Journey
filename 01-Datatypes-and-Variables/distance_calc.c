/*
 * Topic   : Variable definition exercise
 * Concept : unsigned char fits 0-255, saves 3 bytes vs int per variable.
 *           Same logic applies to 8-bit sensor/register values on MCUs.
 * Learned : Always match data type to actual data range — int where char
 *           fits wastes RAM; critical on MCUs with only 20KB SRAM.
 */

#include <stdio.h>

int main(void)
{
    unsigned char a_b = 160;
    unsigned char b_c = 40;

    printf("Distance A to C : %d km\n",  a_b + b_c);  /* decimal */
    printf("Distance A to C : 0x%X\n",   a_b + b_c);  /* hex     */
    printf("Distance A to C : 0%o\n",    a_b + b_c);  /* octal   */

    return 0;
}

/*
 * OUTPUT (GCC, Windows x64):
 *   Distance A to C : 200 km
 *   Distance A to C : 0xC8
 *   Distance A to C : 0310
 */