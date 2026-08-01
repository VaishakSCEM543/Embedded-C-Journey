#include <stdio.h>

/**
 * Lecture 2 Demo: String Literals vs Character Arrays
 *
 * Key Difference:
 *   char msg[]   = "Hello";  --> array in RAM       --> MODIFIABLE
 *   char *msg    = "Hello";  --> pointer to ROM      --> READ-ONLY
 *   const char * = "Hello";  --> best practice       --> clearly read-only
 */

int main(void) {

    /* ─── 1. Character Array (RAM) ─────────────────────────────────────── */
    char msg_array[] = "Hello";

    printf("--- Character Array ---\n");
    printf("Original: %s\n", msg_array);

    msg_array[0] = 'S';  // Safe: array lives in writable RAM
    printf("After modification: %s\n\n", msg_array);

    /* ─── 2. Character Pointer — correct usage (read only) ─────────────── */
    const char *msg_ptr = "Embedded C";  // const protects against accidents

    printf("--- Character Pointer (const) ---\n");
    printf("String: %s\n\n", msg_ptr);

    /* DO NOT do this — undefined behaviour / segfault:
     *   char *bad = "Hello";
     *   bad[0] = 'S';          // Writing to ROM → crash/UB
     */

    /* ─── 3. Observing addresses ────────────────────────────────────────── */
    printf("--- Memory Addresses ---\n");
    printf("msg_array address (RAM):  %p\n", (void *)msg_array);
    printf("msg_ptr   address (ROM):  %p\n", (void *)msg_ptr);

    /*
     * On STM32:
     *   msg_array  → 0x2000xxxx  (SRAM / RAM)
     *   msg_ptr    → 0x0800xxxx  (Flash / ROM .rodata)
     *
     * On a PC both may be in RAM because the OS maps read-only pages
     * differently, but the principle is identical.
     */

    return 0;
}
