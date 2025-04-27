#ifndef MY_MEMORY_H
#define MY_MEMORY_H

#include "blockheader.h"

#define MEMORY_SIZE 1024

extern char memory[MEMORY_SIZE];
extern BlockHeader *block_list = (BlockHeader*) memory;

void init_memory();

#endif