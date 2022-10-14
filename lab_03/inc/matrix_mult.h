#ifndef __MATRIX_MULT_H__
#define __MATRIX_MULT_H__

#include "sparse_matrix.h"

size_t sparse_mult(sparse_matrix sparse_matr, sparse_matrix sparse_row, sparse_matrix *row_res, unsigned int cols);

#endif // __MATRIX_MULT_H__