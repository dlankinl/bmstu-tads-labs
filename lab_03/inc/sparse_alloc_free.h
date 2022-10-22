#ifndef __SPARSE_ALLOC_FREE_H__
#define __SPARSE_ALLOC_FREE_H__

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "errors.h"

size_t sparse_matrix_alloc(sparse_matrix *matrix);

void sparse_matrix_free(sparse_matrix *matr);

#endif // __SPARSE_ALLOC_FREE_H__