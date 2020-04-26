#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <fileH.h>


FILE * pFile;
FILE * pFileW;
uint64_t lSize;
uint64_t NumberOfChunks;
uint8_t ChunkSize;






// Try to open the file & return true if the file exists, Otherwise return false.
bool InitRead(char *filePath) {

	pFile = fopen(filePath, "rb");
	if (pFile == NULL) {
		printf("File doesn't exist\n");
		return false;
	} else {
		return true;
	}

}



// Return the numbers of chunks in respect to the chunk-size
uint64_t SetChunkSize(uint8_t size) {
	ChunkSize = size;
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);
	NumberOfChunks = (lSize%size)? (lSize/size)+1:(lSize/size);
	return NumberOfChunks;
}
// Return the selected chunk from 1 to NumberOfChunks
uint64_t GetChunk(uint64_t ChunkNumber,char * Chunk)
{
	uint64_t NumberOfBytes;
	if (ChunkNumber <= NumberOfChunks)
	{
		fseek(pFile,ChunkSize*(ChunkNumber-1),SEEK_SET);
	}
	NumberOfBytes = fread(Chunk,1,ChunkSize,pFile);
	return NumberOfBytes;
}
void ReadEnd(void){

	 fclose (pFile);
}


bool InitWrite(char *filePath){
	pFileW = fopen(filePath,"wb+");
	if(pFileW == NULL){
		printf("Can't creat the file\n");
		return false;
	} else {
		return true;
	}
}

void WriteEnd(void){
	 fclose (pFileW);
}


void WriteChunk(uint8_t size, char * Chunk){
	fwrite(Chunk,1,size,pFileW);
}

