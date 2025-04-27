#ifndef BLOCKHEADER_H
#define BLOCKHEADER_H

#include <stddef.h>

typedef struct BlockHeader
{
    size_t size;
    int free;
    struct BlockHeader *next;
} BlockHeader;

#endif