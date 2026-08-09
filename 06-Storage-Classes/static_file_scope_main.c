#include<stdio.h>

/*
 * static at file scope:
 * PrivateData can only be accessed within this file.
 * file1.c cannot use it via extern.
 *
 * Remove 'static' to see what happens when file1.c can access it.
 */
static int PrivateData = 100;

void file1_myFun1(void);

int main(void)
{
	printf("PrivateData before call : %d\n", PrivateData);

	file1_myFun1();

	printf("PrivateData after call  : %d\n", PrivateData);

	return 0;
}
