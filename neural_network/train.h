#ifndef TRAIN_H
#define TRAIN_H

#include <stdlib.h>
#include "network.h"
#include "netdata.h"

struct TrainMeta {
    size_t nb_nd;
    size_t nb_epochs;
    size_t mini_batch_size;
    double learn_rate;
    double regularization_rate;
};

void gradient_descent(
    struct Network *net,
    struct TrainMeta p,
    struct NetData *train_nd,
    struct NetData *validation_nd,
    int verbose
);

#endif
