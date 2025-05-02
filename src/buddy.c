#include "buddy.h"
#include "free_list_manager.h"
#include <stdint.h>

// Split target RECURSIVELY until it better fits request_size
block_header_t *split(block_header_t *target, size_t request_size, int order)
{

    if (!target)
    {
        return NULL;
    }
    if (remove_block(target) == 0)
    {
        size_t block_header_t_size = sizeof(block_header_t);
        size_t new_size = (target->size + block_header_t_size) / 2;

        // Splitted block size is insuficient, split cancelled
        if (new_size - block_header_t_size < request_size)
            return target;

        target->size = new_size - block_header_t_size;


        // Create buddy
        uintptr_t buddy_address = ((uintptr_t)target) + new_size;
        block_header_t *buddy = (block_header_t *)buddy_address;
        buddy->size = new_size - block_header_t_size;

        add_block(target, order - 1);
        add_block(buddy, order - 1);

        split(target, request_size, order - 1);
    }
    else
    {
        return NULL;
    }
}

// Merge target with his buddy, return 0 if sucessful
int merge(block_header_t *target, int order)
{
    size_t total_target_size = target->size + sizeof(block_header_t);
    uintptr_t buddy = (uintptr_t)target ^ total_target_size;

    // Buddy does not exist
    if ((block_header_t *)buddy == NULL)
        return 1;

    size_t total_buddy_size = ((block_header_t *)buddy)->size + sizeof(block_header_t);

    // Target and buddy are not in the same order
    if (total_target_size != total_buddy_size)
        return 1;

    // Buddy is in free list
    if (remove_block((block_header_t *)buddy) == 0)
    {
        target->size = (total_target_size * 2) - sizeof(block_header_t);
        add_block(target, order + 1);
        return 0;
    }
    return 1;
}