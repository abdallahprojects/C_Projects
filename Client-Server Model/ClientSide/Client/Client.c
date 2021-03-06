#include <stdio.h>//compile: gcc UDPClient_windows.c -o UDPClient_windows.exe -lws2_32
#include <winsock.h> //Warning: This program does not perform any error handling.
 static void SendRequest(void);
  static int ReceieveFromServer(void);
void ClientSendData(int number)  {
  int client;             
  struct sockaddr_in address;
  WSADATA wsaData;           
  int data;

  WSAStartup(MAKEWORD(2, 0), &wsaData);  //Initialize WinSock
  client = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); //Allocate client socket

  memset(&address, 0, sizeof(address)); //Clear socket address
  address.sin_family      = AF_INET;    //IPv4 address
  address.sin_addr.s_addr = inet_addr("127.0.0.1");//Set to (loopback) IP address
  address.sin_port        = htons(9998); //Make port in network byte order

  data = number; // then send 1 byte package data to client, with flags=0
  sendto(client, (char *)&data, sizeof(data), 0, (struct sockaddr *)&address, sizeof(address)); //(*@\clientBox{1+2)}@*)

  closesocket(client); //(*@\clientBox{4)}@*)
  WSACleanup(); //Finalize Winsock
  }
  
 int ClientRequestData(void)
 {	
	int x;
	SendRequest();
	x=ReceieveFromServer();

	return x;
 }
 
 static void SendRequest(void)
 {
  int client;             
  struct sockaddr_in address;
  WSADATA wsaData;           
  const char data = 'R';

  WSAStartup(MAKEWORD(2, 0), &wsaData);  //Initialize WinSock
  client = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); //Allocate client socket

  memset(&address, 0, sizeof(address)); //Clear socket address
  address.sin_family      = AF_INET;    //IPv4 address
  address.sin_addr.s_addr = inet_addr("127.0.0.1");//Set to (loopback) IP address
  address.sin_port        = htons(9998); //Make port in network byte order
  sendto(client,&data, sizeof(data), 0, (struct sockaddr *)&address, sizeof(address)); //(*@\clientBox{1+2)}@*)

  closesocket(client); //(*@\clientBox{4)}@*)
  WSACleanup(); //Finalize Winsock
 
 }
 
 static int ReceieveFromServer(void)
 {
	 int server, addrSize;
	struct sockaddr_in serverAddr, clientAddr;
	WSADATA wsaData;
	int data;
	
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family      = AF_INET;          //IPv4 address
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);//don't care network interface
	serverAddr.sin_port        = htons(9998);      //set port 9998
	addrSize                   = sizeof(clientAddr);
	
	WSAStartup(MAKEWORD(2, 0), &wsaData);             //Initialize WinSock
	server = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);//Allocate UDP socket
	bind(server, (struct sockaddr *) &serverAddr, sizeof(serverAddr)); //(*@\serverBox{1)}@*)
	recvfrom(server, (char *)&data, sizeof(data), 0, (struct sockaddr *) &clientAddr, &addrSize); //(*@\serverBox{2)}@*)
	printf("New message %d from server %s\n", data, inet_ntoa(clientAddr.sin_addr));  //(*@\serverBox{3)}@*)
	
	closesocket(server); //(*@\serverBox{5)}@*)
	WSACleanup();        //Finalize WinSock
	return data;
 }
 
 
 
 
 
 
 