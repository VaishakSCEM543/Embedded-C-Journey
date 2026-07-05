/*
 * Topic   : char, ASCII encoding, %c vs %d, typecasting
 * Concept : char is a 1-byte integer; characters are stored as ASCII numbers.
 *           In embedded, uint8_t (= unsigned char) carries raw bytes over
 *           UART/SPI/I2C — the same principle applies.
 * Learned : 'a' - 32 = 'A' works because ASCII values are just integers — arithmetic on characters is valid C
 */

#include <stdio.h>

int main(void)
{
    char ch = 'A';
    printf("%c = %d\n", ch, ch);     /* A = 65 */

    /* char can store a number directly — identical result */
    char ch2 = 65;
    printf("%c = %d\n", ch2, ch2);   /* A = 65 */

    /* signed vs unsigned */
    signed char   sc = -50;
    unsigned char uc = 200;
    printf("signed: %d | unsigned: %u\n", sc, uc);

    /* arithmetic on ASCII values */
    printf("'a' - 32 = %c\n", 'a' - 32);   /* lowercase → uppercase */

    /* typecasting */
    int  n  = 67;
    char c  = (char) n;
    printf("(char)67 = %c\n", c);           /* C */

    return 0;
}

/*
 * OUTPUT (GCC, Windows x64):
 *   A = 65
 *   A = 65
 *   signed: -50 | unsigned: 200
 *   'a' - 32 = A
 *   (char)67 = C
 */
