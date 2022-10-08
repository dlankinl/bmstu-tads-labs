#ifndef __SORT_H__
#define __SORT_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "errors.h"
#include "structs_unions.h"

int comparator(const void *ptr_left, const void *ptr_right);

int comparator_keys(const void *ptr_left, const void *ptr_right);

void table_t_qsort(table_t *table);

void table_t_choice_sort(table_t *table);

void keys_t_choice_sort(table_t *table);

void keys_t_qsort(table_t *table);


#endif // __SORT_H__
