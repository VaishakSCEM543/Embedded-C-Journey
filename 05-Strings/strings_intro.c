#include <stdio.h>
#include <string.h>

int main(void)
{
    /* 1. Dynamic Array Size String Initialization */
    // The compiler automatically counts 5 letters + 1 null character ('\0') = 6 bytes
    char msg1[] = "Hello";
    
    /* 2. Fixed Size String Initialization */
    // The first 6 bytes are 'H', 'e', 'l', 'l', 'o', '\0'. The remaining 4 bytes are initialized to 0.
    char msg2[10] = "Hello";

    /* 3. Manual Character Array Initialization (NOT A STRING) */
    // Since there is no '\0', this is just a standard array of characters. 
    // Do not use this with %s in printf, it will print garbage until it hits a 0 in memory!
    char not_a_string[] = {'H', 'e', 'l', 'l', 'o'};

    /* 4. Manual Character Array Initialization (PROPER STRING) */
    char manual_string[] = {'H', 'e', 'l', 'l', 'o', '\0'};

    printf("--- Strings vs Character Arrays ---\n");
    printf("msg1 (String): %s\n", msg1);
    printf("manual_string: %s\n", manual_string);
    
    printf("\n--- sizeof() vs strlen() ---\n");
    
    // sizeof() returns the total allocated memory in bytes
    printf("sizeof(msg1) : %llu bytes\n", (unsigned long long)sizeof(msg1)); // 6
    printf("sizeof(msg2) : %llu bytes\n", (unsigned long long)sizeof(msg2)); // 10
    
    // strlen() returns the number of characters before the '\0'
    printf("strlen(msg1) : %llu characters\n", (unsigned long long)strlen(msg1)); // 5
    printf("strlen(msg2) : %llu characters\n", (unsigned long long)strlen(msg2)); // 5
    
    printf("\n--- Character vs String ---\n");
    char ch = 'A';
    char str[] = "A";
    
    printf("sizeof('A') as a character variable : %llu bytes\n", (unsigned long long)sizeof(ch));
    printf("sizeof(\"A\") as a string literal     : %llu bytes\n", (unsigned long long)sizeof(str));
    
    return 0;
}
