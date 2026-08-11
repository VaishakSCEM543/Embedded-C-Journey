#include<stdio.h>
#include<stdint.h>

/*
 * Bitwise Operators Demo
 * Covers: TEST, SET, CLEAR, TOGGLE (Lectures 104-110)
 *
 * The four standard embedded C bit manipulation patterns:
 *
 *   if (REG & MASK)    → TEST
 *   REG |=  MASK;      → SET
 *   REG &= ~MASK;      → CLEAR
 *   REG ^=  MASK;      → TOGGLE
 */

void print_binary(uint8_t val);

int main(void)
{
	uint8_t data = 0x55;   /* 01010101 */
	uint8_t mask = 0x08;   /* 00001000 — targets Bit 3 */

	printf("Initial data : ");
	print_binary(data);

	/* ── TEST ──────────────────────────────── */
	printf("\n--- TEST Bit 3 ---\n");
	if (data & mask)
		printf("Bit 3 is SET\n");
	else
		printf("Bit 3 is CLEAR\n");

	/* ── SET ───────────────────────────────── */
	printf("\n--- SET Bit 3 ---\n");
	data |= mask;
	printf("After SET    : ");
	print_binary(data);   /* 01011101 */

	/* ── CLEAR ─────────────────────────────── */
	printf("\n--- CLEAR Bit 3 ---\n");
	data &= ~mask;
	printf("After CLEAR  : ");
	print_binary(data);   /* 01010101 */

	/* ── TOGGLE ────────────────────────────── */
	printf("\n--- TOGGLE Bit 3 (twice) ---\n");
	data ^= mask;
	printf("Toggle 1     : ");
	print_binary(data);   /* 01011101 — bit went 0→1 */

	data ^= mask;
	printf("Toggle 2     : ");
	print_binary(data);   /* 01010101 — bit went 1→0 */

	/* ── REAL EMBEDDED PATTERN ─────────────── */
	printf("\n--- Set Bits 4 and 7 (mask = 0x90) ---\n");
	uint8_t reg = 0x55;   /* 01010101 */
	reg |= 0x90;          /* set Bit 4 and Bit 7 */
	printf("GPIO after |= 0x90 : ");
	print_binary(reg);    /* 11010101 */

	printf("\n--- Clear Bits 4,5,6 using ~(0x70) ---\n");
	reg &= ~(0x70);       /* 0x70 = 01110000, ~0x70 = 10001111 */
	printf("GPIO after &= ~0x70 : ");
	print_binary(reg);    /* 11000101 */

	return 0;
}

/* Print an 8-bit value in binary with Bit 7 on the left */
void print_binary(uint8_t val)
{
	int i;
	for (i = 7; i >= 0; i--)
		printf("%d", (val >> i) & 1);
	printf("  (0x%02X = %d)\n", val, val);
}
