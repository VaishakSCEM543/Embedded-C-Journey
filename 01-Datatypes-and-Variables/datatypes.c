/*
 * Topic   : C Data Types — size, range, signed vs unsigned
 * Concept : Each type maps to a fixed memory size; choosing correctly
 *           matters in embedded where RAM is limited (e.g. 20KB on STM32F103)
 * Learned : In embedded, prefer uint8_t/uint16_t/uint32_t over char/int — sizes are guaranteed across all compilers
 */

#include <stdio.h>

int main(void)
{
    char          a  = 'A';
    short         s  = 30000;
    int           i  = 100000;
    long          l  = 1000000L;
    long long     ll = 9000000000LL;
    unsigned char uc = 200;           /* 0–255, no sign bit wasted */
    float         f  = 3.14f;
    double        d  = 3.14159265358979;

    printf("char      : %c  (%d)\n",  a, a);
    printf("short     : %d\n",  s);
    printf("int       : %d\n",  i);
    printf("long      : %ld\n", l);
    printf("long long : %lld\n", ll);
    printf("uchar     : %u\n",  uc);
    printf("float     : %.2f\n", f);
    printf("double    : %.14f\n", d);

    return 0;
}

/*
 * OUTPUT (GCC, Windows x64):
 *   char      : A  (65)
 *   short     : 30000
 *   int       : 100000
 *   long      : 1000000
 *   long long : 9000000000
 *   uchar     : 200
 *   float     : 3.14
 *   double    : 3.14159265358979
 */
