#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "network.h"
#include "matrix.h"


double get_random()
{
    return (double)rand()/(double)(RAND_MAX);
}

void layer_init_random(struct Layer *l)
{
    matrix_map_inplace(l->weights, *get_random);
    matrix_map_inplace(l->biases, *get_random);
}

void layer_alloc(struct Layer *l, size_t nb_in, size_t nb_neurons)
{
    l->nb_neurons = nb_neurons;
    l->in = matrix_init(nb_in, 1);
    l->weights = matrix_init(nb_neurons, nb_in);
    l->biases = matrix_init(nb_neurons, 1);
    l->out = matrix_init(nb_neurons, 1);
    l->delta = matrix_init(nb_neurons, 1);

    layer_init_random(l);
}

void layer_free(struct Layer *l)
{
    matrix_free(l->in);
    matrix_free(l->out);
    matrix_free(l->weights);
    matrix_free(l->biases);
    matrix_free(l->delta);
}

struct Network *network_alloc(size_t nb_layers, size_t *layers_size)
{
    struct Network *net = malloc(sizeof(struct Network));

    net->nb_layers = nb_layers;
    net->layers = malloc(sizeof(struct Layer) * nb_layers);
    for (size_t i = 0; i < nb_layers; ++i)
    {
        if (!i)
        {
            layer_alloc(&net->layers[i], 0, layers_size[i]);
            continue;
        }

        layer_alloc(&net->layers[i], layers_size[i - 1], layers_size[i]);
    }

    return net;
}

void network_free(struct Network *net)
{
    for (size_t i = 0; i < net->nb_layers; ++i)
        layer_free(&net->layers[i]);
    free(net->layers);
    free(net);
}

double sigmoid(double x)
{
    return 1. / (1. + exp(-x));
}

double sigmoid_deriv(double x)
{
    return sigmoid(x) * (1 - sigmoid(x));
}
