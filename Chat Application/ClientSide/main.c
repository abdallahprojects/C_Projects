#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fileH.h"
#include "Client.h"
typedef enum FileState_e{
		file_Init,
		file_ReadNumberOfChunks,
		file_SendChunks,
		file_End
}FileState_t;
void strclr(char * ptr, int size);
static void sender(void);
DWORD WINAPI receiver(LPVOID Param);
void ReadMyName(void);
void SendConnectRequest(void);
void GetFileName(char filePath[400]);
bool FileStateMachine(void);
bool SendFileRequest(void);
void SendChunks(uint64_t NumberOfChunks);
static int mynameFlag = 1;
static char filePath[400];
static char username[50];
static char myname[50];
static char extension[10];
static char fileName[50];
char FullFileName[50];
int main() {
	HANDLE ThreadHandle;
	DWORD ThreadId;
	ClientInit(9998, "127.0.0.1");
	ReadMyName();
	ThreadHandle = CreateThread( NULL, /* default security attributes */0, /* default stack size */
	receiver, /* thread function */NULL, /* parameter to thread function */0, /* default creation    flags */
			&ThreadId);
	SendConnectRequest();
	sender();
	TerminateThread(ThreadHandle, 0);
	CloseSocket();

	return 0;
}

DWORD WINAPI receiver(LPVOID Param) {
	packet_t x;
	while (1) {
		x = ReceiveData();
		if (x.type == type_connect) {
			memcpy(username, x.data, strlen(x.data));
			printf("%s is connected, Say Hi!\n", username);
			mynameFlag = 0;

		} else if (x.type == type_text) {
			printf("%s: %s\n", username, x.data);
		} else if (x.type == type_disconnect) {
			printf("%s disconnected.\n", username);
		} else {
			printf("unexpected protocol..!");
		}
	}
}
static void sender(void) {
	packet_t data;
	int i;
	char text[200];
	while (1) {
		i = 0;

		do {
			scanf("%c", &text[i]);
			i++;
		} while ((i <= 200) && (text[i - 1] != '\n'));
		text[i - 1] = 0;
		if (!strcmp(text, "quit") || !strcmp(text, "QUIT")) {
			printf("Exiting Application and Terminating receiver thread!");
			break;
		} else if (!strcmp(text, "file")) {
		while (	FileStateMachine());
		} else {
			memcpy(data.data, text, i);
			data.type = type_text;
			SendData(data);
		}
	}
}

void ReadMyName(void) {
	printf("Please Enter your name: ");
	int i = 0;

	do {
		scanf("%c", &myname[i]);
		i++;
	} while ((i < 50) && (myname[i - 1] != '\n'));
	i--;
	myname[i] = 0;
}
void SendConnectRequest(void) {
	packet_t x;
	memset(&x, 0, sizeof(x));
	x.type = type_connect;
	memcpy(x.data, myname, strlen(myname));

	while (mynameFlag) //while I didn't receive server name
	{
		SendData(x); // Send my name again
		Sleep(200);
	}

}

void GetFileName(char filePath[400]) {
	int i = 0;
	int len = 0;
	char ch;

	len = strlen(filePath);
	memset(extension, 0, sizeof(extension));
	do {
		ch = filePath[len--];

		if (ch != '"' && ch != '\'' && ch != 0) {
			extension[i++] = ch;
		}

	} while ((ch != '.') && (i < 10));

	if (ch != '.') {
		printf("Wrong File Extension\n");
		return;
	}
//extracting fileName
	i = 0;
	memset(fileName, 0, sizeof(fileName));
	do {
		ch = filePath[len--];
		fileName[i++] = ch;

	} while ((ch != '\\') && (i < 50));
	fileName[i - 1] = 0;

	if (ch != '\\') {
		printf("too long File Name\n");
		return;
	}

	memcpy(extension, strrev(extension), sizeof(extension));
	memcpy(fileName, strrev(fileName), sizeof(fileName));

}

void strclr(char * ptr, int size) {

	memset(ptr, 0, size);
}

bool FileStateMachine(void) {
	static uint64_t NumberOfChunks=0;
	bool ret=true;
	static FileState_t state = file_Init;
	switch (state) {

	case file_Init:
		if (SendFileRequest()) {
			state = file_ReadNumberOfChunks;
		} else {
			state = file_End;
		}
		break;
	case file_ReadNumberOfChunks:
		NumberOfChunks = SetChunkSize(200);
	//	printf("Number of chunks = %I64d\n",NumberOfChunks);
		state = file_SendChunks;
		break;

	case file_SendChunks:
//		printf("Sending Chunks\n");
		SendChunks(NumberOfChunks);
		state = file_End;
		break;
	case file_End:
		state = file_Init;
		NumberOfChunks=0;
		ReadEnd();
		ret = false;
		break;
	}
	return ret;
}

bool SendFileRequest(void) {

	packet_t data;
	int j=0;
	bool ret;
	printf("Please Enter The full path to the file:\n");
	do {
		scanf("%c", &filePath[j]);
		j++;
	} while ((j < 400) && (filePath[j - 1] != '\n'));

	j--;
	filePath[j] = 0;
	//Sending file transmit request
	data.type = type_fileSendRequest;
	GetFileName(filePath);
	printf("Sending \"%s%s\"\n", fileName, extension);
//	printf("%s",filePath);
	ret = InitRead(filePath);

	strclr(FullFileName, sizeof(FullFileName));
	strcpy(FullFileName, fileName);
	strcat(FullFileName, extension);
	strcpy(data.data, FullFileName);
	SendData(data);
	return ret;
}

void SendChunks(uint64_t NumberOfChunks) {
	int i;
	packet_t packet;
	char Chunk[200];
	uint8_t NumberOfBytes;
	printf("Number of Chunks = %I64d\n",NumberOfChunks);
	for (i = 1; i <= NumberOfChunks; i++) {
		NumberOfBytes = GetChunk(i, Chunk);
		packet.type=type_fileSendChunk;
		packet.ChunkSize=NumberOfBytes;
		packet.ChunkNumber=i;
		memcpy(packet.data,Chunk,sizeof(NumberOfBytes));
		printf("The data is %*.s\n",NumberOfBytes,Chunk);
		SendData(packet);
		printf("Sending Chunk Number %d\n",i);
	}
	packet.type = type_fileEnd;
	SendData(packet);
}
