#ifndef MATRIX_AUX_H
#define MATRIX_AUX_H

#include <stdarg.h>

#include "../matrix.h"

void clear_matrix(matrix_t* matrix);
int validate(int amount, ...);
int eq_dimensions(int amount, matrix_t* reference, ...);
void copy_matrix(matrix_t* src, matrix_t* dest);

double mult_matrix_partial(int y, int x, matrix_t* A, matrix_t* B);

void fill_minor(int banned_y, int banned_x, matrix_t* in, matrix_t* out);
int create_minor(int banned_y, int banned_x, matrix_t* in, matrix_t* out);

int determinant_wrapping(matrix_t* A, double* result);
int complements_wrapping(matrix_t* A, matrix_t* buffer);

int inverse_wrapping_simple(matrix_t* A, matrix_t* result, double det);
int inverse_wrapping_complex(matrix_t* A, matrix_t* result, double det);
/*
#include <stdio.h>
void print_matrix(matrix_t matrix);
*/
#endif