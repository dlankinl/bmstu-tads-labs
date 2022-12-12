#ifndef __HASH_TABLE_T_H__
#define __HASH_TABLE_T_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "errors.h"

#define _GNU_SOURCE

typedef struct
{
    char *word;
    int flag;
} hash_elem_t;

typedef struct 
{
    hash_elem_t *arr;
    size_t size;
    size_t divider;
    size_t compares;
} hash_table_t;

hash_table_t *create_table(size_t max_len);

size_t hash_func(char *word, size_t divider);

size_t table_add_elem(hash_table_t *table, char word[MAX_LEN]);

void table_print(hash_table_t *table);

size_t table_fill_from_file(FILE *f, hash_table_t *table, size_t len);

#endif // __HASH_TABLE_T_H__