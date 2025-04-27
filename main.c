#include <stdio.h>
#include "my_memory.h"
#include "blockheader.h"


int main(int argc, char const *argv[])
{

    BlockHeader *free_block = (BlockHeader *)memory;
    free_block->free = 1;
    free_block->size = MEMORY_SIZE - sizeof(BlockHeader);
    free_block->next = NULL;

    printf("Size: %i\n", free_block->size);
    print_blocks(free_block);
    return 0;
}

