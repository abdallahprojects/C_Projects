typedef enum type_e{
		type_text,
		type_connect,
		type_disconnect,
		type_fileSendChunk,
		type_fileSendChunk_Ok,
		type_fileSendRequest,
		type_fileSendRequest_Ok,
		type_fileSendSize,
		type_fileEnd
}type_t;
typedef struct packet_s{
		type_t 		type;
		char 		data [200];
		uint64_t 	ChunkNumber;
		uint8_t 	ChunkSize;
}packet_t;
void NET_SendData(packet_t * data);
void NET_ReceiveData(packet_t * data);
void NET_ServerInit(int PortNumber);
void NET_ClientInit(int PortNumber , char *ip);
void NET_CloseSocket(void);
