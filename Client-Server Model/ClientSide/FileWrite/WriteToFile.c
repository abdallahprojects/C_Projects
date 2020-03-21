#include "RW.h"
#include <stdio.h>

void WriteToFile(int x)
{
	FILE *f;
	f=fopen("source.txt","w");
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


void ReadFile(void)
{	

	FILE *f;
	f=fopen("source.txt","r");
	
	if (f==NULL)
	{
		printf("Can't Find the file\n Creating a new one\n");
		
	/*	f=fopen("source.txt","w");
		fprintf(f,"%d",x);
		printf("%d\n",x);
		*/
	}
	else
	{
		fscanf(f,"%d",&x);
		fclose(f);
		WriteFile();
	}
	
}
		