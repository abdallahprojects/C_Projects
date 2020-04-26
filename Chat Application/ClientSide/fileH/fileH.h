
bool InitRead(char *filePath);
bool InitWrite(char *filePath);
uint64_t SetChunkSize(uint8_t size);
uint64_t GetChunk(uint64_t ChunkNumber,char * Chunk);
void WriteChunk(uint8_t size, char * Chunk);
void WriteEnd(void);
void ReadEnd(void);
