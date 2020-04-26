#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <fileH.h>


FILE * pFile;
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
	if (ChunkNumber <= NumberOfChunks)
	{
		fseek(pFile,ChunkSize*(ChunkNumber-1),SEEK_SET);
	}
	fread(Chunk,1,ChunkSize,pFile);
	return ChunkNumber;
}
void ReadEnd(void){

	 fclose (pFile);
}
