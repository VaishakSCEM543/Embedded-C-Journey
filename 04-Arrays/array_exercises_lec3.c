#include <stdio.h>
#include <stdint.h>

/* 
 * 1. Print all elements of an integer array
 */
void printArray(const int32_t *arr, uint32_t len) {
    printf("Array: ");
    for(uint32_t i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*
 * 2. Calculate the sum of an array
 */
int32_t sumArray(const int32_t *arr, uint32_t len) {
    int32_t sum = 0;
    for(uint32_t i = 0; i < len; i++) {
        sum += arr[i];
    }
    return sum;
}

/*
 * 3. Find the maximum value in an array
 */
int32_t maxArray(const int32_t *arr, uint32_t len) {
    if(len == 0) return 0; // Handle empty array case
    
    int32_t max = arr[0];
    for(uint32_t i = 1; i < len; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/*
 * 4. Print the array in reverse order
 */
void reversePrintArray(const int32_t *arr, uint32_t len) {
    printf("Reversed: ");
    if(len == 0) return;
    
    for(int32_t i = (int32_t)len - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*
 * 5. Swap the contents of two arrays (up to the size of the smaller array)
 */
void swapArrays(int32_t *arr1, uint32_t len1, int32_t *arr2, uint32_t len2) {
    // Find the smaller length to avoid out-of-bounds access
    uint32_t minLen = (len1 < len2) ? len1 : len2;
    
    for(uint32_t i = 0; i < minLen; i++) {
        int32_t temp = arr1[i];
        arr1[i] = arr2[i];
        arr2[i] = temp;
    }
}

int main(void) {
    int32_t dataA[] = {10, -5, 25, 42, 8};
    uint32_t lenA = sizeof(dataA) / sizeof(dataA[0]);
    
    int32_t dataB[] = {100, 200, 300};
    uint32_t lenB = sizeof(dataB) / sizeof(dataB[0]);

    printf("--- Array Utility Exercises ---\n\n");

    printArray(dataA, lenA);
    printf("Sum: %d\n", sumArray(dataA, lenA));
    printf("Max: %d\n", maxArray(dataA, lenA));
    reversePrintArray(dataA, lenA);

    printf("\n--- Swapping Arrays ---\n\n");
    printf("Before Swap:\n");
    printf("Data A: "); printArray(dataA, lenA);
    printf("Data B: "); printArray(dataB, lenB);

    swapArrays(dataA, lenA, dataB, lenB);

    printf("\nAfter Swap:\n");
    printf("Data A: "); printArray(dataA, lenA);
    printf("Data B: "); printArray(dataB, lenB);

    return 0;
}
