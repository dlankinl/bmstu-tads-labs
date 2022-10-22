#ifndef __MATRIX_MULT_H__
#define __MATRIX_MULT_H__

#include "sparse_matrix.h"
#include "std_matrix.h"

size_t sparse_mult(sparse_matrix sparse_matr, sparse_matrix sparse_row, sparse_matrix *row_res, unsigned int cols);

size_t std_matrix_mult(std_matrix matr, std_matrix row, std_matrix *res_row);

#endif // __MATRIX_MULT_H__