/* lecture 16 exercise - deref read and write using char pointer */

#include <stdio.h>

int main() {

    /* step 1 - create char variable and initialize to 100 */
    char var = 100;

    /* step 2 - print address of var */
    printf("address of var : %p \n", (void*)&var);

    /* step 3 - create pointer and store address */
    // char *ptr = &var;

    return 0;
}
