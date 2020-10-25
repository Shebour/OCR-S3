#include <math.h>
#include "eval.h"

double network_cost(
    struct Network *net,
    struct NetData *nd
)
{
    double cost = 0.;

    for (size_t rd_id = 0; rd_id < nd->nb_data; ++rd_id)
    {
        struct Matrix *net_in = nd->raw_data[rd_id].in;
        struct Matrix *expected_out = nd->raw_data[rd_id].out;

        struct Matrix *net_out = network_run(net, net_in);
        double sigma_rd = 0.;

        for (size_t i = 0; i < net_out->rows; ++i)
        {
            double a_i = matrix_get(net_out, i, 0);
            double y_i = matrix_get(expected_out, i, 0);
            double v = y_i * log(a_i) + (1 - y_i) * log(1 - a_i);
            if (!isnan(v))
                sigma_rd += v;
        }
        cost += sigma_rd;
    }

    cost *= -1. / nd->nb_data;
    return cost;
}

double network_regularization_cost(
    struct Network *net,
    struct TrainMeta meta,
    struct NetData *nd
)
{
    double cost = 0.;

    for (size_t i = 0; i < net->nb_layers; ++i)
    {
        struct Layer *layer = &net->layers[i];
        struct Matrix *weights = layer->weights;

        double weight_sum = 0.;
        for (size_t i = 0; i < weights->rows; ++i)
            for (size_t j = 0; j < weights->cols; ++j)
                weight_sum = matrix_get(weights, i, j) * matrix_get(weights, i, j);
        cost += weight_sum;
    }

    cost *= meta.regularization_rate / (2. * nd->nb_data);
    return cost;
}

double network_evaluate_cost(
    struct Network *net,
    struct TrainMeta meta,
    struct NetData *nd
)
{
    double sum_cost = network_cost(net, nd);
    double sum_regularization = network_regularization_cost(net, meta, nd);

    return sum_cost + sum_regularization;
}
