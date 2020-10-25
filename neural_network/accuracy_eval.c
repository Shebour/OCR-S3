#include "eval.h"

int is_network_correct(
    struct Network *net,
    struct Matrix *net_in,
    struct Matrix *expected_out
)
{
    struct Matrix *net_out = network_run(net, net_in);

    return (matrix_max(net_out) == matrix_max(expected_out));
}

double network_evaluate_accuracy(
    struct Network *net,
    struct NetData *nd
)
{
    size_t nb_correct = 0;
    for (size_t i = 0; i < nd->nb_data; ++i)
    {
        struct RawData *rd = &nd->raw_data[i];
        if (is_network_correct(net, rd->in, rd->out))
            ++nb_correct;
    }

    double pct = 100. * nb_correct / nd->nb_data;
    return pct;
}
