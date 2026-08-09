#include<stdio.h>

/*
 * Attempting to access PrivateData from main.c via extern.
 *
 * If PrivateData in main.c is declared as:
 *   static int PrivateData = 100;   →  linker error (internal linkage)
 *   int PrivateData = 100;           →  this works, prints 900
 *
 * This demonstrates file-level privacy using static.
 */

/* extern int PrivateData; */   /* ← uncomment to demonstrate the linker error */

void file1_myFun1(void)
{
	/* PrivateData = 900; */    /* ← uncommenting both lines causes: undefined reference */
	printf("file1_myFun1 called — cannot access static PrivateData from main.c\n");
}
