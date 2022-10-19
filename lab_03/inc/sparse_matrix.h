#ifndef __SPARSE_MATRIX_H__
#define __SPARSE_MATRIX_H__

#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include "structs.h"
#include "errors.h"
#include "sparse_alloc_free.h"

#define USELESS 1001

size_t sparse_matrix_fill(sparse_matrix *matr);

void list_handler(sparse_matrix *matr);

void shift_to_end(int *vector, unsigned int len, unsigned int pos);

void vector_delete_useless_elems(int *vector, unsigned int len, unsigned int *amount_useless, unsigned int *amount_useful);

void print_sparse_matrix_as_std_matrix(sparse_matrix matr, unsigned int ia_len);

size_t sparse_res_row_handler(sparse_matrix *matr);

size_t sparse_rndm_fill(sparse_matrix *matr, int percentage);

void print_sparse_matrix(sparse_matrix matr, unsigned int ia_len);

size_t sparse_matrix_handler(sparse_matrix *matr, unsigned int *list_len, size_t input_method);

#endif // __SPARSE_MATRIX_H__