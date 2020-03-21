#include <stdio.h>

void WriteToFile(int x)
{
	FILE *f;
	f=fopen("D:\\source.txt","w");
	if (f==NULL)
	{
		printf("Can't open the file");
	}
	else
	{
		fprintf(f,"%d",x);
		printf("%d",x);
		fclose(f);
	}
}