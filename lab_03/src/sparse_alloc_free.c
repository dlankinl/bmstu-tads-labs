#include "../inc/sparse_alloc_free.h"

size_t sparse_matrix_alloc(sparse_matrix *matrix)
{
    matrix->vector_a = malloc(matrix->non_zero_nums * sizeof(int));
    if (matrix->vector_a == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        return ALLOC_ERROR;
    }

    matrix->vector_ja = calloc(matrix->non_zero_nums, sizeof(int));
    if (matrix->vector_ja == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        return ALLOC_ERROR;
    }

    matrix->list_ia = calloc(matrix->non_zero_nums + 1, sizeof(int));
    if (matrix->list_ia == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        return ALLOC_ERROR;
    }
    return EXIT_SUCCESS;
}

void sparse_matrix_free(sparse_matrix *matr)
{
    free(matr->vector_a);
    free(matr->vector_ja);
    free(matr->list_ia);
}