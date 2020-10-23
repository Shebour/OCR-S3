#include <stdio.h>
#include <stdlib.h>
#include "network.h"

int main(void)
{
    static size_t layers_size[] = {4, 16, 4};

    struct Network *net = network_alloc(3, layers_size);
    network_free(net);
    return EXIT_SUCCESS;
}
