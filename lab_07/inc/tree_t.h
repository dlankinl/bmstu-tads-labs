#ifndef __TREE_T_H__
#define __TREE_T_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "errors.h"
#include "time_mem_test.h"

#define _GNU_SOURCE

typedef struct node_t node_t;

struct node_t
{
    node_t *left;
    node_t *right;
    char *word;
    size_t height;
};

typedef struct
{
    node_t *root;
    size_t size;
    size_t height;
} tree_t;

node_t *init_node(size_t height, char *word);

void tree_t_insert(node_t **head, char *word);

void tree_t_print(node_t *root, const char *dir, int level);

size_t tree_t_read_from_file(FILE *f, node_t **head, uint64_t *avg_ins_time, size_t is_balanced);

void print_tree(node_t *head, int level);

void print_tree_chosen(node_t *head, int level, char letter, size_t to_print, int *counter);

void tree_t_remove_by_ptr(node_t *to_del);

node_t *tree_t_find_node(node_t *head, char *word, size_t *counter);

void tree_t_delete_node(node_t *head, char *word);

void delete(node_t *head, char *word);

void pre_order(node_t *node, size_t *counter);

void in_order(node_t *node);

void post_order(node_t *node);

int balance_factor(node_t *node);

void recover_height(node_t *node);

node_t *left_rotate(node_t *node);

node_t *right_rotate(node_t *node);

node_t *node_balance(node_t *node);

node_t *balanced_tree_t_insert(node_t *head, char *word);

node_t *balance_tree(node_t *bts, node_t **tree_avl);

node_t *find_avl(node_t *p, char word[MAX_LEN], size_t *counter);

#endif // __TREE_T_H__