#ifndef __BST_GRAPHVIZ_H__
#define __BST_GRAPHVIZ_H__

#include <stdio.h>
#include <stdlib.h>
#include "tree_t.h"

void to_dot(node_t *root, void *param, char letter, int *counter);

void apply(node_t *root, void (*f)(node_t*, void*, char, int *), void *arg, char letter, int *counter);

void export_to_dot(FILE *dst, const char *tree_name, node_t *root, char letter, int *counter);

int export_to_png(const char *png_path, const char *dot_path, const char *tree_name, node_t *root, char letter, int *counter);

#endif // __BST_GRAPHVIZ_H__
