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
    uint32_t true_seed;
	printf("starting at %ld\n", position);
    int i=0;
    while(true){
        while(memory -> position != position){
	        seed = verify((void *)memory->array[position %=COUNT]);
	        if(seed==-1){
		        printf("Error in verify\n");
	        }
	        if(memory->position > position + COUNT ){
	            printf("Preskachane");
	            return 1;
	        }
	        if(i=0){
            	true_seed=seed;
                i = 1;
	        }else if(true_seed + 1 == seed){
	            printf("Error in seed");
	        }else{
           		true_seed++;
	        }
            printf("Veryfy array[%ld] - seed:%d\n",position %=COUNT,seed);
            position ++;
        }
    }  
	return 0;
}
