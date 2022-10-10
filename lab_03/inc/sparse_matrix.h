#ifndef __SPARSE_MATRIX_H__
#define __SPARSE_MATRIX_H__

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "structs.h"
#include "errors.h"

size_t sparse_matric_fill(sparse_matrix *matr);

void sparse_matrix_free(sparse_matrix *matr);

size_t sparse_matrix_handler(sparse_matrix *matr);


#endif // __SPARSE_MATRIX_H__