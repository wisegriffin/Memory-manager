#include <stdio.h>
#include "memory_manager.h"


int main(int argc, char const *argv[])
{

    init_memory();
    print_memory_map();
    // Teste
    char *palavra = (char*) malloc(20 * sizeof(char));
    print_memory_map();
    free(palavra);
    print_memory_map();

    
    return 0;
}

