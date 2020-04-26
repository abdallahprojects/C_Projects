#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <fileH.h>


int main (void)

{	uint64_t numberChunks;
	InitRead("C:\\Users\\abHelal\\Desktop\\Abdallah.txt");
	numberChunks = SetChunkSize(5);
	printf("the number of chunks is :%I64d\n",numberChunks);

	return 0;
}
