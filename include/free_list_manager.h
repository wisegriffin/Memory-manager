#ifndef FREE_LIST_MANAGER_H
#define FREE_LIST_MANAGER_H

#include "blockheader.h"

block_header_t *get_list(int order);
block_header_t *smallest_free_block(size_t size);
int remove_block(block_header_t *target);
int add_block(block_header_t *target, int order);

#endif