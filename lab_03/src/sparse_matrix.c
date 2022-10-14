#include "../inc/sparse_matrix.h"
#include "../inc/std_matrix.h"

size_t sparse_matrix_fill(sparse_matrix *matr)
{
    for (unsigned int i = 0; i < matr->non_zero_nums; i++)
        if (scanf("%d %d %d", &matr->vector_a[i], &matr->list_ia[i], &matr->vector_ja[i]) != 3)
            return INCORRECT_INPUT;
    return EXIT_SUCCESS;
}

void list_handler(sparse_matrix *matr)
{
    int *tmp = malloc(matr->non_zero_nums * sizeof(int));
    for (unsigned int i = 0; i < matr->non_zero_nums; i++)
        tmp[i] = matr->list_ia[i];
    for (unsigned int i = 1; i < matr->non_zero_nums; i++)
    {
        if (tmp[i] > tmp[i - 1])
            matr->list_ia[i] = i;
        else
            matr->list_ia[i] = USELESS;
    }
    free(tmp);
}

void shift_to_end(int *vector, unsigned int len, unsigned int pos)
{
    for (unsigned int i = pos; i < len - 1; i++)
    {
        int tmp = vector[i];
        vector[i] = vector[i + 1];
        vector[i + 1] = tmp;
    }
}

void print_vector(int *vector, unsigned int len)
{
    for (unsigned int i = 0; i < len; i++)
        printf("%d ", vector[i]);
    printf("\n");
}

void vector_delete_useless_elems(int *vector, unsigned int len, unsigned int *amount_useless, unsigned int *amount_useful)
{
    for (int i = len - 1; i >= 0; i--)
    {
        if (vector[i] == USELESS)
        {
            shift_to_end(vector, len, i);
            ++(*amount_useless);
        }
        else
            ++(*amount_useful);
    }
}

void print_sparse_matrix_as_std_matrix(sparse_matrix matr, unsigned int ia_len)
{
    unsigned int counter1 = 0;
    unsigned int counter2 = 0;
    for (unsigned int i = 0; i < ia_len; i++)
    {
        for (unsigned int j = 0; j < matr.cols; j++)
        {
            if (matr.vector_ja[counter1] == (int)j)
            {
                printf("%d ", matr.vector_a[counter1]);
                // counter2++;
                counter1++;
                // printf("\n%u - counter1, %u - counter2\n", counter1, counter2);
            }
            else
                printf("%d ", 0);
        }
        printf("\n");
    }
}

size_t sparse_matrix_handler(sparse_matrix *matr, unsigned int *list_len)
{
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

    sparse_matrix_alloc(matr);

    printf("\nВведите элементы разреженной матрицы построчно в следующем формате:\n\n"
           "elem row_numb column_numb\n\n");
    sparse_matrix_fill(matr);

    // for (unsigned int i = 0; i < matr->non_zero_nums; i++)
    //     printf("%d - elem, %d - column num, %d - row num\n", matr->vector_a[i], matr->vector_ja[i], matr->list_ia[i]);
    list_handler(matr);
    // printf("\n");
    // for (unsigned int i = 0; i < matr->non_zero_nums; i++)
    //     printf("%d - elem, %d - column num, %d - row num\n", matr->vector_a[i], matr->vector_ja[i], matr->list_ia[i]);
    unsigned int amount = 0;
    // unsigned int new_len = 0;
    vector_delete_useless_elems(matr->list_ia, matr->non_zero_nums, &amount, list_len);
    // printf("\n");
    // for (unsigned int i = 0; i < matr->non_zero_nums; i++)
        // printf("%d - elem, %d - column num\n", matr->vector_a[i], matr->vector_ja[i]);
    matr->list_ia[*list_len] = matr->non_zero_nums;
    matr->list_ia = realloc(matr->list_ia, (*list_len + 1) * sizeof(int));

    print_sparse_matrix_as_std_matrix(*matr, *list_len);
    return EXIT_SUCCESS;
}