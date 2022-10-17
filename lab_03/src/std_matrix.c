#include "../inc/std_matrix.h"

int **alloc_matrix(unsigned int rows, unsigned int cols)
{
    int **ptrs, *data;
    ptrs = malloc(rows * sizeof(int *));
    if (!ptrs)
        return NULL;
    data = calloc(rows * cols, sizeof(int));
    if (!data)
    {
        free(ptrs);
        return NULL;
    }
    for (size_t i = 0; i < rows; i++)
        ptrs[i] = data + i * cols;
    return ptrs;
}

void free_matrix(int **ptrs)
{
    free(ptrs[0]);
    free(ptrs);
}

size_t std_matrix_fill(int **matrix, unsigned int rows, unsigned int cols, size_t type)
{
    if (type == 2)
    {
        size_t sign = 0;
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
            {
                sign = rand() % 2;
                if (sign)
                    matrix[i][j] = -1 * rand()%100;
                else
                    matrix[i][j] = rand()%100;
            }
    }
    else if (type == 1)
    {
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                if (scanf("%d", &matrix[i][j]) != 1)
                    return INCORRECT_INPUT;
    }
    return EXIT_SUCCESS;
}

int random_fill_std_matrix(std_matrix *matrix, const int fill_percentage)
{
    srand(time(NULL));
    int num_filled;

    num_filled = matrix->rows * matrix->cols * fill_percentage / 100; 

    if (num_filled == 0)
        return EXIT_FAILURE;

    int k = num_filled;

    for (unsigned int i = 0; i < matrix->rows; i++)
        for (unsigned int j = 0; j < matrix->cols; j++)
        {
            if (k-- > 0)
                while(!(matrix->matrix[i][j] = rand()%100));
            else
                matrix->matrix[i][j] = 0;
        }

    int f, l, num;

    for (unsigned int i = 0; i < matrix->rows; i++)
        for (unsigned int j = 0; j < matrix->cols; j++)
        {
            if (num_filled-- > 0)
            {
                f = 1 + rand() % matrix->rows;
                l = 1 + rand() % matrix->cols;
                
                num = matrix->matrix[f - 1][l - 1];
                matrix->matrix[f - 1][l - 1] = matrix->matrix[i][j];
                matrix->matrix[i][j] = num;
            }
            else
                return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

size_t read_rows_cols(unsigned int *rows, unsigned int *cols)
{
    printf("Введите количество строк: ");
    if (scanf("%u", rows) != 1 || *rows > 1000 || *rows == 0)
        return INCORRECT_INPUT;
    printf("Введите количество столбцов: ");
    if (scanf("%u", cols) != 1 || *cols > 1000 || *cols == 0)
        return INCORRECT_INPUT;
    return EXIT_SUCCESS;
}

size_t std_matrix_handler(std_matrix *matr)
{
    matr->rows = 0;
    matr->cols = 0;
    size_t rc;
    rc = read_rows_cols(&matr->rows, &matr->cols);
    if (rc)
    {
        printf("Введите корректные данные!\n");
        return rc;
    }
    matr->matrix = alloc_matrix(matr->rows, matr->cols);
    if (!matr->matrix)
    {
        printf("Ошибка выделения памяти!\n");
        return ALLOC_ERROR;
    }
    size_t filling_type;
    printf("\nВыберите тип заполнения матрицы:\n\n1. Самостоятельно.\n2. Случайные числа.\n");
    if (scanf("%zu", &filling_type) != 1 || filling_type < 1 || filling_type > 2)
    {
        printf("Введите корректные данные!\n");
        return INCORRECT_INPUT;
    }
    // rc = std_matrix_fill(matr->matrix, matr->rows, matr->cols, filling_type);
    printf("Введите процент разреженности матрицы: ");
    unsigned int percentage = 0;
    if (scanf("%u", &percentage) != 1 || percentage > 100)
        return INCORRECT_INPUT;
    rc = random_fill_std_matrix(matr, percentage);
    if (rc)
    {
        printf("Введите корректные данные!\n");
        return rc;
    }
    return EXIT_SUCCESS;
}

void std_matr_print(std_matrix matr)
{
    printf("\n");
    for (unsigned int i = 0; i < matr.rows; i++)
    {
        for (unsigned int j = 0; j < matr.cols; j++)
            printf("%d ", matr.matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}