// Day-02 | Storage Sizes and Ranges
// Demonstrating sizeof() and data type ranges

#include <stdio.h>
#include <limits.h>    // gives access to range constants like CHAR_MAX, INT_MAX

int main()
{
    // ── SIZES USING sizeof() ──────────────────────────────────
    printf("=== STORAGE SIZES ===\n");
    printf("char      : %zu byte(s)\n", sizeof(char));
    printf("short     : %zu byte(s)\n", sizeof(short));
    printf("int       : %zu byte(s)\n", sizeof(int));
    printf("long      : %zu byte(s)\n", sizeof(long));
    printf("long long : %zu byte(s)\n", sizeof(long long));
    printf("float     : %zu byte(s)\n", sizeof(float));
    printf("double    : %zu byte(s)\n", sizeof(double));

    printf("\n=== SIGNED RANGES ===\n");
    printf("signed char   : %d to %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("signed short  : %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("signed int    : %d to %d\n", INT_MIN, INT_MAX);
    printf("signed long   : %ld to %ld\n", LONG_MIN, LONG_MAX);

    printf("\n=== UNSIGNED RANGES ===\n");
    printf("unsigned char   : 0 to %u\n", UCHAR_MAX);
    printf("unsigned short  : 0 to %u\n", USHRT_MAX);
    printf("unsigned int    : 0 to %u\n", UINT_MAX);
    printf("unsigned long   : 0 to %lu\n", ULONG_MAX);

    // ── OVERFLOW DEMO ─────────────────────────────────────────
    printf("\n=== OVERFLOW DEMO ===\n");
    unsigned char x = 255;
    x = x + 1;             // 255 + 1 = 256 → overflows → wraps to 0
    printf("unsigned char 255 + 1 = %u (overflow!)\n", x);

    signed char y = 127;
    y = y + 1;              // 127 + 1 = 128 → overflows → wraps to -128
    printf("signed char 127 + 1 = %d (overflow!)\n", y);

    return 0;
}

/*
 * EMBEDDED NOTE:
 * On STM32 (ARMCC/GCC-ARM):
 *   sizeof(int)  = 4 bytes
 *   sizeof(long) = 4 bytes
 *
 * On PIC (XC8):
 *   sizeof(int)  = 2 bytes   ← DIFFERENT!
 *   sizeof(long) = 4 bytes
 *
 * FIX: Use <stdint.h> types:
 *   uint8_t  = always 1 byte
 *   uint16_t = always 2 bytes
 *   uint32_t = always 4 bytes
 *
 * Overflow in embedded = dangerous!
 * Example: A timer counter overflowing can cause incorrect timing.
 */
