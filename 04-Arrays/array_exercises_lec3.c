#include<stdio.h>
#include<stdint.h>

void wait_for_user_input(void);
void display_array(int32_t *pArray, uint32_t nItems);
void swap_arrays(int32_t *array1, int32_t *array2, uint32_t nItem1, uint32_t nItem2);

int main(void)
{
    int32_t nItem1, nItem2;
    printf("Array swapping program\n");
    printf("Enter no of elements of Array-1 and Array-2:");
    scanf("%d %d", &nItem1, &nItem2);

    if((nItem1 < 0) || (nItem2 < 0))
    {
    	printf("Number of elements cannot be negative\n");
    	wait_for_user_input();
    	return 0;
    }

    /* VLA — size determined at runtime from user input */
    int32_t array1[nItem1];
    int32_t array2[nItem2];

    for(uint32_t i = 0; i < (uint32_t)nItem1; i++)
    {
    	printf("Enter %d element of array1:", i);
    	scanf("%d", &array1[i]);
    }

    for(uint32_t i = 0; i < (uint32_t)nItem2; i++)
    {
    	printf("Enter %d element of array2:", i);
    	scanf("%d", &array2[i]);
    }

	printf("Contents of arrays before swap \n");

	display_array(array1, (uint32_t)nItem1);

	printf("\n");

	display_array(array2, (uint32_t)nItem2);

	printf("\n");

	printf("Contents of arrays after swap\n");

	swap_arrays(array1, array2, (uint32_t)nItem1, (uint32_t)nItem2);

	display_array(array1, (uint32_t)nItem1);

	printf("\n");

	display_array(array2, (uint32_t)nItem2);

	printf("\n");

	wait_for_user_input();

	return 0;
}


void display_array(int32_t *pArray, uint32_t nItems)
{
	for(uint32_t i = 0 ; i < nItems ; i++)
	{
		printf("%4d  ", pArray[i]);
	}
}


void swap_arrays(int32_t *array1, int32_t *array2, uint32_t nItem1, uint32_t nItem2)
{
   uint32_t len = nItem1 < nItem2 ? nItem1 : nItem2;

   for(uint32_t i = 0 ; i < len ; i++)
   {
	   int32_t temp = array1[i];
	   array1[i] = array2[i];
	   array2[i] = temp;
   }
}


void wait_for_user_input(void)
{
	printf("Press enter key to exit this application");

    while(getchar() != '\n')
    {
    	/* just read the input buffer and do nothing */
    }
    getchar();
}
