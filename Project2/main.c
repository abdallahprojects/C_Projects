#include"Printer.h"
#include<stdio.h>

int main (void)
{	int i;
	const int  x=3;
	char arr[]="hello world";
	/*for (i=0;i<=11;i++)
	{
	printf("address of %c = %p \n",*(arr+i),arr+i);
	}*/
	arr[0]='K';
	Set_X(arr);

	//printf("%s",arr);
	Print_X();
	Print_Hello();
	printf("from the main address of %c = %p \n",*(arr),arr);
	
	
	return 0;
}




