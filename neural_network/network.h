#ifndef NETWORK_H
#define NETWORK_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "matrix.h"

struct Layer {
    size_t nb_neurons;
    struct Matrix *in;
    struct Matrix *out;
    struct Matrix *weights;
    struct Matrix *biases;
    struct Matrix *delta;
};

struct Network {
    size_t nb_layers;
    struct Layer *layers;
};

struct Network *network_alloc(size_t nb_layers, size_t *layers_size);
void network_free(struct Network *net);

double sigmoid(double x);
double sigmoid_deriv(double x);

#endif
