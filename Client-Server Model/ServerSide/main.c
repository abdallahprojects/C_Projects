#include "server.h"
#include "WriteToFile.h"
#include "ReadFromFile.h"
#include <stdio.h>
int main ()
{
	int i,x;
	for (i=0; i<5 ; i++)
	{
		WaitForClientRequest();
		x=ReadFromFile();
		printf("Sending to client number %d\n",x);
		SendToClient(x);
		x=ReadFromClient();
		printf("Received from client number %d\n",x);
		WriteToFile(x);
	}
	

return 0;
}	