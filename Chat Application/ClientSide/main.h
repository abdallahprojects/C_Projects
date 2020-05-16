/*
 * main.h
 *
 *  Created on: May 16, 2020
 *      Author: abHelal
 */

#ifndef MAIN_H_
#define MAIN_H_

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
void GetFileName(char filePath[400],uint32_t size);
bool FileStateMachine(void);
bool SendFileRequest(void);
void SendFileSize(uint64_t TotalNumberOfChunks);
void SendChunks(uint64_t NumberOfChunks);
void Menu(void);


#endif /* MAIN_H_ */
