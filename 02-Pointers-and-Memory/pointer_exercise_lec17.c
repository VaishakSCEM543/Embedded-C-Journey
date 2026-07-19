/* lecture 17 exercise - pointer read and write using char pointer */
/* variable name : data , pointer name : pAddress (p prefix = pointer) */

#include <stdio.h>

int main(void)
{
    /* step 1 - create char variable , initialize to 100 */
    char data = 100;

    /* step 2 - print value and address of the variable */
    printf("value of data : %d\n", data);
    printf("address of data : %p\n", (void*)&data);

    /* step 3 - create pointer variable , store address of data */
    /* data is char so &data is char* , so pointer type is char* */
    /* p prefix in pAddress means it is a pointer variable */
    char *pAddress = &data;

    printf("pAddress holds : %p\n", (void*)pAddress);

    return 0;
}
