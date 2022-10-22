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

void create_test_case(unsigned int rows, unsigned int cols, unsigned int percentage, unsigned int times)
{
    sparse_matrix sprs_matr, sprs_row, sprs_res;
    create_sparse_matrixes(&sprs_matr, &sprs_row, percentage, rows, cols);
    sprs_res.non_zero_nums = sprs_row.cols * sprs_row.rows;

    long long unsigned beg, end;
    beg = milliseconds_now();
    for (size_t i = 0; i < times; i++)
        sparse_mult_test(sprs_matr, sprs_row, &sprs_res, sprs_row.cols);
    end = milliseconds_now();
    printf("\n------------- SPARSE -------------\n%lf - time for multiplication, %ux%u, %u%% fill\n", (double)(end - beg) / times, rows, cols, percentage);
    printf("%zu - memory usage\n--------------- STD --------------\n", (sizeof(sprs_matr.vector_a[0]) + sizeof(sprs_matr.vector_ja[0])) 
    * sprs_matr.non_zero_nums + sizeof(sprs_matr.cols) * 3 + (sizeof(sprs_row.vector_a[0]) + sizeof(sprs_row.vector_ja[0])) 
    * sprs_row.non_zero_nums + sizeof(sprs_row.cols) * 3 + (sizeof(sprs_res.vector_a[0]) + sizeof(sprs_res.vector_ja[0]))
    * sprs_res.non_zero_nums + sizeof(sprs_res.cols) * 3);
    
    free_sparse(sprs_matr);
    free_sparse(sprs_row);
    free_sparse(sprs_res);

    std_matrix std_matr, std_row, std_res;
    create_std_matrixes(&std_matr, &std_row, percentage, rows, cols);

    beg = milliseconds_now();
    for (size_t i = 0; i < times; i++)
        std_matrix_mult(std_matr, std_row, &std_res);
    end = milliseconds_now();
    printf("%lf - time for multiplication, %ux%u, %u%% fill\n", (double)(end - beg) / times, rows, cols, percentage);
    printf("%zu - memory usage\n----------------------------------\n\n", sizeof(std_matr.cols) * 6 + sizeof(std_matr.matrix[0][0]) * 
    std_matr.rows * std_matr.cols + sizeof(std_row.matrix[0][0]) * std_row.rows * std_row.cols + sizeof(std_res.matrix[0][0]) * std_res.rows * std_res.cols);
    
    free_matrix(std_matr.matrix);
    free_matrix(std_row.matrix);
    free_matrix(std_res.matrix);
}

void time_mem_test(void)
{
    for (unsigned int i = 20; i < 101; i += 10)
        create_test_case(10, 10, i, 100000);
    for (unsigned int i = 20; i < 101; i += 5)
        create_test_case(100, 100, i, 10000);
    for (unsigned int i = 20; i < 101; i += 5)
        create_test_case(1000, 1000, i, 100);
}