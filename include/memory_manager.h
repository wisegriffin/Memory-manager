#ifndef MY_MEMORY_H
#define MY_MEMORY_H

#include "blockheader.h"

#define MEMORY_SIZE 1024

void init_memory();
void print_memory_map();

void *malloc(size_t size);
void free(void *ptr);

#endif