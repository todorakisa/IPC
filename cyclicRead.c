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
    uint32_t seed = 0;
    uint32_t true_seed = seed;
	printf("starting at %ld\n", position);
    int i=0;
    while(true){
        while(memory -> position != position)
	    seed = verify((void *)memory->array[position]);
	    if(i == 0){
		    true_seed = seed;
    	    }else if(true_seed + 1 != seed){
            	printf("Error");
	    }
	    true_seed++;
	    i = 1;
            printf("Veryfy array[%ld] - seed:%ld\n",position,seed);
            position ++;
            position %=COUNT;
        }
    }
    
    
	return 0;
}
