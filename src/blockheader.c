#include <stdio.h>
#include "blockheader.h"

void print_blocks(BlockHeader *root)
{
    if (root == NULL) 
    {
        printf("\nprint_blocks: NULL pointer\n");
        return;
    }
    
    BlockHeader *current = root;

    int i = 0;
    printf("\n");
    while (current != NULL)
    {   
        char *state = current->free? "FREE": "OCCUPIED";
        printf("| BLOCK %i: %s %i |", i, state, current->size);
        current = current->next;
        i++;
    }
    printf("\n");
}