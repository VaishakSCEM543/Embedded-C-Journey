/*
 * function_return.c
 *
 * Lecture 3 - Returning Values from Functions
 *
 * Demonstrates:
 *   - Changing void to int return type
 *   - Using return statement to send a value back to the caller
 *   - Storing the returned value in main()
 *   - Why returning is better than printing inside a function
 *   - Embedded Systems analogy: sensor reading functions
 */

#include <stdio.h>

// ------------------------------------------------------------
// Function Prototypes (Declarations)
// Return type changed from void → int
// ------------------------------------------------------------
int function_add_numbers(int a, int b, int c);
int readTemperature(void);

int main(void)
{
    // ----------------------------------------------------------
    // Demo 1: Capture the returned value and print it in main()
    // ----------------------------------------------------------
    printf("--- Demo 1: Storing Returned Value ---\n");

    int returnValue;
    returnValue = function_add_numbers(10, 20, 30);
    printf("Returned value: %d\n", returnValue);

    // ----------------------------------------------------------
    // Demo 2: Use the returned value directly in an expression
    // The function is called multiple times, each result is
    // captured and used independently.
    // ----------------------------------------------------------
    printf("\n--- Demo 2: Reusing the Return Value ---\n");

    int sum1 = function_add_numbers(10, 20, 30);
    int sum2 = function_add_numbers(12, 13, 14);
    int sum3 = function_add_numbers(-20, +20, 14);

    printf("Sum 1 : %d\n", sum1);
    printf("Sum 2 : %d\n", sum2);
    printf("Sum 3 : %d\n", sum3);

    // ----------------------------------------------------------
    // Demo 3: Use return value inside another calculation
    // This would be IMPOSSIBLE if the function only printed.
    // ----------------------------------------------------------
    printf("\n--- Demo 3: Using Return Value in a Calculation ---\n");

    int a = 10, b = 20, c = 30;
    int total = function_add_numbers(a, b, c);
    int average = total / 3;

    printf("Sum     : %d\n", total);
    printf("Average : %d\n", average);

    // ----------------------------------------------------------
    // Demo 4: Embedded Systems analogy
    // readTemperature() returns a value instead of printing it.
    // The caller decides what to do with it.
    // ----------------------------------------------------------
    printf("\n--- Demo 4: Embedded Systems Analogy ---\n");

    int temperature = readTemperature();

    // Caller decides what to do:
    printf("Temperature: %d C\n", temperature);

    if (temperature > 30)
    {
        printf("WARNING: Temperature too high! Triggering cooling...\n");
    }
    else
    {
        printf("Temperature is within safe range.\n");
    }

    return 0; // Return 0 to OS indicating SUCCESS
}

// ------------------------------------------------------------
// Function Definition
// Returns the sum of three integers to the caller
// ------------------------------------------------------------
int function_add_numbers(int a, int b, int c)
{
    int sum;

    sum = a + b + c;

    return sum; // Send sum back to whoever called this function
                // Function ends immediately after return
}

// ------------------------------------------------------------
// Embedded Systems Example
// Simulates reading a temperature sensor
// Returns the value instead of printing it
// Caller decides: display, compare, send over UART, save, etc.
// ------------------------------------------------------------
int readTemperature(void)
{
    // In real embedded code, you'd read from a sensor register.
    // Example: return (int)ADC_Read(TEMP_SENSOR_CHANNEL);
    return 32; // Simulated sensor reading
}
