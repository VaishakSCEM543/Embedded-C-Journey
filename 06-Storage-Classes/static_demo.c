#include<stdio.h>
#include<stdint.h>

void myFun1(void);

int main(void)
{
	myFun1();
	myFun1();
	myFun1();
	myFun1();

	return 0;
}

void myFun1(void)
{
	/* static — created once, survives every function return */
	static uint32_t count = 0;

	count++;

	printf("Executed %d time(s)\n", count);
}
