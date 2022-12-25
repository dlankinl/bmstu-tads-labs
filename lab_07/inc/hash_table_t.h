#ifndef __HASH_TABLE_T_H__
#define __HASH_TABLE_T_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "errors.h"
#include "time_mem_test.h"

#define _GNU_SOURCE

typedef struct
{
    char name[MAX_LEN];
} value_s;

typedef struct hash_elem_t
{
    size_t hash_index;
    value_s hash_value;
    struct hash_elem_t *next;
} hash_elem_t;

typedef struct hash_elem_step_t
{
    size_t hash_index;
    value_s hash_value;
} hash_elem_step_t;

int is_empty_hash_table(hash_elem_t **table, size_t len);

size_t hash_func(char *word, size_t divider);

int add_element_hash_table(hash_elem_t **table, char word[MAX_LEN], size_t len);

void del_element_hash_table(hash_elem_t **table, char word[MAX_LEN], size_t len);

size_t hash_table_find(hash_elem_t **table, char word[MAX_LEN], size_t *counter, size_t len, uint64_t *time);

size_t hash_table_fill_from_file(FILE *f, hash_elem_t **table, size_t len);

void hash_table_print(hash_elem_t **table, size_t len);

hash_elem_t *push_node(char word[MAX_LEN], size_t len);

void hash_table_free(hash_elem_t **table, size_t len);

hash_elem_t **create_hash_table(size_t len);

size_t count_collisions(hash_elem_t **table, size_t len);

size_t max_depth(hash_elem_t **table, size_t len);

size_t nearest_bigger_prime(size_t num);

hash_elem_t **hash_table_restructure(hash_elem_t **table, size_t *len);

// In hash

hash_elem_step_t **create_hash_table_step(size_t len);

int add_element_hash_table_step(hash_elem_step_t **table, char word[MAX_LEN], size_t len);

size_t hash_table_step_find(hash_elem_step_t **table, char word[MAX_LEN], size_t *counter, size_t len, uint64_t *time);

size_t hash_table_step_fill_from_file(FILE *f, hash_elem_step_t **table, size_t len);

void hash_table_step_print(hash_elem_step_t **table, size_t len);

void hash_table_step_free(hash_elem_step_t **table, size_t len);

size_t wrong_hash_elements(hash_elem_step_t **table, size_t len);

hash_elem_step_t **hash_table_step_restructure(hash_elem_t **table, size_t *len);

#endif // __HASH_TABLE_T_H__