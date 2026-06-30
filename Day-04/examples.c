// Day-04 | Variable Definition Exercise
// Problem: Calculate total distance from A to C
// A to B = 160 km, B to C = 40 km

#include <stdio.h>

int main()
{
    unsigned char a_b = 160;   // Distance A→B | 1 byte | range: 0-255
    unsigned char b_c = 40;    // Distance B→C | 1 byte | range: 0-255

    printf("The total distance from point A to point C is %d", a_b + b_c);

    // Output: The total distance from point A to point C is 200

    return 0;
}

/*
 * EMBEDDED NOTE:
 * unsigned char = 1 byte = 8 bits
 * In STM32, peripheral registers are also 8/16/32-bit wide
 * Example: GPIOA->ODR is a 32-bit register
 * Choosing correct data type saves precious SRAM on microcontrollers
 */
