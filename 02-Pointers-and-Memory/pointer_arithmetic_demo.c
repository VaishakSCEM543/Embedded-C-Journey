/* lecture 19 - pointer arithmetic */
/* key : pAddress + 1 does NOT always add 1 to the address */
/* it adds sizeof(pointer_type) bytes */

#include <stdio.h>

long long int g_data = 0xFFFEABCD11112345;

int main(void)
{
    /* char* : +1 moves address by 1 byte */
    char *pAddress = (char*)&g_data;

    printf("char* base addr  : %p , value : %x\n", (void*)pAddress, *pAddress);

    pAddress = pAddress + 1;   /* moves 1 byte forward , since char = 1 byte */

    printf("char* after +1   : %p , value : %x\n", (void*)pAddress, *pAddress);

    /* short* : +1 moves address by 2 bytes , sizeof(short) = 2 */
    short *pAddress2 = (short*)&g_data;

    printf("short* base addr : %p , value : %x\n", (void*)pAddress2, *pAddress2);

    pAddress2 = pAddress2 + 1;   /* moves 2 bytes forward */

    printf("short* after +1  : %p , value : %x\n", (void*)pAddress2, *pAddress2);

    /* int* : +1 moves address by 4 bytes , sizeof(int) = 4 */
    int *pAddress3 = (int*)&g_data;

    printf("int*  base addr  : %p , value : %x\n", (void*)pAddress3, *pAddress3);

    pAddress3 = pAddress3 + 1;   /* moves 4 bytes forward */

    printf("int*  after +1   : %p , value : %x\n", (void*)pAddress3, *pAddress3);

    return 0;
}

// output :
// char* base addr  : 00404008 , value : 45
// char* after +1   : 00404009 , value : 23     <- moved 1 byte
// short* base addr : 00404008 , value : 2345
// short* after +1  : 0040400A , value : 1111   <- moved 2 bytes
// int*  base addr  : 00404008 , value : 11112345
// int*  after +1   : 0040400C , value : fffeabcd  <- moved 4 bytes
//
// rule : pAddress + 1 adds sizeof(pointer_type) to the address
// char*  +1 = +1 byte
// short* +1 = +2 bytes
// int*   +1 = +4 bytes
// long long* +1 = +8 bytes
