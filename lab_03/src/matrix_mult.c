#include "../inc/matrix_mult.h"

size_t sparse_mult(sparse_matrix sparse_matr, sparse_matrix sparse_row, sparse_matrix *row_res, unsigned int cols)
{
    unsigned int count = 0;
    int non_zero_nums = 0;
    int sum, k;
    for (unsigned int i = 0; i < cols; i++)
    {
        sum = 0;
        for (unsigned int j = 0; j < sparse_matr.non_zero_nums; j++)
            if (sparse_matr.vector_ja[j] == (int)i)
            {
                for (k = 0; k < (int)(sparse_matr.rows - 1); k++)
                    if ((int)j < sparse_matr.list_ia[k + 1])
                        break;
                for (unsigned int l = 0; l < sparse_row.non_zero_nums; l++)
                {
                    if (sparse_row.vector_ja[l] == k)
                    {
                        sum += sparse_row.vector_a[l] * sparse_matr.vector_a[j];
                        break;
                    }
                }
            }
        row_res->vector_a[i] = sum;
        row_res->vector_ja[i] = i;
        row_res->list_ia[i] = 0;
        non_zero_nums++;
    }
    row_res->list_ia[row_res->non_zero_nums] = non_zero_nums;
    row_res->rows = sparse_row.rows;
    row_res->cols = sparse_row.cols;
    row_res->vector_a = realloc(row_res->vector_a, non_zero_nums * sizeof(int));
    row_res->vector_ja = realloc(row_res->vector_ja, non_zero_nums * sizeof(int));

    return EXIT_SUCCESS;
}

size_t std_matrix_mult(std_matrix matr, std_matrix row, std_matrix *res_row)
{
    res_row->matrix = alloc_matrix(row.rows, row.cols);
    res_row->rows = 1;
    res_row->cols = matr.cols;
    for (unsigned int i = 0; i < row.cols; i++)
        for (unsigned int j = 0; j < row.cols; j++)
            res_row->matrix[0][j] += row.matrix[0][i] * matr.matrix[i][j];
}