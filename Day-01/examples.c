// Day-01 | Data Types and Variables
// Demonstrating all basic data types in C

#include <stdio.h>

int main()
{
    // ── INTEGER TYPES ─────────────────────────────────────────
    char          a = 'A';          // 1 byte | stores character or small number
    short         s = 30000;        // 2 bytes | short integer
    int           i = 100000;       // 4 bytes (on GCC) | general integer
    long          l = 1000000L;     // 4 bytes | long integer
    long long     ll = 9000000000LL;// 8 bytes | very large integer

    // ── UNSIGNED TYPES ────────────────────────────────────────
    unsigned char  uc = 200;        // 1 byte | 0 to 255 (no negatives)
    unsigned int   ui = 4000000000U;// 4 bytes | 0 to 4,294,967,295

    // ── FLOAT TYPES ───────────────────────────────────────────
    float  f  = 3.14f;             // 4 bytes | ~6-7 decimal digits
    double d  = 3.14159265358979;  // 8 bytes | ~15-16 decimal digits

    // ── PRINT ALL ─────────────────────────────────────────────
    printf("char          : %c  (ASCII: %d)\n", a, a);
    printf("short         : %d\n", s);
    printf("int           : %d\n", i);
    printf("long          : %ld\n", l);
    printf("long long     : %lld\n", ll);
    printf("unsigned char : %u\n", uc);
    printf("unsigned int  : %u\n", ui);
    printf("float         : %.2f\n", f);
    printf("double        : %.14lf\n", d);

    return 0;
}

/*
 * EMBEDDED NOTE:
 * In embedded systems (STM32, ESP32), use fixed-width types:
 *   uint8_t  instead of unsigned char
 *   uint16_t instead of unsigned short
 *   uint32_t instead of unsigned int
 * Include <stdint.h> to use them.
 * This ensures consistent sizes across all compilers (GCC, ARMCC, XC8).
 */
