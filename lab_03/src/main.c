#include <stdlib.h>
#include <stdio.h>
#include "../inc/std_matrix.h"
#include "../inc/errors.h"

int main(void)
{
    std_matrix std_matr;
    size_t rc = 0;
    rc = std_matrix_handler(&std_matr);
    if (rc)
        return rc;
    std_matr_print(std_matr);
    free_matrix(std_matr.matrix);
    return EXIT_SUCCESS;
}