
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
	 static uint8_t buff[2*sizeof(packet_t)]; //448
	 static uint16_t buff_ptr=0;

	 memset(data,0,sizeof(packet_t));
	//bind(server, (struct sockaddr *) &serverAddr, sizeof(serverAddr)); //(*@\serverBox{1)}@*)

	//recvfrom(server, (char *)&data, sizeof(data), 0, (struct sockaddr *) &clientAddr, &addrSize); //(*@\serverBox{2)}@*)
	while((buff_ptr < sizeof(packet_t)) && (error != SOCKET_ERROR))
	{
		error = recv(client_socket, (char *)(buff+buff_ptr), sizeof(packet_t), 0);
		if(error > 0)
		buff_ptr+=error;
	}
	if(buff_ptr < sizeof(packet_t)){
		printf("unexpected packet length!\n");
		//intermediate buffer should be handled
	}
	memcpy(data,buff,sizeof(packet_t));
	memcpy(buff,buff+sizeof(packet_t),sizeof(packet_t));
	buff_ptr -= sizeof(packet_t);
	//printf("type rec is :%d \n",data->type);
	if(error == SOCKET_ERROR){
		printf("\nClient Endded the connection");
		CloseSocket();
		exit(0);
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
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
 
 
	 
