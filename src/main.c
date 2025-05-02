#include <stdio.h>
#include "memory_manager.h"


int main(int argc, char const *argv[])
{
    init_memory();
    my_malloc(50);
    return 0;
}

