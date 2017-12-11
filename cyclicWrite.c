#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include "cyclicBuf.h"
#include "gen.h"
#include "gen.c"

int main()
{
	int memFd = shm_open( "simple_memory", O_CREAT | O_RDWR, S_IRWXU );
	if( memFd == -1 )
	{
		perror("Can't open file");
		return 1;
	}

	int resize;
	resize = ftruncate( memFd, sizeof(struct buffer) );
	if( resize == -1 )
	{
		perror("Can't truncate file");
		return resize;
	}
	
	struct buffer* memory = mmap( NULL, sizeof(struct buffer), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0 );
	if( memory == NULL )
	{
		perror("Can't mmap");
		return -1;
	}
	
    memory->position = 0;
    uint32_t seed = 0;
    while(true) {
		//memory->position++;
		generate((void*)memory->array[memory->position %= COUNT], seed);
		printf("Generate: array[%ld] - seed: %d\n", memory->position %= COUNT,seed);
		memory->position++;
		//memory->position %= COUNT;
		seed++;
    }

	return 0;
}
