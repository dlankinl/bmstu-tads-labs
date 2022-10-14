#include <stdlib.h>
#include <stdio.h>
#include "../inc/std_matrix.h"
#include "../inc/sparse_matrix.h"
#include "../inc/matrix_mult.h"
#include "../inc/errors.h"

int main(void)
{
    // std_matrix std_matr;
    sparse_matrix sparse_matr;
    sparse_matrix sparse_row;
    size_t rc = 0;
    // rc = std_matrix_handler(&std_matr);
    // if (rc)
    //     return rc;
    // std_matr_print(std_matr);
    // free_matrix(std_matr.matrix);
    unsigned int matr_len = 0, row_len = 0;
    rc = sparse_matrix_handler(&sparse_matr, &matr_len);
    if (rc)
        return rc;
    rc = sparse_matrix_handler(&sparse_row, &row_len);
    sparse_matrix res_row;
    res_row.vector_a = calloc(sparse_row.cols, sizeof(int));
    res_row.vector_ja = calloc(sparse_row.cols, sizeof(int));
    res_row.list_ia = calloc(sparse_row.rows + 1, sizeof(int));
    // sparse_mult(sparse_matr, sparse_row, &res_row, matr_len, row_len);
    sparse_mult(sparse_matr, sparse_row, &res_row, sparse_row.cols);
    print_sparse_matrix_as_std_matrix(res_row, res_row.rows);
    sparse_matrix_free(&sparse_matr);
    sparse_matrix_free(&sparse_row);
    sparse_matrix_free(&res_row);
    return EXIT_SUCCESS;
}