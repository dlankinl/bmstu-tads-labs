#include <stdlib.h>
#include <stdio.h>
#include "../inc/std_matrix.h"
#include "../inc/sparse_matrix.h"
#include "../inc/errors.h"

int main(void)
{
    // std_matrix std_matr;
    sparse_matrix sparse_matr;
    size_t rc = 0;
    // rc = std_matrix_handler(&std_matr);
    // if (rc)
    //     return rc;
    // std_matr_print(std_matr);
    // free_matrix(std_matr.matrix);
    rc = sparse_matrix_handler(&sparse_matr);
    if (rc)
        return rc;
    sparse_matrix_free(&sparse_matr);
    return EXIT_SUCCESS;
}