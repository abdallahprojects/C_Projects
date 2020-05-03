
#include <stdint.h>
#include <winsock.h>
#include <stdio.h>
#include "Server.h"
	 int server;             
  struct sockaddr_in clientAddr;
  struct sockaddr_in serverAddr;
  SOCKET client_socket;

void SendData(packet_t data)
 {
	//sendto(server, (char *)&data, sizeof(data), 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr)); //(*@\clientBox{1+2)}@*)
	send(client_socket, (char *)&data, sizeof(data), 0);//send TCP packet
 }
  

  void ReceiveData(packet_t * data)
 {
	//int addrSize=sizeof(clientAddr);
	 int error;
	 memset(data,0,sizeof(packet_t));
	//bind(server, (struct sockaddr *) &serverAddr, sizeof(serverAddr)); //(*@\serverBox{1)}@*)

	//recvfrom(server, (char *)&data, sizeof(data), 0, (struct sockaddr *) &clientAddr, &addrSize); //(*@\serverBox{2)}@*)
	error = recv(client_socket, (char *)data, sizeof(packet_t), 0);
	printf("type rec is :%d \n",data->type);
	if(error == SOCKET_ERROR){
		printf("\n\n\nError from inside the socket read ********************************\n\n\n");
		CloseSocket();
	}
 }
 
 
 
 void ServerInit(int PortNumber)
 {

	WSADATA wsaData;
	int addrSize=sizeof(clientAddr);
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family      = AF_INET;          //IPv4 address
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);//don't care network interface
	serverAddr.sin_port        = htons(PortNumber);      //set port 9998

	WSAStartup(MAKEWORD(2, 0), &wsaData);  //Initialize WinSock
	server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(server, (struct sockaddr *) &serverAddr, sizeof(serverAddr)); //(*@\serverBox{1)}@*)
	listen(server, 5);
	//server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //Allocate client socket
	client_socket = accept(server,(struct sockaddr *)&clientAddr,&addrSize);
	if(client_socket == INVALID_SOCKET)
		printf("Somethign WRong!\n");

 }
 
 void CloseSocket(void)
 {
	 closesocket(server);
	 WSACleanup();
 }
 
 
	 
