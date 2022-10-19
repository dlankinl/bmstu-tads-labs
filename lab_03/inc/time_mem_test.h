#ifndef __TIME_MEM_TEST_H__
#define __TIME_MEM_TEST_H__

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "sparse_matrix.h"
#include "matrix_mult.h"

void create_sparse_matrixes(sparse_matrix *matr, sparse_matrix *row, int percentage, unsigned int rows_matr, unsigned int cols);

void create_std_matrixes(std_matrix *matr, std_matrix *row, int percentage, unsigned int rows_matr, unsigned int cols);

void time_mem_test(void);

#endif // __TIME_MEM_TEST_H__