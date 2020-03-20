#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Printer.h"
static int SizeChar(char * string);

	static char * Text_Buffer;
	//This variable is in .bss  
	//Life-Time = Application life cycle


int SizeChar(char * string)
{	int counter =0;

	while(*(string++))
	{	
		counter+=1;
	}
	return counter+1;
}
		



void Set_X( char * In_text)
{	char * temp= 	;
	int size=0;
	size=SizeChar(In_text);
	Text_Buffer=(char*)malloc(sizeof(char)*size);
	memset(Text_Buffer,0,size);
	temp=Text_Buffer;
	while(*In_text)
	{
		*temp=*In_text;
		
		
		temp++;
		In_text++;
	}	
}

void Print_X(void)
{	char * temp= Text_Buffer;

	//printf("the address of the %c is %p \n",*Text_Buffer,Text_Buffer);
	while(1)
	{
		
		printf("%c",*temp);
		if (*temp == 0)
		{
				printf("\n");
				break;
		}
	temp++;
	
	}

}

void Print_Hello (void)

{
		printf("from printer address of %c = %p \n",*Text_Buffer,Text_Buffer);
	
}

