#ifndef __STD_MATRIX_H__
#define __STD_MATRIX_H__

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "structs.h"
#include "errors.h"

int **alloc_matrix(unsigned int rows, unsigned int cols);

void free_matrix(int **ptrs);

size_t std_matrix_fill(int **matrix, unsigned int rows, unsigned int cols, size_t type);

size_t read_rows_cols(unsigned int *rows, unsigned int *cols);

size_t std_matrix_handler(std_matrix *matrix);

void std_matr_print(std_matrix matr);

#endif // __STD_MATRIX_H__