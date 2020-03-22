#include <winsock.h>
#include <stdio.h>
	 int client;             
  struct sockaddr_in address;


void ClientSendData(int number) 
 {
	sendto(client, (char *)&number, sizeof(number), 0, (struct sockaddr *)&address, sizeof(address)); //(*@\clientBox{1+2)}@*)
 }
  
  
  int ClientReceiveData(void)
 {
	 int addrSize;
	struct sockaddr_in  clientAddr;
	int len = sizeof(clientAddr);
	int data;
	//struct sockaddr name;
	memset(&clientAddr, 0, sizeof(clientAddr));
	clientAddr.sin_family      = AF_INET;          //IPv4 address
	clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);//don't care network interface
	getsockname(client,(struct sockaddr *)&clientAddr,&len);
	printf("source port number %d\n", ntohs(clientAddr.sin_port));	
	printf("source ip number %s\n", inet_ntoa(clientAddr.sin_addr));	
	addrSize                   = sizeof(clientAddr);
	
	//WSAStartup(MAKEWORD(2, 0), &wsaData);             //Initialize WinSock
	//server = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);//Allocate UDP socket
	//bind(server, (struct sockaddr *) &serverAddr, sizeof(serverAddr)); //(*@\serverBox{1)}@*)
	recvfrom(client, (char *)&data, sizeof(data), 0, (struct sockaddr *) &clientAddr, &addrSize); //(*@\serverBox{2)}@*)	
	printf("New message %d from server %s\n", data, inet_ntoa(clientAddr.sin_addr));  //(*@\serverBox{3)}@*)

	return data;
 }
 
 
 
 void ClientInit(int PortNumber , char *ip)
 {

  WSADATA wsaData;           


  WSAStartup(MAKEWORD(2, 0), &wsaData);  //Initialize WinSock
  client = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); //Allocate client socket

  memset(&address, 0, sizeof(address)); //Clear socket address
  address.sin_family      = AF_INET;    //IPv4 address
  address.sin_addr.s_addr = inet_addr(ip);//Set to (loopback) IP address
  address.sin_port        = htons(PortNumber); //Make port in network byte order

 }
 
 void CloseSocket(void)
 {
	 closesocket(client);
	 WSACleanup();
 }
 
 
	 