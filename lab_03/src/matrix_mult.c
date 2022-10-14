#include "../inc/matrix_mult.h"

// size_t sparse_mult(sparse_matrix sparse_matr, sparse_matrix sparse_row, sparse_matrix *row_res, unsigned int cols)
// {
//     unsigned int counter = 0;
//     // for (unsigned int i = 0; i < cols; i++)
//     // {
//     for (unsigned int j = 0; j < cols; j++)
//     {
//         // if (sparse_row.vector_a[sparse_row.rows - 1 + j] != 0)
//         // {
//         //     printf("%d - row_vector_a[%u]\n", sparse_row.vector_a[sparse_row.rows - 1 + j], j);
//         // }
//         int k = sparse_matr.list_ia[j];
//         // printf("%d - k\n", k);
//         while (k < sparse_matr.list_ia[j + 1])
//         {
//             printf("%d is %d\n", sparse_matr.vector_ja[counter], (int)j);
//             if (sparse_matr.vector_ja[counter] == (int)j)
//             {
//                 printf("%d - vector_a[%u]\n", sparse_matr.vector_a[k], j);
//                 counter++;
//             }
//             k++;
//         }
//         // if (sparse_matr.vector_ja[counter] == (int)j)
//         // {
//         //     printf("%d - vector_ja[%u]\n", sparse_matr.vector_ja[counter], j);
//         //     printf("%d - matr, %d - row, %u - j\n", sparse_matr.vector_a[counter], sparse_row.vector_a[j], j);
//         //     // row_res->vector_a[i] += sparse_row.vector_a[j] * sparse_matr.
//         //     counter++;
//         // }
//     }
//     // int k = sparse_matr.list_ia[cols - 1];
//     // // printf("%d - k\n", k);
//     // while (k < sparse_matr.list_ia[cols])
//     // {
//     //     if (sparse_matr.vector_ja[counter] == (int)(cols - 1))
//     //     {
//     //         printf("%d - vector_a[%u]\n", sparse_matr.vector_a[k], cols - 1);
//     //         counter++;
//     //     }
//     //     k++;
//     // }
//     printf("\n");
//     // }
    
//     return EXIT_SUCCESS;
// }

// size_t sparse_mult(sparse_matrix sparse_matr, sparse_matrix sparse_row, sparse_matrix *row_res, unsigned int cols)
// {
//     for (unsigned int i = 0; i < cols; i++)
//     {
//         // for (unsigned int j = 0; j < cols; j++)
//         // {
//         int k = sparse_matr.list_ia[i];
//         while (k < sparse_matr.list_ia[i + 1])
//         {
//             // if (sparse_matr.vector_ja[sparse_matr.list_ia[j]] == (int)i)
//             // printf("%d - vector_a, %d - k\n", sparse_matr.vector_ja[k], k);
//             if (sparse_matr.vector_ja[k] == (int)i)
//                 printf("%d - vector_a\n", sparse_matr.vector_a[k]);
//                 // printf("%d - vector_a\n", sparse_matr.vector_a[sparse_matr.list_ia[j]]);
//             // printf("%d - k\n", k);
//             k++;
//         }
//         // }
//         printf("\n");
//     }
    
//     return EXIT_SUCCESS;
// }

size_t sparse_mult(sparse_matrix sparse_matr, sparse_matrix sparse_row, sparse_matrix *row_res, unsigned int cols)
{
    unsigned int count = 0;
    int sum, k;
    for (unsigned int i = 0; i < cols; i++)
    {
        sum = 0;
        for (unsigned int j = 0; j < sparse_matr.non_zero_nums; j++)
            if (sparse_matr.vector_ja[j] == (int)i)
            {
                for (k = 0; k < (int)(sparse_matr.rows - 1); k++)
                    if ((int)j < sparse_matr.list_ia[k + 1])
                        break;
                for (unsigned int l = 0; l < sparse_row.non_zero_nums; l++)
                {
                    if (sparse_row.vector_ja[l] == k)
                    {
                        sum += sparse_row.vector_a[l] * sparse_matr.vector_a[j];
                        break;
                    }
                }
            }
        row_res->vector_a[i] = sum;
        row_res->vector_ja[i] = i;
        row_res->non_zero_nums++;
        row_res->cols++;
    }
    row_res->rows = sparse_row.rows;

    return EXIT_SUCCESS;
}