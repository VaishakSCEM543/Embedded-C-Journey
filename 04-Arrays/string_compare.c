#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * Custom implementation of strcmp()
 * Returns true if both strings are exactly identical.
 */
bool custom_strcmp(const char *str1, const char *str2) {
    uint32_t i = 0;
    
    // Loop until we reach the end of either string
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false; // Characters mismatch
        }
        i++;
    }
    
    // If both ended at the exact same length with the null terminator
    if (str1[i] == '\0' && str2[i] == '\0') {
        return true;
    }
    
    // One string was longer than the other
    return false;
}

int main(void) {
    char password[] = "Embedded123";
    
    char attempt1[] = "Embedded123";
    char attempt2[] = "embedded123"; // Case mismatch
    char attempt3[] = "Embedded12";  // Length mismatch
    
    printf("Comparing '%s' and '%s': %s\n", password, attempt1, custom_strcmp(password, attempt1) ? "MATCH" : "FAIL");
    printf("Comparing '%s' and '%s': %s\n", password, attempt2, custom_strcmp(password, attempt2) ? "MATCH" : "FAIL");
    printf("Comparing '%s' and '%s': %s\n", password, attempt3, custom_strcmp(password, attempt3) ? "MATCH" : "FAIL");
    
    return 0;
}
