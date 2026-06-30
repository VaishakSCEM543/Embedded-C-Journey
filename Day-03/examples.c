// Day-03 | Char Data Type in Detail
// Demonstrating signed/unsigned char, ASCII, %c vs %d, and typecasting

#include <stdio.h>

int main()
{
    // ── CHAR STORING A CHARACTER ──────────────────────────────
    char ch = 'A';
    printf("=== char storing character ===\n");
    printf("char ch = 'A'\n");
    printf("  Printed as %%c : %c\n", ch);    // prints: A
    printf("  Printed as %%d : %d\n", ch);    // prints: 65  (ASCII value)

    // ── CHAR STORING A NUMBER ─────────────────────────────────
    char ch2 = 66;
    printf("\n=== char storing number 66 ===\n");
    printf("char ch2 = 66\n");
    printf("  Printed as %%c : %c\n", ch2);   // prints: B
    printf("  Printed as %%d : %d\n", ch2);   // prints: 66

    // ── SIGNED vs UNSIGNED CHAR ───────────────────────────────
    signed char   sc =  -50;
    unsigned char uc =   200;
    printf("\n=== signed vs unsigned char ===\n");
    printf("signed char   sc = -50  → %d\n", sc);
    printf("unsigned char uc = 200  → %u\n", uc);

    // ── ASCII TABLE DEMO ──────────────────────────────────────
    printf("\n=== ASCII values ===\n");
    printf("'A' = %d\n", 'A');   // 65
    printf("'a' = %d\n", 'a');   // 97
    printf("'0' = %d\n", '0');   // 48
    printf("'Z' = %d\n", 'Z');   // 90

    // ── ARITHMETIC ON CHAR (ASCII TRICK) ─────────────────────
    printf("\n=== arithmetic on char ===\n");
    char letter = 'A';
    printf("'A' + 1 = %c\n", letter + 1);    // B
    printf("'A' + 2 = %c\n", letter + 2);    // C
    printf("'a' - 32 = %c\n", 'a' - 32);     // A  (lowercase to uppercase)

    // ── TYPECASTING ───────────────────────────────────────────
    printf("\n=== typecasting ===\n");
    int  num = 67;
    char casted = (char) num;                 // int → char
    printf("(char) 67 printed as %%c : %c\n", casted);    // C
    printf("(char) 67 printed as %%d : %d\n", casted);    // 67

    char c = 'D';
    int back = (int) c;                       // char → int
    printf("(int) 'D' = %d\n", back);         // 68

    return 0;
}

/*
 * EMBEDDED NOTE:
 * - In UART communication, data is transferred byte by byte (uint8_t)
 * - Each byte could be an ASCII character for text protocols
 * - Or a raw binary value for binary protocols
 *
 * ASCII trick in embedded:
 *   uint8_t digit = adc_value % 10;         // get last digit (0-9)
 *   uint8_t ascii  = digit + '0';           // convert to ASCII (48-57)
 *   HAL_UART_Transmit(&huart1, &ascii, 1, 100);  // send over UART
 *
 * Always use unsigned char / uint8_t for raw byte data in embedded.
 * Use signed char only when you need negative small integers.
 */
