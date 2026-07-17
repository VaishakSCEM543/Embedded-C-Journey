/* lecture 16 exercise - deref read and write using char pointer */

#include <stdio.h>

int main() {

    /* step 1 - create char variable and initialize to 100 */
    char var = 100;

    /* step 2 - print address of var */
    printf("address of var : %p \n", (void*)&var);

    /* step 3 - create pointer and store address */
    char *ptr = &var;

    /* step 4 - read operation , dereference the pointer */
    char data = *ptr;

    /* step 5 - print the data we got */
    printf("data from ptr : %d \n", data);

    /* step 6 - write operation , store 65 via pointer */
    *ptr = 65;

    /* step 7 - print var , should now be 65 */
    printf("var after write : %d \n", var);

    return 0;
}

// output after running :
// address of var : 0061FF1A
// data from ptr : 100
// var after write : 65
// worked perfectly , write via pointer updated the original var
