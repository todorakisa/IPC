#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "gen.h"
#include "cyclicBuf.h"


int main()
{
	int memFd = shm_open( "simple_memory", O_RDONLY, 0 );
	if( memFd == -1 )
	{
		perror("Can't open file");
		return 1;
	}

	struct cyclic_buf* mem = mmap( NULL, sizeof(struct cyclic_buf), PROT_READ, MAP_SHARED, memFd, 0 );
	if( mem == NULL )
	{
		perror("Can't mmap");
		return 1;
	}
    
    uint64_t pos = mem->pos;
    uint32_t seed;
	printf("starting at %ld\n", pos);
    while(true){
        if(mem -> pos == pos){
            continue;
        }
        printf("Veryfy array[%ld] - seed:%ld\n",pos,verify((void *)mem->array[pos]));
        pos ++;
        pos %=_BLOCK_COUNT;
    }
    
    
	return 0;
}
