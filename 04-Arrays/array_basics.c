#include <stdio.h>
#include <stdint.h>

int main(void)
{
    /* Array definition: 100 data items of type uint8_t */
    uint8_t studentsAge[100];

    printf("Size of uint8_t array (100 items)  : %lu bytes\n", (unsigned long)sizeof(studentsAge));

    /* Array with uint32_t elements */
    uint32_t data[100];

    printf("Size of uint32_t array (100 items) : %lu bytes\n", (unsigned long)sizeof(data));

    /* The array name acts as a base pointer to the array */
    /* It holds the base address (address of the first element) */
    printf("Base address of studentsAge array  : %p\n", (void*)studentsAge);
    printf("Base address of data array         : %p\n", (void*)data);

    return 0;
}
