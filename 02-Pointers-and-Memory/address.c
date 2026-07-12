/*
 * Topic   : Memory Addresses — the & operator and %p
 * Concept : Every variable has a memory address. Use &var to get it.
 *           %p prints the address in hex (pointer format).
 *           Stack variables are allocated top-down — each char
 *           is 1 byte, so addresses decrease by 1 each time.
 *
 * Learned : Address size is architecture-dependent:
 *             8-bit  MCU (AVR)       → 2-byte address
 *             32-bit MCU (STM32)     → 4-byte address
 *             64-bit PC  (Windows)   → 8-byte address
 *
 *           In embedded bare-metal, hardware peripheral registers
 *           ARE memory addresses — e.g., GPIOA base = 0x40010800.
 *           Understanding &var is the first step to understanding
 *           how drivers write directly to hardware.
 *
 * Compile : gcc address.c -o address
 * Run     : address.exe  (Windows)
 */

#include <stdio.h>

int main(void)
{
    char a = 'A';
    char b = 'B';
    char c = 'C';
    char d = 'D';
    char e = 'E';
    char f = 'F';

    /* %p prints the memory address of the variable (hex format) */
    printf("Address of a: %p\n", &a);
    printf("Address of b: %p\n", &b);
    printf("Address of c: %p\n", &c);
    printf("Address of d: %p\n", &d);
    printf("Address of e: %p\n", &e);
    printf("Address of f: %p\n", &f);

    /*
     * Expected output pattern (Windows x64 — addresses decrease on stack):
     *   Address of a: 000000000061FE1F
     *   Address of b: 000000000061FE1E   ← 1 byte less (char = 1 byte)
     *   Address of c: 000000000061FE1D
     *   Address of d: 000000000061FE1C
     *   Address of e: 000000000061FE1B
     *   Address of f: 000000000061FE1A
     *
     * The exact values will differ each run (ASLR), but the
     * 1-byte difference between consecutive chars is constant.
     */

    return 0;
}
