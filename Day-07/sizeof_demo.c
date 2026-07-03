/*
 * Topic   : sizeof() operator — compiler-assigned sizes of data types
 * Concept : sizeof() returns the actual size in bytes your compiler gives
 *           each type. int and long sizes vary across GCC / ARMCC / XC8.
 * Learned : Never assume int = 4 bytes in embedded code. Always verify
 *           with sizeof() or use fixed-width types from <stdint.h>.
 */

#include <stdio.h>

int main(void)
{
    printf("signed char      : %zu byte(s)\n", sizeof(signed char));
    printf("unsigned char    : %zu byte(s)\n", sizeof(unsigned char));

    printf("signed short     : %zu byte(s)\n", sizeof(signed short));
    printf("unsigned short   : %zu byte(s)\n", sizeof(unsigned short));

    printf("signed int       : %zu byte(s)\n", sizeof(signed int));
    printf("unsigned int     : %zu byte(s)\n", sizeof(unsigned int));

    printf("signed long      : %zu byte(s)\n", sizeof(signed long));
    printf("unsigned long    : %zu byte(s)\n", sizeof(unsigned long));

    printf("signed long long : %zu byte(s)\n", sizeof(signed long long));
    printf("unsigned long long: %zu byte(s)\n", sizeof(unsigned long long));

    return 0;
}

/*
 * GCC output (this machine):
 *   char=1  short=2  int=4  long=4  long long=8
 *
 * XC8 (PIC microcontroller):
 *   char=1  short=2  int=2  long=4  long long=8   ← int differs!
 *
 * Fix: use <stdint.h>
 *   uint8_t=1  uint16_t=2  uint32_t=4  uint64_t=8  (always)
 */
