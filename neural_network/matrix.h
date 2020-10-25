#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

struct Matrix {
    double *data;
    size_t rows;
    size_t cols;
};

struct Matrix *matrix_init(size_t rows, size_t cols);
void matrix_free(struct Matrix *m);

double matrix_get(struct Matrix *m, size_t i, size_t j);
void matrix_print(struct Matrix *m);
void matrix_set(struct Matrix *m, size_t i, size_t j, double elm);
double *matrix_get_ptr(struct Matrix *m, size_t i, size_t j);

struct Matrix *matrix_add(struct Matrix *m1, struct Matrix *m2);
struct Matrix *matrix_scl(struct Matrix *m, double k);
struct Matrix *matrix_mult(struct Matrix *m1, struct Matrix *m2);
struct Matrix *matrix_mult_each(struct Matrix *m1, struct Matrix *m2);
struct Matrix *matrix_map(struct Matrix *m, double (*f)(double));
void matrix_map_inplace(struct Matrix *m, double (*f)(double));
struct Matrix *matrix_copy(struct Matrix *m);

#endif
