#include <stdint.h>
#include "Client.h"
#include <winsock.h>
#include <stdio.h>


	 int serverSocket;             
  struct sockaddr_in ServerAddress;


  void SendData(packet_t * data)
   {
  	//sendto(serverSocket, (char *)&data, sizeof(data), 0, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress)); //(*@\clientBox{1+2)}@*)
	  send(serverSocket, (char *)data, sizeof(packet_t),0);
	// printf("packet type is %d\n",data.type);
   }

  
  packet_t ReceiveData(void)
 {
	/* int addrSize;
	struct sockaddr_in  clientAddr;
	int len = sizeof(clientAddr);*/
	static packet_t data;

	memset(&data,0,sizeof(data));
	/*//struct sockaddr name;
	memset(&clientAddr, 0, sizeof(clientAddr));
	clientAddr.sin_family      = AF_INET;          //IPv4 address
	clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);//don't care network interface
	getsockname(serverSocket,(struct sockaddr *)&clientAddr,&len);
	addrSize                   = sizeof(clientAddr);
	recvfrom(serverSocket, (char *)&data, sizeof(data), 0, (struct sockaddr *) &clientAddr, &addrSize); //(*@\serverBox{2)}@*)	*/
	 recv(serverSocket, (char *)&data, sizeof(data),0);
	return data;
 }
 
 
 
 void ClientInit(int PortNumber , char *ip)
 {

  WSADATA wsaData;           
  WSAStartup(MAKEWORD(2, 0), &wsaData);  //Initialize WinSock
  ServerAddress.sin_family      = AF_INET;    //IPv4 address
  ServerAddress.sin_addr.s_addr = inet_addr(ip);//Set to (loopback) IP address
  ServerAddress.sin_port        = htons(PortNumber); //Make port in network byte order
  serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //Allocate server socket
  connect(serverSocket,(struct sockaddr *)&ServerAddress,sizeof(ServerAddress));

 }
 
 void CloseSocket(void)
 {
	 closesocket(serverSocket);
	 WSACleanup();
 }
 
 

	 
