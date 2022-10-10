#ifndef __SPARSE_MATRIX_H__
#define __SPARSE_MATRIX_H__

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "structs.h"
#include "errors.h"

#define USELESS 1001

size_t sparse_matrix_fill(sparse_matrix *matr);

void sparse_matrix_free(sparse_matrix *matr);

void list_handler(sparse_matrix *matr);

void shift_to_end(int *vector, unsigned int len, unsigned int pos);

void vector_delete_useless_elems(int *vector, unsigned int len, unsigned int *amount_useless, unsigned int *amount_useful);

size_t sparse_matrix_handler(sparse_matrix *matr, unsigned int *list_len);


#endif // __SPARSE_MATRIX_H__