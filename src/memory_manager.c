#include "memory_manager.h"
#include <stdio.h>

static unsigned char memory[MEMORY_SIZE];
static block_header_t *block_list = (block_header_t *)memory;

void init_memory()
{
    block_list->free = 1;
    block_list->size = MEMORY_SIZE - sizeof(block_header_t);
    block_list->next = NULL;
}

void *my_malloc(size_t size)
{
    block_header_t *current = block_list;

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
    }
    return NULL;
}

void my_free(void *ptr)
{
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