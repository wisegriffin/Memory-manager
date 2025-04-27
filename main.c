#include <stdio.h>
#include "my_memory.h"
#include "blockheader.h"


int main(int argc, char const *argv[])
{

    init_memory();
    print_blocks(block_list);
    return 0;
}

