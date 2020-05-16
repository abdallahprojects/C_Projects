#define MAIN_C_
#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "fileH.h"
#include "NET.h"
#include "main.h"
#include "main_local.h"

int main() {
	HANDLE ThreadHandle;
	DWORD ThreadId;
	ReadMyName();
	NET_ClientInit(9998, "127.0.0.1");
	ThreadHandle = CreateThread( NULL, /* default security attributes */0, /* default stack size */
	receiver, /* thread function */NULL, /* parameter to thread function */0, /* default creation    flags */
	&ThreadId);
	SendConnectRequest();
	sender();
	TerminateThread(ThreadHandle, 0);
	NET_CloseSocket();

	return 0;
}

DWORD WINAPI receiver(LPVOID Param) {

	packet_t x;
	uint64_t TotalNumberOfChunks;

	while (1) {
		NET_ReceiveData(&x);
		switch (x.type) {

		case type_connect:
			memcpy(username, x.data, strlen(x.data));
			printf("%s is connected, Say Hi!\n", username);
			mynameFlag = 0;
			break;

		case type_text:
			printf("%s: %s\n", username, x.data);
			break;

		case type_disconnect:
			printf("%s disconnected.\n", username);
			break;

		case type_fileSendRequest:
			printf("receiving %s\n", x.data);
			InitWrite(x.data);
			break;

		case type_fileSendSize:
			TotalNumberOfChunks = x.ChunkNumber;
			break;

		case type_fileSendChunk:
			WriteChunk(x.ChunkSize, x.data);
			printf("\r%I64d%%", (x.ChunkNumber * 100) / TotalNumberOfChunks);
			break;

		case type_fileEnd:
			WriteEnd();
			printf("\nFile received!\n");
			break;

		default:
			printf("unexpected protocol..!\n");

		}

	}
}
static void sender(void) {
	packet_t data;
	int i;
	char text[200];
	while (1) {
		i = 0;
		memset(text, 0, 200);
		do {
			scanf("%c", &text[i]);
			i++;
		} while ((i <= 200) && (text[i - 1] != '\n'));
		text[i - 1] = 0;
		if (!strcmp(text, "quit") || !strcmp(text, "QUIT")) {
			printf("Exiting Application and Terminating receiver thread!");
			break;
		} else if (!strcmp(text, "file")) {
			while (FileStateMachine())
				;
		} else {
			memset(&data, 0, sizeof(data));
			memcpy(data.data, text, i);
			data.type = type_text;
			NET_SendData(&data);
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
	printf("Hello %s!\n", myname);

}
void SendConnectRequest(void) {
	packet_t x;
	memset(&x, 0, sizeof(x));
	x.type = type_connect;
	memcpy(x.data, myname, strlen(myname));

	while (mynameFlag) //while I didn't receive server name
	{
		NET_SendData(&x); // Send my name again
		Sleep(200);
	}

}
//C:\hello.tx
void GetFileName(char filePath[400], uint32_t size) {
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

	} while ((ch != '\\') && (ch != '.') && (i < 10) && (len != -1));

	if ((ch != '.') || (len == 0)) {
		//printf("No File Extension\n");
		// no file extension
		extension[i] = 0;
		strcpy(fileName, strrev(extension));
		memset(extension, 0, sizeof(extension));
		return;
	}
//extracting fileName
	i = 0;
	memset(fileName, 0, sizeof(fileName));
	do {
		ch = filePath[len--];
		fileName[i++] = ch;

	} while (((ch != '\\') && (ch != 0)) && (i < 50));
	fileName[i - 1] = 0;

	if (i >= 50) {
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
	static uint64_t NumberOfChunks = 0;
	bool ret = true;
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
		SendFileSize(NumberOfChunks);
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
		NumberOfChunks = 0;
		ReadEnd();
		ret = false;
		break;
	}
	return ret;
}

bool SendFileRequest(void) {

	packet_t data;
	int j = 0;
	bool ret;
	char buff = 0;
	printf("Please Enter The full path to the file:\n");
	do {
		scanf("%c", &buff);
		if ((buff != '"') && buff != '\'') {
			filePath[j] = buff;
			j++;
		}
	} while ((j < 400) && (filePath[j - 1] != '\n'));

	j--;
	filePath[j] = 0;
	//Sending file transmit request
	data.type = type_fileSendRequest;
	GetFileName(filePath, j);
	printf("Sending \"%s%s\"\n", fileName, extension);
//	printf("%s",filePath);
	ret = InitRead(filePath);

	strclr(FullFileName, sizeof(FullFileName));
	strcpy(FullFileName, fileName);
	strcat(FullFileName, extension);
	strcpy(data.data, FullFileName);
	NET_SendData(&data);
	return ret;
}

void SendFileSize(uint64_t TotalNumberOfChunks) {

	packet_t packet;

	packet.type = type_fileSendSize;
	packet.ChunkNumber = TotalNumberOfChunks;
	NET_SendData(&packet);
}

void SendChunks(uint64_t NumberOfChunks) {
	int i;
	packet_t packet;
	char Chunk[200];
	memset(Chunk, 0, 200);
	uint8_t NumberOfBytes;
	//printf("Number of Chunks = %I64d\n",NumberOfChunks);
	for (i = 1; i <= NumberOfChunks; i++) {
		NumberOfBytes = GetChunk(i, Chunk);
		memset(&packet, 0, sizeof(packet_t));
		packet.type = type_fileSendChunk;
		packet.ChunkSize = NumberOfBytes;
		packet.ChunkNumber = i;
		memcpy(packet.data, Chunk, (NumberOfBytes));
		//printf("The data is %.*s\n",NumberOfBytes,Chunk);
		NET_SendData(&packet);
		//printf("Sending Chunk Number %d\n",i);
		printf("\r%I64d%%", (i * 100) / NumberOfChunks);

	}
	packet.type = type_fileEnd;
	NET_SendData(&packet);
	printf("\nFile sent!\n");
}
