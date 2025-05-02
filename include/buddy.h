#ifndef BUDDY_H
#define BUDDY_H

#include "blockheader.h"

block_header_t *split(block_header_t *target, size_t request_size, int order);
int merge(block_header_t *target, int order);

#endif