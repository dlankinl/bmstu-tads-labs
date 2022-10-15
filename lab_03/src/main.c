#include <stdlib.h>
#include <stdio.h>
#include "../inc/std_matrix.h"
#include "../inc/sparse_matrix.h"
#include "../inc/matrix_mult.h"
#include "../inc/errors.h"

void print_prompt(void)
{
    printf("\nМеню:\n\n"
           "1. Смоделировать операцию умножения вектора-строки и матрицы, хранящихся в форме разреженных матриц.\n"
           "2. Произвести операцию умножения, применяя стандартный алгоритм работы с матрицами.\n"
           "3. Сравнить время выполнения операций и объём памяти при использовании этих 2-х алгоритмов при различном заполнении матриц.\n"
           "0. Завершить работу программы.\n\n"
           "Введите желаемую команду: ");
}

int main(void)
{
    unsigned int cmd = 0;
    sparse_matrix sparse_matr;
    sparse_matrix sparse_row;
    sparse_matrix res_row;
    // std_matrix matrix;
    // std_matrix row;
    unsigned int matr_len = 0, row_len = 0;
    while (1)
    {
        print_prompt();
        size_t rc = 0;
        
        if (scanf("%u", &cmd) != 1 || cmd > 3)
        {
            printf("Введите корректную команду!\n");
            return WRONG_CMD_ERROR;
        }
        if (cmd == 1)
        {
            if (sparse_matr.vector_a != NULL)
            {
                sparse_matrix_free(&sparse_matr);
                sparse_matrix_free(&sparse_row);
                sparse_matrix_free(&res_row);
                matr_len = 0;
                row_len = 0;
            }
            size_t method = 0;
            printf("\nКак желаете заполнить матрицу?\n\n"
                   "1. Самостоятельно.\n"
                   "2. Случайным образом.\n\n"
                   "Введите желаемую опцию: ");
            if (scanf("%zu", &method) != 1 || method < 1 || method > 2)
            {
                printf("Введите корректные данные!\n");
                return WRONG_METHOD_ERROR;
            }

            rc = sparse_matrix_handler(&sparse_matr, &matr_len, method);
            if (rc)
                return rc;
            printf("\nКак желаете заполнить матрицу?\n\n"
                   "1. Самостоятельно.\n"
                   "2. Случайным образом.\n\n"
                   "Введите желаемую опцию: ");
            if (scanf("%zu", &method) != 1 || method < 1 || method > 2)
            {
                printf("Введите корректные данные!\n");
                return WRONG_METHOD_ERROR;
            }
            rc = sparse_matrix_handler(&sparse_row, &row_len, method);
            res_row.non_zero_nums = sparse_row.cols * sparse_row.rows;
            sparse_matrix_alloc(&res_row);
            sparse_mult(sparse_matr, sparse_row, &res_row, sparse_row.cols);
            printf("\n");
            printf("Результат умножения вектора-строки на матрицу:\n");
            sparse_res_row_handler(&res_row);

            sparse_matrix_free(&sparse_matr);
            sparse_matrix_free(&sparse_row);
            sparse_matrix_free(&res_row);
        }
        else if (cmd == 2)
        {
            std_matrix matrix, row, res_row;
            rc = std_matrix_handler(&matrix);
            if (rc)
                return rc;
            std_matr_print(matrix);

            rc = std_matrix_handler(&row);
            if (rc) 
                return rc;
            std_matr_print(row);

            std_matrix_mult(matrix, row, &res_row);
            std_matr_print(res_row);

            free_matrix(matrix.matrix);
            free_matrix(row.matrix);
            free_matrix(res_row.matrix);
        }
        // else if (cmd == 3)
        // {
        //     printf()
        // }
        else if (cmd == 0)
        {
            printf("Завершение работы...\n");
            return EXIT_SUCCESS;
        }
    }
}