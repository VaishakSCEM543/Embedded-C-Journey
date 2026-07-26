#include <stdio.h>
#include <stdint.h>

/* 
 * Function to display array elements.
 * Uses 'const' to guarantee it won't modify the array.
 * Requires the length as a separate parameter because pArray has decayed to a pointer.
 */
void displayArray(const uint8_t *pArray, uint32_t nItems)
{
    printf("Array elements: ");
    for (uint32_t i = 0; i < nItems; i++)
    {
        /* pArray[i] is identical to *(pArray + i) */
        printf("%02X ", pArray[i]);
    }
    printf("\n");
}

/*
 * Function to modify the array.
 * Notice the lack of 'const', allowing us to change the data.
 */
void modifyArray(uint8_t *pArray, uint32_t nItems)
{
    for (uint32_t i = 0; i < nItems; i++)
    {
        pArray[i] = pArray[i] + 1; // Increment each element by 1
    }
}

int main(void)
{
    uint8_t sensorData[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
    
    // Calculate the number of elements
    uint32_t length = sizeof(sensorData) / sizeof(sensorData[0]);

    printf("--- Original Array ---\n");
    displayArray(sensorData, length);

    printf("\n--- After Modification ---\n");
    modifyArray(sensorData, length);
    displayArray(sensorData, length);

    printf("\n--- Passing a Subarray (Slicing) ---\n");
    // Pass starting from the 3rd element (index 2)
    // We must also adjust the length! (length - 2)
    displayArray(&sensorData[2], length - 2);

    /* 
     * Beginner mistake demonstration (commented out):
     * If we try to use sizeof() inside a function on a pointer, it fails.
     * displayArray(sensorData, sizeof(sensorData)); // ❌ WRONG! sizeof(sensorData) here gives total bytes, not length if type > 1 byte.
     * Actually, if we just pass a pointer without calculating length properly, we get bugs.
     */

    return 0;
}
