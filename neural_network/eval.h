#ifndef EVAL_H
#define EVAL_H

#include "network.h"
#include "train.h"

struct Matrix *network_run(
    struct Network *net,
    struct Matrix *inputs
);

void network_eval(
    struct Network *net,
    struct TrainMeta meta,
    struct NetData *nd,
    const char *nd_name
);

double network_evaluate_accuracy(struct Network *net, struct NetData *nd);
double network_evaluate_cost(
    struct Network *net,
    struct TrainMeta meta,
    struct NetData *nd
);

#endif
