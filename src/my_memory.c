#include "my_memory.h"
#include "blockheader.h"

char memory[MEMORY_SIZE];
BlockHeader *block_list = (BlockHeader*) memory;

void init_memory()
{
    block_list->free = 1;
    block_list->size = MEMORY_SIZE - sizeof(BlockHeader);
    block_list->next = NULL;
}