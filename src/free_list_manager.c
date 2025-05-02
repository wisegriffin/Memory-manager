#include "free_list_manager.h"
#include "order.h"

static block_header_t *free_list[MAX_ORDER + 1] = {NULL};

block_header_t *get_list(int order)
{
    if (order > MAX_ORDER)
        return NULL;
    return free_list[order];
}

// Remove target block from free_list
int remove_block(block_header_t *target)
{
    if (!target)
    {
        return 1;
    }

    int order = get_order(target->size + sizeof(block_header_t));
    block_header_t *current = free_list[order];
    block_header_t *previous = NULL;

    // Finds target
    while (current != NULL && current != target)
    {
        previous = current;
        current = current->next;
    }
    if (!current)
    {
        return 1;
    }

    if (!current->next)
    {
        // The target is the first node
        if (!previous)
        {
            free_list[order] = NULL;
        }
        // Target is the last node
        else
        {
            previous->next = NULL;
        }
    }
    // Target is in the middle
    else
    {
        previous->next = current->next;
    }

    return 0;
}

// Add target block to head of free_list[order]
int add_block(block_header_t *target, int order)
{
    if (!target)
        return 1;

    // List is empty
    if (free_list[order] == NULL)
    {
        free_list[order] = target;
    }
    else
    {
        target->next = free_list[order];
        free_list[order] = target;
    }
    return 0;
}

// Return the smallest free block that fits size
block_header_t *smallest_free_block(size_t size)
{
    block_header_t *current;
    for (int i = 0; i <= MAX_ORDER; i++)
    {
        current = free_list[i];
        if (!current)
            continue;
        if (order_to_number(i) >= size)
        return current;
    }
    // There is no free blocks
    if (!current)
        return NULL;
}
