#include <stdio.h>
#include <stdint.h>

/**
 * Custom implementation of strlen()
 * Counts characters until the null terminator is reached.
 */
uint32_t custom_strlen(const char *str) {
    uint32_t count = 0;
    
    // Loop until we hit the '\0' null character
    while (str[count] != '\0') {
        count++;
    }
    
    return count;
}

int main(void) {
    char greeting[] = "Hello Embedded World";
    
    printf("String: \"%s\"\n", greeting);
    printf("Calculated Length: %u\n", custom_strlen(greeting));
    
    // Demonstrate that it stops at the first null character
    char hidden_msg[] = {'S', 'e', 'c', 'r', 'e', 't', '\0', 'H', 'i', 'd', 'd', 'e', 'n'};
    printf("\nString with embedded null: \"%s\"\n", hidden_msg);
    printf("Length before null: %u\n", custom_strlen(hidden_msg));
    
    return 0;
}
