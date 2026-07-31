#include <stdio.h>
#include <stdint.h>

/**
 * Custom implementation of strcpy()
 * Copies characters from source to destination, including the null terminator.
 */
void custom_strcpy(char *dest, const char *src) {
    uint32_t i = 0;
    
    // Copy character by character until we hit the null terminator
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    
    // Don't forget to append the null terminator to the destination!
    dest[i] = '\0';
}

int main(void) {
    char source[] = "Embedded C is awesome!";
    
    // Make sure destination array is large enough (including \0)
    char destination[50]; 
    
    printf("Source String: \"%s\"\n", source);
    
    // Perform the manual copy
    custom_strcpy(destination, source);
    
    printf("Destination String after copy: \"%s\"\n", destination);
    
    return 0;
}
