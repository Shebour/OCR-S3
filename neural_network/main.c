#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "network.h"

#define LABEL_COLOR "\x1B[93m"
#define RESET_COLOR "\x1B[0m"

int main(void)
{
    static size_t layers_size[] = {4, 16, 4};

    struct Network *net = network_alloc(3, layers_size);

    for (size_t i = 0; i < net->nb_layers; ++i)
    {
        printf(LABEL_COLOR "layer%lu\nnet.layers[%lu]->in\n" RESET_COLOR, i, i);
        matrix_print(net->layers[i].in);
        printf(LABEL_COLOR "net->layers[%lu].weights\n" RESET_COLOR, i);
        matrix_print(net->layers[i].weights);
        printf(LABEL_COLOR "net->layers[%lu].biases\n" RESET_COLOR, i);
        matrix_print(net->layers[i].biases);
    }

    network_free(net);
    return EXIT_SUCCESS;
}
