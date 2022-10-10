#include <stdlib.h>
#include <stdio.h>
#include "../inc/std_matrix.h"
#include "../inc/sparse_matrix.h"
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
    sparse_matrix_free(&sparse_matr);
    sparse_matrix_free(&sparse_row);
    return EXIT_SUCCESS;
}