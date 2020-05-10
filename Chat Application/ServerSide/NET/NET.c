#define  NET_C_
#include <stdint.h>
#include <winsock.h>
#include <stdint.h>
#include <stdio.h>
#include "NET.h"
#include "net_local.h"


void NET_SendData(packet_t * data)
 {
	  send(net_socket, (char *)data, sizeof(packet_t),0);
 }

  void NET_ReceiveData(packet_t * data)
 {
	 int error;
	 static uint8_t buff[2*sizeof(packet_t)]; //448
	 static uint16_t buff_ptr=0;

	 memset(data,0,sizeof(packet_t));
	while((buff_ptr < sizeof(packet_t)) && (error != SOCKET_ERROR))
	{
		error = recv(net_socket, (char *)(buff+buff_ptr), sizeof(packet_t), 0);
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
		NET_CloseSocket();
		exit(0);
	}
 }
 
 void NET_ServerInit(int PortNumber)
 {

	WSADATA wsaData;
	int addrSize=sizeof(clientAddr);
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family      = AF_INET;          //IPv4 address
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);//don't care network interface
	serverAddr.sin_port        = htons(PortNumber);      //set port 9998
	WSAStartup(MAKEWORD(2, 0), &wsaData);  //Initialize WinSock
	net_socNumber = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(net_socNumber, (struct sockaddr *) &serverAddr, sizeof(serverAddr)); //(*@\serverBox{1)}@*)
	listen(net_socNumber, 5);
	net_socket = accept(net_socNumber,(struct sockaddr *)&clientAddr,&addrSize);
	if(net_socket == INVALID_SOCKET)
		printf("Something WRong!\n");

 }
 
 void NET_ClientInit(int PortNumber , char *ip)
  {

   WSADATA wsaData;
   WSAStartup(MAKEWORD(2, 0), &wsaData);  //Initialize WinSock
   serverAddr.sin_family      = AF_INET;    //IPv4 address
   serverAddr.sin_addr.s_addr = inet_addr(ip);//Set to (loopback) IP address
   serverAddr.sin_port        = htons(PortNumber); //Make port in network byte order
   net_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //Allocate server socket
   while(connect(net_socket,(struct sockaddr *)&serverAddr,sizeof(serverAddr)));

  }

 void NET_CloseSocket(void)
 {

	 closesocket(net_socNumber);
	 WSACleanup();
 }
 
 
	 
