#ifndef BLOCKHEADER_H
#define BLOCKHEADER_H

#include <stddef.h>

typedef struct block_header_t
{
    size_t size;
    struct block_header_t *next;
} block_header_t;

#endif