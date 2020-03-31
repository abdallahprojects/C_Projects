#include <windows.h>
#include "Client.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void sender(void);
static void receiver(void);
void ReadMyName(void);
void SendConnectRequest(void);

char username[50];
static char myname[50];
int main ()
{	int x=0;
	HANDLE ThreadHandle;
	DWORD ThreadId;
	ClientInit(9998 ,"127.0.0.1");
	ReadMyName();
	SendConnectRequest();
	ThreadHandle = CreateThread( NULL, /* default security attributes */ 0, /* default stack size */
	  receiver, /* thread function */ NULL, /* parameter to thread function */ 0, /* default creation    flags */ &ThreadId);
	sender();
	TerminateThread(ThreadHandle,0);
	CloseSocket();

return 0;
}	


static void receiver(void)
{
	packet_t x;
	while(1)
	{
		x=ReceiveData();
		if (x.type == type_connect)
		{
			memcpy(username,x.data,strlen(x.data));
			printf("%s is connected, Say Hi!\n",username);
		}
		else if (x.type == type_text)
		{
			printf("%s: %s\n",username,x.data);
		}
		else if (x.type == type_disconnect)
		{
			printf("%s disconnected.\n",username);
		}
		else
		{
			printf("unexpected protocol..!");
		}
	}
}
static void sender(void)
{
	packet_t data;
	int i;
	char text[200];
	while(1)
	{
		i=0;

		do
		{
			scanf("%c",&text[i]);
			i++;
		}while((i<=200)||(text[--i]!="\n"));

		if (!strcmp(text,"quit\n") || !strcmp(text,"QUIT\n"))
				{	printf("Exiting Application and Terminating receiver thread!")
					break;
				}
		memcpy(data.data,text,i-1);
		data.type = type_text;
		SendData(data);
	}
}

void ReadMyName(void)
{
	printf("Please Enter your name:\n");
	int i=0;

	do
	{
		scanf("%c",&myname[i]);
		i++;
	}while((i<=50)||(myname[--i]!="\n"));
	myname[i]=0;
}
void SendConnectRequest(void)
{
	packet_t x;
	memset(x,0,sizeof(x));
	x.type=type_connect;
	memcpy(x.data,myname,strlen(myname));
	SendData(x);
}
