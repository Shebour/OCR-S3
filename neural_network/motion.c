#include "motion.h"

void layer_forward(struct Layer *prev, struct Layer *cur)
{
    matrix_free(cur->in);
    matrix_free(cur->out);

    struct Matrix *w_dot_out = matrix_mult(cur->weights, prev->out);

    cur->in = matrix_add(w_dot_out, cur->biases);
    cur->out = matrix_map(cur->in, *sigmoid);

    matrix_free(w_dot_out);
}

void network_forward(struct Network *net, struct Matrix *in)
{
    struct Layer *in_layer = &net->layers[0];
    matrix_free(in_layer->out);
    matrix_free(in_layer->in);
    in_layer->in = matrix_copy(in);
    in_layer->out = matrix_copy(in);

    for (size_t i = 1; i < net->nb_layers; ++i)
        layer_forward(&net->layers[i - 1], &net->layers[i]);
}
