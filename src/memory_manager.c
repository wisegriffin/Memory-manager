#include "memory_manager.h"
#include "buddy.h"
#include "free_list_manager.h"
#include "order.h"
#include <stdio.h>

// 1Kb
static unsigned char memory[MEMORY_SIZE];
static int initialized = 0;

static void init_memory()
{
    block_header_t *root = (block_header_t *)memory;
    root->next = NULL;
    root->size = MEMORY_SIZE - sizeof(block_header_t);
    add_block(root, MAX_ORDER);
}

// ALERT: Free pointers allocked by my_malloc ONLY with my_free()
void *my_malloc(size_t size)
{
    if (!initialized)
    {
        init_memory();
        initialized = 1;
    }

    block_header_t *block = smallest_free_block(size + sizeof(block_header_t));
    size_t total_block_size = block->size + sizeof(block_header_t);

    if (!block)
    {
        return NULL;
    }
    if (block->size > size)
    {
        block = split(block, size, get_order(total_block_size));
    }
    void *data = (void *)(block + 1);
    return data;
}

// ALERT: Use ONLY to free pointers with my_malloc()
void my_free(void *ptr)
{
    if (!ptr)
        return;

    block_header_t *block = ((block_header_t *)ptr) - 1;

    // Checks if pointer to block is out of memory vector
    if ((void *)block < (void *)memory || (void *)block >= (void *)(memory + MEMORY_SIZE))
    {
        return;
    }

    size_t total_size = block->size + sizeof(block_header_t);
    int order = get_order(total_size);

    if (merge(block, order) == 0)
        return;

    add_block(block, order);
}


void print_memory_map()
{
    printf("\n==| M E M O R Y  M A P |==\n\n");
    for (size_t i = 0; i <= MAX_ORDER; i++)
    {
        block_header_t *current = get_list(i);
        printf("ORDER %d (%d): ", i, order_to_number(i));

        int count = 0;
        while (current != NULL)
        {
            printf("| Block %d |", count);
            current = current->next;
            count++;
        }
        if (count == 0)
            printf("empty");
        printf("\n");
    }
    printf("\n");
}
