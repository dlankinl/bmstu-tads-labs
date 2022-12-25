#include "graph.h"

void zero_matrix(int matrix[][MAX_NODE], size_t dims)
{
    for (size_t i = 0; i < dims; i++)
        for (size_t j = 0; j < dims; j++)
            matrix[i][j] = 0;
}

size_t graph_matrix_input(int matrix[][MAX_NODE], int dims)
{
    size_t counter = 0;
    int row = 0, col = 0, len = 0;
    while (counter < dims * dims)
    {
        if (scanf("%d %d %d", &row, &col, &len) != 3)
            return INCORRECT_INPUT;
        if (row == -1)
            break;        
        if (row - 1 >= dims || col - 1 >= dims || !row || !col)
        {
            setbuf(stdin, NULL);
            printf("Введите корректные номер столбца или строки.\n");
        }
        if (!matrix[row - 1][col - 1])
        {
            matrix[row - 1][col - 1] = len;
            counter++;
        }
        else
            printf("Данное ребро (row = %d, col = %d) уже построено.\n", row, col);
    }

    return EXIT_SUCCESS;
}

void graph_matrix_print(int matrix[][MAX_NODE], size_t dims)
{
    for (size_t i = 0; i < dims; i++)
    {
        for (size_t j = 0; j < dims; j++)
            printf("| %4d |", matrix[i][j]);
        printf("\n");
    }
}

void create_graph(char *filename, char *graph_name, int matrix[][MAX_NODE], int len)
{
    FILE *f = fopen(filename, "w");
    if (!f)
    {
        printf("Unable ot open file\n");
        return;
    }
    fprintf(f, "digraph %s {\nnode [shape = circle];\n\n", graph_name);
    graph_matrix_print(matrix, len);
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            if (matrix[j][i] && i != j)
                fprintf(f, "%d -> %d [label = %d, color = red];\n", j + 1, i + 1, matrix[j][i]);
    fprintf(f, "}\n");
    fclose(f);
}

void print_distances(int src[][MAX_NODE], size_t vert_number)
{
    for (size_t i = 0; i < vert_number - 1; i++)
    {
        printf("Вершина %zu:\n", i + 1);
        for (size_t j = i + 1; j < vert_number; j++)
            printf("%zu -> %zu = %d\n", i + 1, j + 1, src[i][j]);
        printf("\n");
    }
}

void inv_floydWarshall(int src[][MAX_NODE], int vert_number)
{
    for (int i = 0; i < vert_number; i++)
        for (int j = 0; j < vert_number; j++)
            for (int k = 0; k < vert_number; k++)
                if (src[j][i] && src[i][k] && j != k)
                    if (src[j][i] + src[i][k] > src[j][k] || src[j][k] == INT_MAX)
                        src[j][k] = src[j][i] + src[i][k];
}