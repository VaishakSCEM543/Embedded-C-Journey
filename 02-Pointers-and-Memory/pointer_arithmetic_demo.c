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

    return 0;
}
