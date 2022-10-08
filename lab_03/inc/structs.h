#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <stdint.h>

typedef struct
{
    int *vector_a;
    int *vector_ja;
    int *list_ia;
    unsigned int rows;
    unsigned int cols;
    unsigned int non_zero_percentage;
} sparse_matrix;

typedef struct
{
    unsigned int rows;
    unsigned int cols;
    int **matrix;
} std_matrix;

#endif // __STRUCTS_H__