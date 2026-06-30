/*
 * Problem : Total distance A→C given A→B = 160 km, B→C = 40 km
 * Concept : Variable definition with unsigned char; value fits 0–255
 *           so no byte is wasted — same reasoning used for 8-bit sensor
 *           readings and register values on microcontrollers.
 */

#include <stdio.h>

int main(void)
{
    unsigned char a_b = 160;
    unsigned char b_c = 40;

    printf("Total distance A to C: %d km\n", a_b + b_c);   /* 200 */

    return 0;
}
