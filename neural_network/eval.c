#include "motion.h"
#include "eval.h"

struct Matrix *network_run(
    struct Network *net,
    struct Matrix *inputs
)
{
    network_forward(net, inputs);

    struct Layer *output = &net->layers[net->nb_layers - 1];
    return output->out;
}

void network_eval(
    struct Network *net,
    struct TrainMeta meta,
    struct NetData *nd,
    const char *nd_name
)
{
    printf("[NEURAL_NETWORK][%s] Resultats :\n"
           "precision du reseau : %.2f pourcents\n"
           "image fonction cout : %.2f\n",
            nd_name,
            network_evaluate_accuracy(net, nd),
            network_evaluate_cost(net, meta, nd));
}
