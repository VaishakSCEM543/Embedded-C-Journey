#include <stdio.h>
#include <stdint.h>

int main(void) {
    // 1. Array initialization
    // Initializing the first 3 elements; the remaining 7 will automatically be 0.
    uint8_t someData[10] = {0xff, 0xff, 0xff}; 

    printf("--- Array Initialization ---\n");
    for(uint32_t i = 0; i < 10; i++) {
        printf("%x\t", someData[i]);
    }
    printf("\n\n");

    // 2. Read and Write using pointer manipulation vs Array Indexing
    printf("--- Array Read and Write ---\n");
    
    // Changing the 2nd element (index 1) using pointer dereferencing
    *(someData + 1) = 0x9;
    
    // Changing the 3rd element (index 2) using array indexing (shorthand)
    someData[2] = 0x33;

    printf("After modification:\n");
    for(uint32_t i = 0; i < 10; i++) {
        printf("%x\t", someData[i]);
    }
    printf("\n\n");

    // 3. Variable Length Array (VLA) - C99 standard
    printf("--- Variable Length Array (VLA) ---\n");
    int len = 5;
    int vlaArray[len]; // Size determined at runtime by variable 'len'
    
    for(int i = 0; i < len; i++) {
        vlaArray[i] = i * 10;
        printf("vlaArray[%d] = %d\n", i, vlaArray[i]);
    }

    return 0;
}
