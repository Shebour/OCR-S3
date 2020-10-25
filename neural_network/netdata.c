#include <err.h>
#include "netdata.h"

struct NetData *netdata_alloc(size_t nb_data)
{
    struct NetData *nd = malloc(sizeof(struct NetData));
    nd->nb_data = nb_data;
    nd->raw_data = calloc(nb_data, sizeof(struct RawData));
    return nd;
}

void netdata_free(struct NetData *nd)
{
    for (size_t i = 0; i < nd->nb_data; ++i)
    {
        matrix_free(nd->raw_data[i].in);
        matrix_free(nd->raw_data[i].out);
    }
    free(nd->raw_data);
    free(nd);
}

void netdata_save(struct NetData *nd, const char *filename)
{
    FILE *f = fopen(filename, "wb");
    if (!f)
        errx(1, "netdata_save: failed to open %s", filename);

    fwrite(&nd->nb_data, sizeof(size_t), 1, f);
    for (size_t i = 0; i < nd->nb_data; ++i)
    {
        matrix_save(f, nd->raw_data[i].in);
        matrix_save(f, nd->raw_data[i].out);
    }

    fclose(f);
}

struct NetData *netdata_load(const char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (!f)
        errx(1, "netdata_save: failed to open %s", filename);

    size_t nb_data = 0ul;
    fread(&nb_data, sizeof(size_t), 1, f);

    struct NetData *nd = netdata_alloc(nb_data);
    for (size_t i = 0; i < nb_data; ++i)
    {
        struct RawData *rd = &nd->raw_data[i];
        rd->in = matrix_load(f);
        rd->out = matrix_load(f);
    }

    fclose(f);
    return nd;
}

void raw_data_copy(struct RawData *src, struct RawData *dst)
{
    dst->in = matrix_copy(src->in);
    dst->out = matrix_copy(src->out);
}

struct NetData *netdata_get_batch(
    struct NetData *nd, size_t batch_size, size_t bid)
{
    struct NetData *batch = netdata_alloc(batch_size);
    for (size_t i = 0; i < batch_size; ++i)
        raw_data_copy(&batch->raw_data[i], &nd->raw_data[bid * batch_size + i]);

    return batch;
}

void netdata_shuffle(struct NetData *nd)
{
    if (nd->nb_data <= 1)
        return;

    for (size_t i = 0; i < nd->nb_data - 1; ++i)
    {
        size_t n = i + rand() / (RAND_MAX / (nd->nb_data - 1) + 1);

        struct RawData tmp = nd->raw_data[n];
        nd->raw_data[n] = nd->raw_data[i];
        nd->raw_data[i] = tmp;
    }
}

void netdata_split(
    struct NetData *nd,
    struct NetData *train_nd,
    struct NetData *validation_nd,
    struct NetData *test_nd
)
{
    size_t tot_n = train_nd->nb_data
                 + validation_nd->nb_data
                 + test_nd->nb_data;

    if (tot_n > nd->nb_data)
        errx(1, "netdata_split: cardinal mismatch");

    netdata_shuffle(nd);

    size_t did = 0;
    for (size_t i = 0; i < train_nd->nb_data; ++i)
        raw_data_copy(&nd->raw_data[did++], &train_nd->raw_data[i]);
    for (size_t i = 0; i < validation_nd->nb_data; ++i)
        raw_data_copy(&nd->raw_data[did++], &validation_nd->raw_data[i]);
    for (size_t i = 0; i < test_nd->nb_data; ++i)
        raw_data_copy(&nd->raw_data[did++], &test_nd->raw_data[i]);
}
