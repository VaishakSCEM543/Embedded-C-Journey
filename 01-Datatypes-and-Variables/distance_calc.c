// Write a C program to calculate and print the total distance from point A to point C.

// Given:

// Distance from A to B = 160 km
// Distance from B to C = 40 km


#include <stdio.h>

int main()
{
    unsigned char a_b =160;
    unsigned char b_c = 40;
    printf("The total distance from point A to point C is %d\n",a_b+b_c);
    printf("The total distance from point A to point C is %X\n",a_b+b_c); // This will print the value in Hexadecimal 
    printf("The total distance from point A to point C is %O\n",a_b+b_c); // This will print the value in Octal 

    return 0;
}