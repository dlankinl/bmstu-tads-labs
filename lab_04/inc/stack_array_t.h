#ifndef __STACK_ARRAY_H__
#define __STACK_ARRAY_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "errors.h"

#define MAX_STACK_SIZE 2000

typedef struct
{
    int *ptr;
    size_t size;
} stack_array_t;

size_t stack_array_print(stack_array_t *stack);

size_t stack_array_add_elems(stack_array_t *stack, size_t amount);

void stack_array_remove_elems(stack_array_t *stack, size_t amount);

size_t stack_array_fill_random(stack_array_t *stack, size_t amount);

size_t stack_array_descending_seq(stack_array_t *stack);

#endif // __STACK_ARRAY_H__