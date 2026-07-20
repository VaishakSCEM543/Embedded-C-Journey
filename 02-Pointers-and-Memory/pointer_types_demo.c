/* lecture 18 - effect of pointer data type on read operation */
/* key idea : pointer type decides how many bytes get fetched */

#include <stdio.h>

/* global variable - 8 bytes of data stored in hex */
/* 0xFFFEABCD11223344 = 8 bytes */
long long int g_data = 0xFFFEABCD11223344;

int main(void)
{
    /* char* pointer - should read only 1 byte from g_data */
    char *pAddress1 = (char*)&g_data;   /* cast needed , types differ */

    printf("char* read (1 byte)  : %x \n", *pAddress1);

    /* int* pointer - should read 4 bytes */
    int *pAddress2 = (int*)&g_data;

    printf("int*  read (4 bytes) : %x \n", *pAddress2);

    /* short* pointer - should read 2 bytes */
    short *pAddress3 = (short*)&g_data;

    printf("short* read (2 bytes): %x \n", *pAddress3);

    return 0;
}
