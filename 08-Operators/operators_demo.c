#include<stdio.h>
#include<stdint.h>

/*
 * Operators Demo — Lecture 1
 * Topics: Arithmetic operators, precedence, associativity, parentheses
 */

int main(void)
{
	int a = 14;
	int b = 4;

	/* ── Arithmetic operators ─────────────────────── */
	printf("=== Arithmetic Operators ===\n");
	printf("a = %d, b = %d\n\n", a, b);
	printf("a + b = %d\n", a + b);   /*  18 */
	printf("a - b = %d\n", a - b);   /*  10 */
	printf("a * b = %d\n", a * b);   /*  56 */
	printf("a / b = %d\n", a / b);   /*   3  ← integer division, truncates */
	printf("a %% b = %d\n", a % b);  /*   2  ← remainder */

	/* ── Precedence demo ──────────────────────────── */
	printf("\n=== Precedence ===\n");
	printf("2 + 3 * 4     = %d\n", 2 + 3 * 4);       /* 14 — * before + */
	printf("(2 + 3) * 4   = %d\n", (2 + 3) * 4);     /* 20 — () first  */

	/* ── Associativity demo ───────────────────────── */
	printf("\n=== Associativity (left to right) ===\n");
	printf("20 / 2 * 5    = %d\n", 20 / 2 * 5);      /* 50 — (20/2)*5  */
	printf("10 - 3 + 2    = %d\n", 10 - 3 + 2);      /*  9 — (10-3)+2  */

	/* ── Modulus use case: even/odd ───────────────── */
	printf("\n=== Modulus: Even / Odd ===\n");
	int nums[] = {11, 14, 7, 20};
	uint8_t i;
	for (i = 0; i < 4; i++)
	{
		if (nums[i] % 2 == 0)
			printf("%d is Even\n", nums[i]);
		else
			printf("%d is Odd\n", nums[i]);
	}

	/* ── Ternary operator ─────────────────────────── */
	printf("\n=== Ternary (Conditional) Operator ===\n");
	int x = 10, y = 20;
	int max = (x > y) ? x : y;
	printf("max of %d and %d = %d\n", x, y, max);

	return 0;
}
