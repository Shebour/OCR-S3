#ifndef NETDATA_H
#define NETDATA_H

#include <stdlib.h>
#include "matrix.h"

struct RawData
{
    struct Matrix *in;
    struct Matrix *out;
};

struct NetData
{
    size_t nb_data;
    struct RawData *raw_data;
};


struct NetData *netdata_alloc(size_t nb_data);
void netdata_free(struct NetData *nd);
void netdata_save(struct NetData *nd, const char *filename);
struct NetData *netdata_load(const char *filename);
void raw_data_copy(struct RawData *src, struct RawData *dst);
struct NetData *netdata_get_batch(
    struct NetData *nd, size_t batch_size, size_t bid);
void netdata_shuffle(struct NetData *nd);
void netdata_split(
    struct NetData *nd,
    struct NetData *train_nd,
    struct NetData *validation_nd,
    struct NetData *test_nd
);

#endif
