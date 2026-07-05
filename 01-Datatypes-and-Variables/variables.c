/*
 * Topic   : Variables — definition, initialization, naming rules
 * Concept : A variable is a label for a memory address. The compiler replaces
 *           variable names with actual addresses in machine code. Variable names
 *           do NOT exist post-compilation — only addresses do.
 * Learned : Define before use. Naming rules: alphanumeric + underscore only,
 *           cannot start with digit, no reserved keywords, max ~30 chars.
 */

#include <stdio.h>

int main(void)
{
    /* definition — compiler reserves memory */
    int sensor_value;

    /* initialization — assign a value */
    sensor_value = 1024;

    /* definition + initialization in one line */
    unsigned char led_state  = 1;
    unsigned int  timer_ms   = 5000;
    char          exam_score = 95;

    printf("sensor_value : %d\n",  sensor_value);
    printf("led_state    : %u\n",  led_state);
    printf("timer_ms     : %u\n",  timer_ms);
    printf("exam_score   : %d\n",  exam_score);

    return 0;
}

/*
 * NAMING RULES (quick ref):
 *   legal   : exam_score, _value, myVar123
 *   illegal : 1score (digit first), my-var (hyphen), int (keyword)
 *
 * DEFINITION vs DECLARATION:
 *   Definition  → allocates memory  →  int x;
 *   Declaration → informs compiler only, no memory  →  extern int x;
 *
 * EMBEDDED:
 *   In STM32, peripheral registers are fixed memory addresses.
 *   Variables abstract that: volatile uint32_t *ODR = (uint32_t*)0x40020014;
 */
