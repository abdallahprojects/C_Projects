#include <stdio.h>

int ReadFile(void)
{	int x;

	FILE *f;
	f=fopen("D:\\source.txt","r");
	
	if (f==NULL)
	{
		printf("Can't Find the file, Returning default 1\n");
		x=1;
		
	/*	f=fopen("source.txt","w");
		fprintf(f,"%d",x);
		printf("%d\n",x);
	*/
	}
	else
	{
		fscanf(f,"%d",&x);
		fclose(f);
	}
return x;	
}
		