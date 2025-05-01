#ifndef MY_MEMORY_H
#define MY_MEMORY_H

#include "blockheader.h"

#define MEMORY_SIZE 1024

void init_memory();
void print_memory_map();

void *my_malloc(size_t size);
void my_free(void *ptr);

#endif