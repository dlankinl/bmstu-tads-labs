#include "../inc/sparse_matrix.h"

size_t sparse_matric_fill(sparse_matrix *matr)
{
    for (unsigned int i = 0; i < matr->non_zero_nums; i++)
        if (scanf("%d %d", &matr->vector_a[i], &matr->vector_ja[i]) != 2)
            return INCORRECT_INPUT;
    return EXIT_SUCCESS;
}

void sparse_matrix_free(sparse_matrix *matr)
{
    free(matr->vector_a);
    free(matr->vector_ja);
}

size_t sparse_matrix_handler(sparse_matrix *matr)
{
    matr->vector_a = calloc(matr->non_zero_nums * sizeof(int), sizeof(int));
    if (matr->vector_a == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        return ALLOC_ERROR;
    }

    matr->vector_ja = calloc(matr->non_zero_nums * sizeof(int), sizeof(int));
    if (matr->vector_ja == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        return ALLOC_ERROR;
    }

    // matr->list_ia = calloc(matr->non_zero_nums * sizeof(int), sizeof(int *));
    // if (matr->list_ia == NULL)
    // {
    //     printf("Ошибка выделения памяти!\n");
    //     return ALLOC_ERROR;
    // }

    printf("Введите размер матрицы (максимум 1000х1000): ");
    if (scanf("%u %u", &matr->rows, &matr->cols) != 2 || matr->rows > 1000 || matr->cols > 1000)
    {
        printf("Неверный ввод!\n");
        return INCORRECT_INPUT;
    }

    printf("Введите количество ненулевых элементов (от 1 до %d): ", matr->rows * matr->cols);
    if (scanf("%u", &matr->non_zero_nums) != 1 || matr->non_zero_nums <= 0 || matr->non_zero_nums > matr->rows * matr->cols)
    {
        printf("Неверный ввод!\n");
        return INCORRECT_INPUT;
    }

    printf("\nВведите элементы разреженной матрицы построчно в следующем формате:\n\n"
           "elem row_numb column_numb\n\n");
    sparse_matric_fill(matr);

    for (unsigned int i = 0; i < matr->non_zero_nums; i++)
        printf("%d - elem, %d - row num\n", matr->vector_a[i], matr->vector_ja[i]);
    return EXIT_SUCCESS;
}