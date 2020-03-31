#include <winsock.h>
#include <stdio.h>
#include "Server.h"
	 int server;             
  struct sockaddr_in clientAddr;
  struct sockaddr_in serverAddr;
  struct sockaddr_in	clientAddr;

void SendData(packet_t data)
 {
	sendto(server, (char *)&data, sizeof(data), 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr)); //(*@\clientBox{1+2)}@*)
 }
  
  
  packet_t ReceiveData(void)
 {

	 packet_t data;
	int addrSize=sizeof(clientAddr);
	bind(server, (struct sockaddr *) &serverAddr, sizeof(serverAddr)); //(*@\serverBox{1)}@*)
	recvfrom(server, (char *)&data, sizeof(data), 0, (struct sockaddr *) &clientAddr, &addrSize); //(*@\serverBox{2)}@*)
	return data;
 }
 
 
 
 void ServerInit(int PortNumber)
 {

	WSADATA wsaData;           
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family      = AF_INET;          //IPv4 address
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);//don't care network interface
	serverAddr.sin_port        = htons(PortNumber);      //set port 9998

	WSAStartup(MAKEWORD(2, 0), &wsaData);  //Initialize WinSock
	server = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); //Allocate client socket


 }
 
 void CloseSocket(void)
 {
	 closesocket(server);
	 WSACleanup();
 }
 
 
	 
