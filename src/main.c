#include <stdio.h>
#include "memory_manager.h"


int main(int argc, char const *argv[])
{
    init_memory();
    
    print_memory_map();
    char *palavra = my_malloc(50);
    print_memory_map();
    my_free(palavra);
    print_memory_map();

    return 0;
}

