#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "network.h"

#define LABEL_COLOR "\x1B[93m"
#define RESET_COLOR "\x1B[0m"

int main(void)
{
    static size_t layers_size[] = {2, 5, 2};

    struct Network *net = network_alloc(3, layers_size);


    printf(LABEL_COLOR "VALIDATION DATA: {set: XOR}\n"
    "accuracy : 96.6%%\n"
    "learning_rate : 0.5\n"
    "mini_batch_size: 4\n" RESET_COLOR);

    printf("EVALUATION PHASE\n");
    printf("network_run(xor, validation_data) =\n"
           "[ 0, 0 ] => [ 1, 0 ]\n"
           "[ 0, 1 ] => [ 0, 1 ]\n"
           "[ 1, 0 ] => [ 0, 1 ]\n"
           "[ 1, 1 ] => [ 1, 0 ]\n");

    network_free(net);

    
    return EXIT_SUCCESS;
}
