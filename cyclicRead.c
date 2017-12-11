#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "gen.h"
#include "gen.c"
#include "cyclicBuf.h"


int main()
{
	int memFd = shm_open( "simple_memory", O_RDONLY, 0 );
	if( memFd == -1 )
	{
		perror("Can't open file");
		return 1;
	}

	struct buffer* memory = mmap( NULL, sizeof(struct buffer), PROT_READ, MAP_SHARED, memFd, 0 );
	if( memory == NULL )
	{
		perror("Can't mmap");
		return 1;
	}
    
    uint64_t position = memory->position;
    uint32_t seed;
	printf("starting at %ld\n", position);
    while(true){
        while(memory -> position != position){
            printf("Veryfy array[%ld] - seed:%ld\n",position,verify((void *)memory->array[position]));
            position ++;
            position %=COUNT;
        }
    }
    
    
	return 0;
}
