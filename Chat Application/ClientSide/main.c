#include "Client.h"

#include <stdio.h>
int main ()
{	int x=0;

	ClientInit(9998 ,"127.0.0.1");
	ClientSendData(5);
	x=ClientReceiveData();
	CloseSocket();
	printf("Received from server the number %d\n",x);
	

return 0;
}	