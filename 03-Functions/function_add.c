#include <stdio.h>

// Function Prototype (Declaration)
// This tells the compiler about the function before we call it in main()
void function_add_numbers(int a, int b, int c);

int main(void)
{
    // Calling the function with raw numbers
    printf("--- Passing Raw Numbers ---\n");
    function_add_numbers(10, 20, 30);
    function_add_numbers(12, 13, 14);
    function_add_numbers(-20, +20, 14);
    
    // Calling the function with variables
    printf("\n--- Passing Variables ---\n");
    int valueA = 90;
    int valueB = 70;
    int valueC = 55;
    function_add_numbers(valueA, valueB, valueC);
    
    // Mixing variables and raw numbers
    printf("\n--- Mixing Variables and Numbers ---\n");
    function_add_numbers(valueA, 40, 100);

    return 0; // Return 0 to OS indicating SUCCESS
}

// Function Definition (Implementation)
void function_add_numbers(int a, int b, int c)
{
    int sum;
    sum = a + b + c;
    printf("Sum of %d, %d, and %d is: %d\n", a, b, c, sum);
}
