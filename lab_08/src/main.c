#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

int main(void)
{
    size_t vert_amount;
    printf("Введите количество вершин: ");
    while (1)
    {
        if (scanf("%zu", &vert_amount) != 1)
        {
            setbuf(stdin, NULL);
            printf("Некорректный ввод.\n");
        }
        else
            break;
    }

    int vertexes[MAX_NODE][MAX_NODE];

    printf("Введите все связи между вершинами в формате: 'вершина1 вершина2 длина' без кавычек (ввод заканчивайте вводом -1 0 0):\n");

    zero_matrix(vertexes, vert_amount);

    graph_matrix_input(vertexes, vert_amount);

    graph_matrix_print(vertexes, vert_amount);
    printf("\n");

    create_graph("graph.dot", "roads", vertexes, vert_amount);
    system("dot -Tpng graph.dot -o graph.png");

    inv_floydWarshall(vertexes, vert_amount);

    print_distances(vertexes, vert_amount);

    return EXIT_SUCCESS;
}