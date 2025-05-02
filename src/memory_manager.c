#include "memory_manager.h"
#include "buddy.h"
#include <stdio.h>
#include <stdint.h>

#define MAX_ORDER 10

// 1Kb
static unsigned char memory[MEMORY_SIZE];

static block_header_t *block_list = (block_header_t *)memory;
static block_header_t *free_list[MAX_ORDER + 1] = {NULL};

static block_header_t *smallest_free_block(size_t size);
static int remove_block(block_header_t *target);
static int add_block(block_header_t *target, int order);
static block_header_t *split(block_header_t *target, size_t request_size, int order);


void init_memory()
{
    block_list->free = 1;
    block_list->size = MEMORY_SIZE - sizeof(block_header_t);
    block_list->next = NULL;
    free_list[MAX_ORDER] = block_list;
}

void *my_malloc(size_t size)
{
    // ALERT: IMPLEMENT THIS
    /*  block_header_t *current = block_list;

     while (current != NULL)
     {
         if (current->free && current->size >= size)
         {
             void *data = (void *)(current + 1);
             printf("allocating %p...\n", data);
             current->free = 0;
             return data;
         }
         current = current->next;
     } */
    
    block_header_t *block = smallest_free_block(size + sizeof(block_header_t));
    size_t total_block_size = block->size + sizeof(block_header_t);

    if (!block)
    {
        printf("Cant find free blocks\n");
    }
    if (block->size > size)
    {
        block_header_t *splitted_block;
        splitted_block = split(block, size, get_order(total_block_size));
    }
    return NULL;
}

void my_free(void *ptr)
{
    // ALERT: IMPLEMENT THIS
    printf("freeing %p...\n", ptr);

    if (!ptr)
        return;

    block_header_t *block = ((block_header_t *)ptr) - 1;

    if ((void *)block < (void *)memory || (void *)block >= (void *)(memory + MEMORY_SIZE))
    {
        fprintf(stderr, "Error: invalid pointer\n");
        return;
    }
    block->free = 1;
}

void print_memory_map()
{
    block_header_t *current = block_list;

    if (!current)
    {
        printf("\nprint_blocks: NULL pointer\n");
        return;
    }

    int i = 0;
    printf("\n");
    while (current != NULL)
    {
        char *state = current->free ? "FREE" : "OCCUPIED";
        printf("| BLOCK %i: %s %i |", i, state, current->size);
        current = current->next;
        i++;
    }
    printf("\n");
}

static block_header_t *smallest_free_block(size_t size)
{
    block_header_t *current;
    for (int i = 0; i <= MAX_ORDER; i++)
    {
        current = free_list[i];
        printf("%p ", current);
        if (!current)
            continue;
        printf("%d ", order_to_number(i));
        if (order_to_number(i) >= size)
            printf("The block fits!\n");
            return current;
    }
    // There is no free blocks
    if (!current)
        return NULL;
}

static block_header_t *split(block_header_t *target, size_t request_size, int order)
{
    if (!target)
    {
        printf("Null pointer\n");
        return NULL;
    }
    if (remove_block(target) == 0)
    {
        size_t block_header_t_size = sizeof(block_header_t);
        size_t new_size = (target->size + block_header_t_size) / 2;

        // Splitted block size is insuficient, split cancelled
        if (new_size - block_header_t_size < request_size) return target;

        target->size = new_size - block_header_t_size;

        printf("New size: %d\n", new_size);

        // Create buddy
        uintptr_t buddy_address = ((uintptr_t)target) + new_size;
        block_header_t *buddy = (block_header_t*)buddy_address;
        buddy->size = new_size - block_header_t_size;      
        
        printf("Buddy at order %d: %p\n", order - 1, buddy);

        add_block(target, order - 1);
        add_block(buddy, order - 1);

        split(target, request_size, order - 1);
    }
    else
    {
        printf("Split failed\n");
        return NULL;
    }
    
}

// Remove target block from free_list
static int remove_block(block_header_t *target)
{
    if (!target)
    {
        printf("Null pointer\n");
        return 1;
    }

    int order = get_order(target->size + sizeof(block_header_t));
    printf("Order: %d %p\n", order, target);
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
        printf("Cant find target block\n");
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
static int add_block(block_header_t *target, int order)
{
    if (!target) return 1;

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


