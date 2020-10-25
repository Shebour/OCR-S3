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

void layer_backward(struct Layer *prev, struct Layer *cur)
{
    matrix_free(prev->delta);

    struct Matrix *wT = matrix_T(cur->weights);
    struct Matrix *wT_dot_delta = matrix_mult(wT, cur->delta);
    struct Matrix *sig_in = matrix_map(prev->in, *sigmoid);

    prev->delta = matrix_mult_each(wT_dot_delta, sig_in);

    matrix_free(wT);
    matrix_free(sig_in);
    matrix_free(wT_dot_delta);
}

void network_backward(struct Network *net)
{
    for (int i = net->nb_layers - 2; i >= 0; --i)
        layer_backward(&net->layers[i], &net->layers[i + 1]);
}
