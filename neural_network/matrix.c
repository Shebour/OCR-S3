#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "matrix.h"

struct Matrix *matrix_init(size_t rows, size_t cols)
{
    struct Matrix *m = malloc(sizeof(struct Matrix));

    if (!m)
        errx(1, "matrix_init: failed initial struct alloc");

    m->rows = rows;
    m->cols = cols;
    m->data = calloc(rows * cols, sizeof(double));

    if (!m->data)
        errx(1, "matrix_init: failed data struct alloc");

    return m;
}

void matrix_free(struct Matrix *m)
{
    free(m->data);
    free(m);
}

double matrix_get(struct Matrix *m, size_t i, size_t j)
{
    return m->data[i * m->cols + j];
}

void matrix_print(struct Matrix *m)
{
    for (size_t i = 0; i < m->rows; ++i)
    {
        for (size_t j = 0; j < m->cols; ++j)
            printf("%.2f ", matrix_get(m, i, j));
        printf("\n");
    }
}

double *matrix_get_ptr(struct Matrix *m, size_t i, size_t j)
{
    return m->data + i * m->cols + j;
}

void matrix_set(struct Matrix *m, size_t i, size_t j, double elm)
{
    *(matrix_get_ptr(m, i, j)) = elm;
}

struct Matrix *matrix_add(struct Matrix *m1, struct Matrix *m2)
{
    if (m1->cols != m2->cols || m1->rows != m2->rows)
        errx(1, "matrix_add: dimension mismatch");

    struct Matrix *res = matrix_init(m1->rows, m1->cols);

    for (size_t i = 0; i < m1->rows; ++i)
        for (size_t j = 0; j < m1->cols; ++j)
            matrix_set(res, i, j, matrix_get(m1, i, j) + matrix_get(m2, i, j));

    return res;
}

struct Matrix *matrix_sub(struct Matrix *m1, struct Matrix *m2)
{
    if (m1->cols != m2->cols || m1->rows != m2->rows)
        errx(1, "matrix_sub: dimension mismatch");

    struct Matrix *res = matrix_init(m1->rows, m1->cols);

    for (size_t i = 0; i < m1->rows; ++i)
        for (size_t j = 0; j < m1->cols; ++j)
            matrix_set(res, i, j, matrix_get(m1, i, j) - matrix_get(m2, i, j));

    return res;
}

struct Matrix *matrix_scl(struct Matrix *m, double k)
{
    struct Matrix *res = matrix_init(m->rows, m->cols);
    for (size_t i = 0; i < m->rows; ++i)
        for (size_t j = 0; j < m->cols; ++j)
            matrix_set(res, i, j, k * matrix_get(m, i, j));

    return res;
}

struct Matrix *matrix_mult(struct Matrix *m1, struct Matrix *m2)
{
    if (m1->cols != m2->rows)
        errx(1, "matrix_mult: dimension mismatch");

    struct Matrix *res = matrix_init(m1->rows, m2->cols);

    for (size_t i = 0; i < m1->rows; ++i)
        for (size_t j = 0; j < m2->cols; ++j)
            for (size_t k = 0; k < m1->cols; ++k)
                matrix_set(res, i, j, matrix_get(res, i, j) +
                    matrix_get(m1, i, k) *
                    matrix_get(m2, k, j));
    return res;
}

struct Matrix *matrix_mult_each(struct Matrix *m1, struct Matrix *m2)
{
    if (m1->rows != m2->rows || m1->cols != m2->cols)
        errx(1, "matrix_mult_each: dimension mismatch");

    struct Matrix *res = matrix_init(m1->rows, m1->cols);

    for (size_t i = 0; i < m1->rows; ++i)
        for (size_t j = 0; j < m1->cols; ++j)
            matrix_set(res, i, j, matrix_get(m1, i, j) * matrix_get(m2, i, j));

    return res;
}

struct Matrix *matrix_map(struct Matrix *m, double (*f)(double))
{
    struct Matrix *res = matrix_init(m->rows, m->cols);
    for (size_t i = 0; i < m->rows; ++i)
        for (size_t j = 0; j < m->cols; ++j)
            matrix_set(res, i, j, f(matrix_get(m, i, j)));

    return res;
}

void matrix_map_inplace(struct Matrix *m, double (*f)(double))
{
    for (size_t i = 0; i < m->rows; ++i)
        for (size_t j = 0; j < m->cols; ++j)
            matrix_set(m, i, j, f(matrix_get(m, i, j)));
}

struct Matrix *matrix_copy(struct Matrix *m)
{
    struct Matrix *new = matrix_init(m->rows, m->cols);
    memcpy(new->data, m->data, m->rows * m->cols);
    return new;
}

struct Matrix *matrix_T(struct Matrix *m)
{
    struct Matrix *res = matrix_init(m->cols, m->rows);
    for (size_t i = 0; i < m->rows; ++i)
        for (size_t j = 0; j < m->cols; ++j)
            matrix_set(res, j, i, matrix_get(m, i, j));

    return res;
}
