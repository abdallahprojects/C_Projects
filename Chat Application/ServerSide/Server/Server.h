typedef enum type_e{
		type_text,
		type_connect,
		type_disconnect,
		type_fileSendRequest
}type_t;
typedef struct packet_s{
		type_t type;
		char data [200];
}packet_t;
void SendData(packet_t data);
packet_t ReceiveData(void);
void ServerInit(int PortNumber);
void CloseSocket(void);
