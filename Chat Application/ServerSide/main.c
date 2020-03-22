#include "Server.h"
#include <stdio.h>

int main ()
{	int x=0;

	ServerInit(9998);
	x=ServerReceiveData();
	x++;
	ServerSendData(x);
	CloseSocket();
	printf("Sent from server the number %d\n",x);
	

return 0;
}	