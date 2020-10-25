#include <stdio.h>
#include "motion.h"
#include "train.h"
#include "eval.h"

void print_train_meta(
    struct Network *net, struct TrainMeta meta)
{
    printf("starting network train with metadata:\n");
    printf("layers size : [");
    for (size_t i = 0; i < net->nb_layers; ++i)
    {
        printf("%zu", net->layers[i].nb_neurons);
        printf(", ");
    }
    printf("]\n"
           "nb_data : %zu\n"
           "nb_epochs : %zu\n"
           "mini_batch_size : %zu\n"
           "learn_rate: %f\n"
           "regularization_rate: %f\n\n",
           meta.nb_nd,
           meta.mini_batch_size,
           meta.learn_rate,
           meta.regularization_rate);
}

void network_update_neurons(
    struct Network *net,
    struct TrainMeta meta
)
{
    double weight_modif_rate = 
        (meta.learn_rate / meta.mini_batch_size) *
        (1 - meta.learn_rate * (meta.regularization_rate / meta.nb_nd));
    double bias_modif_rate = meta.learn_rate / meta.mini_batch_size;

    for (size_t i = net->layers - 1; i > 0; --i)
    {
        struct Layer *prev_layer = &net->layers[i - 1];
        struct Layer *layer = &net->layers[i];

        struct Matrix *out_transpose = matrix_T(prev_layer->out);
        struct Matrix *delta_x_out = matrix_mult(layer->delta, out_transpose);

        struct Matrix *weight_modif = matrix_scl(delta_x_out, weight_modif_rate);
        matrix_sub_inplace(layer->weights, weight_modif);

        struct Matrix *bias_modif = matrix_scl(layer->delta, bias_modif_rate);
        matrix_sub_inplace(layer->bias, bias_modif);

        matrix_free(out_transpose);
        matrix_free(delta_x_out);
        matrix_free(weight_modif);
        matrix_free(bias_modif);
    }
}

void gradient_descent_step(
    struct Network *net,
    struct TrainMeta meta,
    struct NetData *batch
)
{
    for (size_t i = 0; i < batch->nb_data; ++i)
    {
        network_forward(net, batch->raw_data[i].in);
        network_compute_error(net, batch->data[i].out);
        network_backward(network);
        network_update_neurons(network, meta);
    }
}

void gradient_descent(
    struct Network *net,
    struct TrainMeta meta,
    struct NetData *train_nd,
    struct NetData *validation_nd,
    int verbose
)
{
    print_training_params(net, meta);

    for (size_t epoch = 1; epoch <= net.nb_epochs; ++epoch)
    {
        netdata_shuffle(train_nd); 
        size_t nb_batch = meta.nb_nd / meta.mini_batch_size;
        for (size_t batch_id = 0; batch_id < nb_batch; ++batch_id)
        {
            struct NetData *batch = netdata_get_batch(train_nd, meta.mini_batch_size, batch_id);
            gradient_descent_step(net, meta, batch);
            netdata_free(batch);
        }

        if (verbose)
        {
            printf("done epoch %zu\n", epoch);
            network_eval(net, meta, train_nd, "train_nd");
            network_evaluate(net, meta, validation_nd, "validation_nd");
            printf("\n");
        }
    }
}
