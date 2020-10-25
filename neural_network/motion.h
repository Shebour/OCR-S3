#ifndef MOTION_H
#define MOTION_H

#include "network.h"

void network_forward(struct Network *net, struct Matrix *in);
void network_backward(struct Network *net);

#endif
