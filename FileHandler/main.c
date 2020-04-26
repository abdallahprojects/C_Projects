#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <fileH.h>

int main (void)

{	int i;
	uint64_t NumberOfBytes;
	uint64_t numberChunks;
	char Chunk[200];
	InitRead("C:\\Users\\abHelal\\Desktop\\C_Projects\\FileHandler\\FileHandler.exe");
	InitWrite("C:\\Users\\abHelal\\Desktop\\C_Projects\\FileHandler\\FileHandler2.exe");
	numberChunks = SetChunkSize(200);
	printf("the number of chunks is :%I64d\n",numberChunks);
	for (i = 1 ;i <= (numberChunks) ; i++){
		NumberOfBytes = GetChunk(i,Chunk);
		WriteChunk(NumberOfBytes,Chunk);
		//printf("%.*s",NumberOfBytes,Chunk);
	}
	printf("the number of bytes is :%I64d\n",NumberOfBytes);
	return 0;
}

