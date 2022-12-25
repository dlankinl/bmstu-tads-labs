#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "errors.h"

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

#define MAX_NODE 100

typedef struct
{
    int **matrix;
    int *visited;
    int *parent;
} graph_t;


void zero_matrix(int matrix[][MAX_NODE], size_t dims);

size_t graph_matrix_input(int matrix[][MAX_NODE], int dims);

void graph_matrix_print(int matrix[][MAX_NODE], size_t dims);

void inverted_FloydWarshall(int matrix[][MAX_NODE], int vert_amount);

void create_graph(char *filename, char *graph_name, int matrix[][MAX_NODE], int len);

void bfs(int g[][MAX_NODE], int start, int vertexes);

void primMST(int graph[MAX_NODE][MAX_NODE]);

void floydWarshall(int src[][MAX_NODE], int vert_number);

void print_distances(int src[][MAX_NODE], size_t vert_number);

void inv_floydWarshall(int src[][MAX_NODE], int vert_number);

void print_graph(int vertexes[][MAX_NODE], int vertex, int *peaks_array, int peaks_array_size, FILE *f, int vert_amount);

#endif // __GRAPH_H__