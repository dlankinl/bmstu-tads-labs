#ifndef __STACK_LIST_H__
#define __STACK_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "errors.h"

#define MAX_STACK_SIZE 2000

typedef struct
{
    int elem;
    struct node_t *next;
} node_t;

typedef struct
{
    size_t len;
    node_t *head;
} stack_list_t;

size_t stack_list_print(stack_list_t stack);

size_t stack_list_append(stack_list_t *stack, int elem);

size_t stack_list_add_elems(stack_list_t *stack, size_t amount);

// void stack_list_remove_elems(stack_list_t *stack, size_t amount);

// size_t stack_list_fill_random(stack_list_t *stack, size_t amount);

// size_t stack_list_descending_seq(stack_list_t *stack);

#endif // __STACK_LIST_H__