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
    int tmp;
    for (unsigned int i = pos; i < len - 1; i++)
    {
        tmp = vector[i];
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
    unsigned int counter = 0;
    for (unsigned int i = 0; i < ia_len; i++)
    {
        for (unsigned int j = 0; j < matr.cols; j++)
        {
            if (matr.vector_ja[counter] == (int)j)
            {
                printf("%d ", matr.vector_a[counter]);
                if (counter < matr.non_zero_nums - 1)
                    counter++;
            }
            else
                printf("%d ", 0);
        }
        printf("\n");
    }
}

void sort_matrix(sparse_matrix *matr)
{
    for (unsigned int i = 0; i < matr->non_zero_nums - 1; i++)
        for (unsigned int j = i + 1; j < matr->non_zero_nums; j++)
            if (matr->list_ia[i] > matr->list_ia[j])
            {
                int tmp = matr->list_ia[i];
                matr->list_ia[i] = matr->list_ia[j];
                matr->list_ia[j] = tmp;

                tmp = matr->vector_a[i];
                matr->vector_a[i] = matr->vector_a[j];
                matr->vector_a[j] = tmp;

                tmp = matr->vector_ja[i];
                matr->vector_ja[i] = matr->vector_ja[j];
                matr->vector_ja[j] = tmp;
            }
}

size_t sparse_rndm_fill(sparse_matrix *matr, int percentage)
{
    
    double dbl_prcntg = (float)percentage / 100;

    matr->non_zero_nums = (int)(matr->cols * matr->rows * dbl_prcntg);
    if (matr->non_zero_nums < 1)
        return INCORRECT_INPUT;
    sparse_matrix_alloc(matr);

    srand(time(NULL));

    for (unsigned int i = 0; i < matr->non_zero_nums; i++)
        while(!(matr->vector_a[i] = rand() % 100));

    for (unsigned int i = 0; i < matr->non_zero_nums; i++)
    {
        if (rand() % 2)
            matr->vector_a[i] *= -1;
        matr->list_ia[i] = i / matr->cols;
        matr->vector_ja[i] = i % matr->cols;
    }

    int new_i, new_j;

    for (unsigned int i = 0; i < matr->non_zero_nums; i++)
    {
        new_i = rand() % matr->rows;
        new_j = rand() % matr->cols;

        for (unsigned int j = 0; j < matr->non_zero_nums; j++)
        {
            if (matr->list_ia[j] == new_i && matr->vector_ja[j] == new_j)
                break;

            if (j == matr->non_zero_nums - 1)
            {
                matr->list_ia[i] = new_i;
                matr->vector_ja[i] = new_j;
            }
        }
    }

    sort_matrix(matr);
}

size_t sparse_res_row_handler(sparse_matrix *matr)
{
    unsigned int useless = 0, useful = 0;
    list_handler(matr);

    vector_delete_useless_elems(matr->list_ia, matr->non_zero_nums, &useless, &useful);
    print_sparse_matrix_as_std_matrix(*matr, useful);
    return EXIT_SUCCESS;
}

size_t sparse_matrix_handler(sparse_matrix *matr, unsigned int *list_len, size_t input_method)
{
    printf("Введите размер матрицы (максимум 1000х1000): ");
    if (scanf("%u %u", &matr->rows, &matr->cols) != 2 || matr->rows > 1000 || matr->cols > 1000)
    {
        printf("Неверный ввод!\n");
        return INCORRECT_INPUT;
    }

    if (input_method == 1)
    {
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
    }
    else if (input_method == 2)
    {
        int percentage = 0;
        printf("Введите процент разреженности матрицы: ");
        if (scanf("%d", &percentage) != 1 || percentage > 100 || percentage < 0)
        {
            printf("Введите корректные данные!\n");
            return INCORRECT_INPUT;
        }
        sparse_rndm_fill(matr, percentage);
    }

    list_handler(matr);
    unsigned int amount = 0;
    vector_delete_useless_elems(matr->list_ia, matr->non_zero_nums, &amount, list_len);
    matr->list_ia[*list_len] = matr->non_zero_nums;
    matr->list_ia = realloc(matr->list_ia, (*list_len + 1) * sizeof(int));

    // printf("\nMatrix\n");
    // print_sparse_matrix_as_std_matrix(*matr, *list_len);

    return EXIT_SUCCESS;
}