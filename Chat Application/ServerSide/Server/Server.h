typedef enum type_e{
		type_text,
		type_connect,
		type_disconnect,
		type_fileSendChunk,
		type_fileSendChunk_Ok,
		type_fileSendRequest,
		type_fileSendRequest_Ok,
		type_fileEnd
}type_t;
typedef struct packet_s{
		type_t 		type;
		char 		data [200];
		uint64_t 	ChunkNumber;
		uint8_t 	ChunkSize;
}packet_t;
void SendData(packet_t data);
void ReceiveData(packet_t * data);
void ServerInit(int PortNumber);
void CloseSocket(void);
