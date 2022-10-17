#include "../inc/time_mem_test.h"

unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long)-1;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

void create_sparse_matrixes(sparse_matrix *matr, sparse_matrix *row, int percentage, unsigned int rows_matr, unsigned int cols)
{
    matr->rows = rows_matr;
    matr->cols = cols;
    row->rows = 1;
    row->cols = cols;
    sparse_rndm_fill(matr, percentage);
    sparse_rndm_fill(row, percentage);
    
    list_handler(matr);
    list_handler(row);
    unsigned int amount1 = 0, list_len1 = 0, amount2 = 0, list_len2 = 0;
    vector_delete_useless_elems(matr->list_ia, matr->non_zero_nums, &amount1, &list_len1);
    vector_delete_useless_elems(row->list_ia, row->non_zero_nums, &amount2, &list_len2);
    matr->list_ia[list_len1] = matr->non_zero_nums;
    matr->list_ia = realloc(matr->list_ia, (list_len1 + 1) * sizeof(int));
    row->list_ia[list_len2] = row->non_zero_nums;
    row->list_ia = realloc(matr->list_ia, (list_len2 + 1) * sizeof(int));
}

void create_std_matrixes(std_matrix *matr, std_matrix *row, int percentage, unsigned int rows_matr, unsigned int cols)
{
    matr->rows = rows_matr;
    matr->cols = cols;
    row->rows = 1;
    row->cols = cols;
    matr->matrix = alloc_matrix(matr->rows, matr->cols);
    row->matrix = alloc_matrix(row->rows, row->cols);
    random_fill_std_matrix(matr, percentage);
    random_fill_std_matrix(row, percentage);
}

size_t time_mem_test(void)
{
    { // 10x10, 25% comparison
        sparse_matrix sprs_matr, sprs_row, sprs_res;
        create_sparse_matrixes(&sprs_matr, &sprs_row, 25, 10, 10);
        sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
        sparse_matrix_alloc(&sprs_res);

        long long unsigned beg, end;
        beg = milliseconds_now();
        for (size_t i = 0; i < 100000; i++)
            sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
        end = milliseconds_now();
        sparse_res_row_handler(&sprs_res);
        printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 10x10, 25%% fill\n", (double)(end - beg) / 100000);
        printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
        * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
        * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
        * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);

        std_matrix std_matr, std_row, std_res;
        create_std_matrixes(&std_matr, &std_row, 25, 10, 10);

        std_matrix_mult(std_matr, std_row, &std_res);
        beg = milliseconds_now();
        for (size_t i = 0; i < 100000; i++)
            sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
        end = milliseconds_now();
        printf("%lf - time for multiplication, 10x10, 25%% fill\n", (double)(end - beg) / 100000);
        printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
        std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
        free_matrix(std_matr.matrix);
        free_matrix(std_row.matrix);
        free_matrix(std_res.matrix);
    }

    { // 10x10, 50% comparison
        sparse_matrix sprs_matr, sprs_row, sprs_res;
        create_sparse_matrixes(&sprs_matr, &sprs_row, 50, 10, 10);
        sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
        sparse_matrix_alloc(&sprs_res);

        long long unsigned beg, end;
        beg = milliseconds_now();
        for (size_t i = 0; i < 100000; i++)
            sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
        end = milliseconds_now();
        sparse_res_row_handler(&sprs_res);
        printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 10x10, 50%% fill\n", (double)(end - beg) / 100000);
        printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
        * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
        * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
        * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);


        std_matrix std_matr, std_row, std_res;
        create_std_matrixes(&std_matr, &std_row, 50, 10, 10);

        std_matrix_mult(std_matr, std_row, &std_res);
        beg = milliseconds_now();
        for (size_t i = 0; i < 100000; i++)
            sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
        end = milliseconds_now();
        printf("%lf - time for multiplication, 10x10, 50%% fill\n", (double)(end - beg) / 100000);
        printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
        std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
        free_matrix(std_matr.matrix);
        free_matrix(std_row.matrix);
        free_matrix(std_res.matrix);
    }

    { // 10x10, 75% comparison
        sparse_matrix sprs_matr, sprs_row, sprs_res;
        create_sparse_matrixes(&sprs_matr, &sprs_row, 75, 10, 10);
        sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
        sparse_matrix_alloc(&sprs_res);

        long long unsigned beg, end;
        beg = milliseconds_now();
        for (size_t i = 0; i < 100000; i++)
            sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
        end = milliseconds_now();
        sparse_res_row_handler(&sprs_res);
        printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 10x10, 75%% fill\n", (double)(end - beg) / 100000);
        printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
        * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
        * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
        * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);

        std_matrix std_matr, std_row, std_res;
        create_std_matrixes(&std_matr, &std_row, 75, 10, 10);

        std_matrix_mult(std_matr, std_row, &std_res);
        beg = milliseconds_now();
        for (size_t i = 0; i < 100000; i++)
            sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
        end = milliseconds_now();
        printf("%lf - time for multiplication, 10x10, 75%% fill\n", (double)(end - beg) / 100000);
        printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
        std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
        free_matrix(std_matr.matrix);
        free_matrix(std_row.matrix);
        free_matrix(std_res.matrix);
    }

    { // 10x10, 100% comparison
        sparse_matrix sprs_matr, sprs_row, sprs_res;
        create_sparse_matrixes(&sprs_matr, &sprs_row, 100, 10, 10);
        sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
        sparse_matrix_alloc(&sprs_res);

        long long unsigned beg, end;
        beg = milliseconds_now();
        for (size_t i = 0; i < 100000; i++)
            sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
        end = milliseconds_now();
        sparse_res_row_handler(&sprs_res);
        printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 10x10, 100%% fill\n", (double)(end - beg) / 100000);
        printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
        * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
        * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
        * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);

        std_matrix std_matr, std_row, std_res;
        create_std_matrixes(&std_matr, &std_row, 100, 10, 10);

        std_matrix_mult(std_matr, std_row, &std_res);
        beg = milliseconds_now();
        for (size_t i = 0; i < 100000; i++)
            sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
        end = milliseconds_now();
        printf("%lf - time for multiplication, 10x10, 100%% fill\n", (double)(end - beg) / 100000);
        printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
        std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
        free_matrix(std_matr.matrix);
        free_matrix(std_row.matrix);
        free_matrix(std_res.matrix);
    }

    { // 100x100, 25% comparison
        sparse_matrix sprs_matr, sprs_row, sprs_res;
        create_sparse_matrixes(&sprs_matr, &sprs_row, 25, 100, 100);
        sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
        sparse_matrix_alloc(&sprs_res);

        long long unsigned beg, end;
        beg = milliseconds_now();
        for (size_t i = 0; i < 1000; i++)
            sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
        end = milliseconds_now();
        sparse_res_row_handler(&sprs_res);
        printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 100x100, 25%% fill\n", (double)(end - beg) / 1000);
        printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
        * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
        * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
        * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);

        std_matrix std_matr, std_row, std_res;
        create_std_matrixes(&std_matr, &std_row, 25, 100, 100);

        std_matrix_mult(std_matr, std_row, &std_res);
        beg = milliseconds_now();
        for (size_t i = 0; i < 1000; i++)
            sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
        end = milliseconds_now();
        printf("%lf - time for multiplication, 100x100, 25%% fill\n", (double)(end - beg) / 1000);
        printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
        std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
        free_matrix(std_matr.matrix);
        free_matrix(std_row.matrix);
        free_matrix(std_res.matrix);
    }

    { // 100x100, 5% comparison
        sparse_matrix sprs_matr, sprs_row, sprs_res;
        create_sparse_matrixes(&sprs_matr, &sprs_row, 50, 100, 100);
        sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
        sparse_matrix_alloc(&sprs_res);

        long long unsigned beg, end;
        beg = milliseconds_now();
        for (size_t i = 0; i < 1000; i++)
            sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
        end = milliseconds_now();
        sparse_res_row_handler(&sprs_res);
        printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 100x100, 50%% fill\n", (double)(end - beg) / 1000);
        printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
        * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
        * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
        * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);

        std_matrix std_matr, std_row, std_res;
        create_std_matrixes(&std_matr, &std_row, 50, 100, 100);

        std_matrix_mult(std_matr, std_row, &std_res);
        beg = milliseconds_now();
        for (size_t i = 0; i < 1000; i++)
            sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
        end = milliseconds_now();
        printf("%lf - time for multiplication, 100x100, 50%% fill\n", (double)(end - beg) / 1000);
        printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
        std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
        free_matrix(std_matr.matrix);
        free_matrix(std_row.matrix);
        free_matrix(std_res.matrix);
    }
}