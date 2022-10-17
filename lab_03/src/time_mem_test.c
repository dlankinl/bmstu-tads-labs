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
    row->list_ia = realloc(row->list_ia, (list_len2 + 1) * sizeof(int));
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

size_t sparse_mult_test(sparse_matrix sparse_matr, sparse_matrix sparse_row, sparse_matrix *row_res, unsigned int cols)
{
    size_t count = 0;

    if (!row_res->vector_a)
        free(row_res->vector_a);
    if (!row_res->vector_ja)
        free(row_res->vector_ja);
    if (!row_res->list_ia)
        free(row_res->list_ia);
    row_res->vector_a = calloc(cols + 1, sizeof(int));
    row_res->vector_ja = calloc(cols + 1, sizeof(int));
    row_res->list_ia = calloc(cols + 1, sizeof(int));

    if (cols != sparse_matr.rows)
        return NOT_AVAILABLE_TO_MULTIPLY;

    int *temp = calloc(cols + 1, sizeof(int));
    if (!temp)
        return ALLOC_ERROR;

    for (size_t i = 0; i < sparse_row.non_zero_nums; i++)
    {
        size_t start = sparse_matr.list_ia[sparse_row.vector_ja[i]];
        size_t end = sparse_matr.list_ia[sparse_row.vector_ja[i] + 1];
        for (size_t k = start; k < end; k++)
            temp[sparse_matr.vector_ja[k]] += sparse_row.vector_a[i] * sparse_matr.vector_a[k];
    }

    int non_zero_nums = 0;
    for (size_t i = 0; i < cols; i++)
    {
        if (temp[i] != 0)
        {
            row_res->vector_a[non_zero_nums] = temp[i];
            row_res->vector_ja[non_zero_nums] = i;
            // row_res->list_ia[i] = 0;
            non_zero_nums++;
            count++;
        }
    } 

    row_res->rows = sparse_row.rows;
    row_res->cols = sparse_row.cols;

    free(temp);
    if (non_zero_nums == 0)
        return EXIT_FAILURE;
    
    row_res->non_zero_nums = non_zero_nums;

    row_res->vector_a = realloc(row_res->vector_a, row_res->non_zero_nums * sizeof(int));
    row_res->vector_ja = realloc(row_res->vector_ja, row_res->non_zero_nums * sizeof(int));
    row_res->list_ia = realloc(row_res->list_ia, 2 * sizeof(int));

    row_res->list_ia[0] = 0;
    row_res->list_ia[1] = count;

    return EXIT_SUCCESS;
}

void free_sparse(sparse_matrix matr)
{
    if (!matr.vector_a)
        free(matr.vector_a);
    if (!matr.vector_ja)
        free(matr.vector_ja);
    if (!matr.list_ia)
        free(matr.list_ia);
}

size_t time_mem_test(void)
{
    // { // 10x10, 25% comparison
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 25, 10, 10);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         sparse_mult_test(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 10x10, 25%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);
        
    //     free_sparse(sprs_matr);
    //     free_sparse(sprs_row);
    //     free_sparse(sprs_res);

    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 25, 10, 10);

    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         std_matrix_mult(std_matr, std_row, &std_res);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 10x10, 25%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }

    // { // 10x10, 50% comparison
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 50, 10, 10);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
    //     sparse_matrix_alloc(&sprs_res);

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         sparse_mult_test(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     // sparse_res_row_handler(&sprs_res);
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 10x10, 50%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);
        
    //     free_sparse(sprs_matr);
    //     free_sparse(sprs_row);
    //     free_sparse(sprs_res);

    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 50, 10, 10);

    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         std_matrix_mult(std_matr, std_row, &std_res);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 10x10, 50%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }

    // { // 10x10, 75% comparison
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 75, 10, 10);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
    //     sparse_matrix_alloc(&sprs_res);

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         sparse_mult_test(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 10x10, 75%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);
        
    //     free_sparse(sprs_matr);
    //     free_sparse(sprs_row);
    //     free_sparse(sprs_res);

    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 75, 10, 10);

    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         std_matrix_mult(std_matr, std_row, &std_res);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 10x10, 75%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }

    // { // 10x10, 100% comparison
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 100, 10, 10);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
    //     sparse_matrix_alloc(&sprs_res);

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         sparse_mult_test(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 10x10, 100%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);
        
    //     free_sparse(sprs_matr);
    //     free_sparse(sprs_row);
    //     free_sparse(sprs_res);

    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 100, 10, 10);

    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         std_matrix_mult(std_matr, std_row, &std_res);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 10x10, 100%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }

    // { // 100x100 5%
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 5, 100, 100);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
    //     sparse_matrix_alloc(&sprs_res);

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         sparse_mult_test(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 100x100, 5%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);
        
    //     free_sparse(sprs_matr);
    //     free_sparse(sprs_row);
    //     free_sparse(sprs_res);

    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 5, 100, 100);

    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         std_matrix_mult(std_matr, std_row, &std_res);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 100x100, 5%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }

    // { // 100x100, 25% comparison
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 25, 100, 100);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
    //     sparse_matrix_alloc(&sprs_res);

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         sparse_mult_test(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 100x100, 25%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);
        
    //     free_sparse(sprs_matr);
    //     free_sparse(sprs_row);
    //     free_sparse(sprs_res);

    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 25, 100, 100);

    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         std_matrix_mult(std_matr, std_row, &std_res);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 100x100, 25%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }

    // { // 100x100, 50% comparison
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 50, 100, 100);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
    //     sparse_matrix_alloc(&sprs_res);

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         sparse_mult_test(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 100x100, 50%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);
        
    //     free_sparse(sprs_matr);
    //     free_sparse(sprs_row);
    //     free_sparse(sprs_res);

    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 50, 100, 100);

    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         std_matrix_mult(std_matr, std_row, &std_res);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 100x100, 50%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }

    // { // 100x100, 100% comparison
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 100, 100, 100);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
    //     sparse_matrix_alloc(&sprs_res);

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         sparse_mult_test(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 100x100, 100%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);
        
    //     free_sparse(sprs_matr);
    //     free_sparse(sprs_row);
    //     free_sparse(sprs_res);

    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 100, 100, 100);

    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         std_matrix_mult(std_matr, std_row, &std_res);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 100x100, 100%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }

    // { // 1000x1000, 5% comparison
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 5, 1000, 1000);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
    //     sparse_matrix_alloc(&sprs_res);

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100; i++)
    //         sparse_mult_test(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 1000x1000, 5%% fill\n", (double)(end - beg) / 100);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);
        
    //     free_sparse(sprs_matr);
    //     free_sparse(sprs_row);
    //     free_sparse(sprs_res);

    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 5, 1000, 1000);

    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100; i++)
    //         std_matrix_mult(std_matr, std_row, &std_res);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 1000x1000, 5%% fill\n", (double)(end - beg) / 100);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }

    // { // 1000x1000, 25% comparison
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 25, 1000, 1000);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
    //     sparse_matrix_alloc(&sprs_res);

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100; i++)
    //         sparse_mult_test(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 1000x1000, 25%% fill\n", (double)(end - beg) / 100);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);
        
    //     free_sparse(sprs_matr);
    //     free_sparse(sprs_row);
    //     free_sparse(sprs_res);

    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 25, 1000, 1000);

    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100; i++)
    //         std_matrix_mult(std_matr, std_row, &std_res);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 1000x1000, 25%% fill\n", (double)(end - beg) / 100);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }

    // { // 1000x1000, 50% comparison
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 50, 1000, 1000);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
    //     sparse_matrix_alloc(&sprs_res);

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100; i++)
    //         sparse_mult_test(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 1000x1000, 50%% fill\n", (double)(end - beg) / 100);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);
        
    //     free_sparse(sprs_matr);
    //     free_sparse(sprs_row);
    //     free_sparse(sprs_res);

    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 50, 1000, 1000);

    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100; i++)
    //         std_matrix_mult(std_matr, std_row, &std_res);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 1000x1000, 50%% fill\n", (double)(end - beg) / 100);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }

    { // 1000x1000, 75% comparison
        sparse_matrix sprs_matr, sprs_row, sprs_res;
        create_sparse_matrixes(&sprs_matr, &sprs_row, 75, 1000, 1000);
        sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
        sparse_matrix_alloc(&sprs_res);

        long long unsigned beg, end;
        beg = milliseconds_now();
        // for (size_t i = 0; i < 2; i++)
        sparse_mult_test(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
        end = milliseconds_now();
        printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 1000x1000, 75%% fill\n", (double)(end - beg));
        printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
        * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
        * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
        * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);
        
        free_sparse(sprs_matr);
        free_sparse(sprs_row);
        free_sparse(sprs_res);

        // std_matrix std_matr, std_row, std_res;
        // create_std_matrixes(&std_matr, &std_row, 75, 1000, 1000);

        // beg = milliseconds_now();
        // for (size_t i = 0; i < 10; i++)
        //     std_matrix_mult(std_matr, std_row, &std_res);
        // end = milliseconds_now();
        // printf("%lf - time for multiplication, 1000x1000, 75%% fill\n", (double)(end - beg) / 10);
        // printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
        // std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
        // free_matrix(std_matr.matrix);
        // free_matrix(std_row.matrix);
        // free_matrix(std_res.matrix);
    }

    { // 1000x1000, 100% comparison
        sparse_matrix sprs_matr, sprs_row, sprs_res;
        create_sparse_matrixes(&sprs_matr, &sprs_row, 100, 1000, 1000);
        sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
        sparse_matrix_alloc(&sprs_res);

        long long unsigned beg, end;
        beg = milliseconds_now();
        // for (size_t i = 0; i < 2; i++)
        sparse_mult_test(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
        end = milliseconds_now();
        printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 1000x1000, 100%% fill\n", (double)(end - beg));
        printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
        * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
        * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
        * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);
        
        free_sparse(sprs_matr);
        free_sparse(sprs_row);
        free_sparse(sprs_res);

        // std_matrix std_matr, std_row, std_res;
        // create_std_matrixes(&std_matr, &std_row, 100, 1000, 1000);

        // beg = milliseconds_now();
        // for (size_t i = 0; i < 100; i++)
        //     std_matrix_mult(std_matr, std_row, &std_res);
        // end = milliseconds_now();
        // printf("%lf - time for multiplication, 1000x1000, 100%% fill\n", (double)(end - beg) / 100);
        // printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
        // std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
        // free_matrix(std_matr.matrix);
        // free_matrix(std_row.matrix);
        // free_matrix(std_res.matrix);
    }

    // { // 10x10, 50% comparison
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 50, 10, 10);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
    //     sparse_matrix_alloc(&sprs_res);

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     sparse_res_row_handler(&sprs_res);
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 10x10, 50%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);


    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 50, 10, 10);

    //     std_matrix_mult(std_matr, std_row, &std_res);
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         std_matrix_mult(std_matr, std_row, &std_res);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 10x10, 50%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }

    // { // 10x10, 75% comparison
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 75, 10, 10);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
    //     sparse_matrix_alloc(&sprs_res);

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     sparse_res_row_handler(&sprs_res);
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 10x10, 75%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);

    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 75, 10, 10);

    //     std_matrix_mult(std_matr, std_row, &std_res);
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 10x10, 75%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }

    // { // 10x10, 100% comparison
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 100, 10, 10);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
    //     sparse_matrix_alloc(&sprs_res);

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     sparse_res_row_handler(&sprs_res);
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 10x10, 100%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);

    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 100, 10, 10);

    //     std_matrix_mult(std_matr, std_row, &std_res);
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 100000; i++)
    //         sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 10x10, 100%% fill\n", (double)(end - beg) / 100000);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }

    // { // 100x100, 25% comparison
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 25, 100, 100);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
    //     sparse_matrix_alloc(&sprs_res);

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 1000; i++)
    //         sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     sparse_res_row_handler(&sprs_res);
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 100x100, 25%% fill\n", (double)(end - beg) / 1000);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);

    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 25, 100, 100);

    //     std_matrix_mult(std_matr, std_row, &std_res);
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 1000; i++)
    //         sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 100x100, 25%% fill\n", (double)(end - beg) / 1000);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }

    // { // 100x100, 5% comparison
    //     sparse_matrix sprs_matr, sprs_row, sprs_res;
    //     create_sparse_matrixes(&sprs_matr, &sprs_row, 5, 100, 100);
    //     sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;
    //     sparse_matrix_alloc(&sprs_res);

    //     long long unsigned beg, end;
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 1000; i++)
    //         sparse_mult(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    //     end = milliseconds_now();
    //     sparse_res_row_handler(&sprs_res);
    //     printf("\n------------- SPARSE -------------\n%lf - time for multiplication, 100x100, 5%% fill\n", (double)(end - beg) / 1000);
    //     printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    //     * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    //     * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    //     * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);

    //     std_matrix std_matr, std_row, std_res;
    //     create_std_matrixes(&std_matr, &std_row, 5, 100, 100);

    //     std_matrix_mult(std_matr, std_row, &std_res);
    //     beg = milliseconds_now();
    //     for (size_t i = 0; i < 1000; i++)
    //         std_matrix_mult(std_matr, std_row, &std_res);
    //     end = milliseconds_now();
    //     printf("%lf - time for multiplication, 100x100, 5%% fill\n", (double)(end - beg) / 1000);
    //     printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    //     std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
        
    //     free_matrix(std_matr.matrix);
    //     free_matrix(std_row.matrix);
    //     free_matrix(std_res.matrix);
    // }
}