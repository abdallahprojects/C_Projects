#include<stdio.h>
#include<stdlib.h>



void WriteFile(void);
void ReadFile(void);
static int x=1;

int main (void)

{
	//WriteFile();
	ReadFile();
	
	
	
	
	
return 0;
}


void WriteFile(void)
{
	FILE *f;
	f=fopen("source.txt","w");
	if (f==NULL)
	{
		printf("Can't open the file");
	}
	else
	{
		x++;
		fprintf(f,"%d",x);
		printf("%d",x);
		fclose(f);
	}
	//static int x=1	
	//x++;
	
//	printf("%d\n",x);
}


	
void ReadFile(void)
{	

	//char arr[6];
	
	FILE *f;
	f=fopen("source.txt","r");
	
	if (!f)
	{
		printf("Can't Find the file\n Creating a new one\n");
		
		f=fopen("source.txt","w");
		fprintf(f,"%d",x);
		printf("%d\n",x);
	}
	else
	{
		fscanf(f,"%d",&x);
		//arr[4]=0;
		fclose(f);
		WriteFile();
	//	printf("\n%d\n",x);
	}
		
}		
	