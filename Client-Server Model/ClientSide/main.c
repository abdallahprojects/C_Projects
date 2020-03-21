#include "Client.h"
#include "ReadFromFile.h"
#include <stdio.h>

int main ()
{	int x=0;

	x=ClientRequestData();
	printf("Received from server number %d\n",x);
	x++;
	ClientSendData(x);
	printf("Sending to server number %d\n",x);
	
	
return 0;
}
	