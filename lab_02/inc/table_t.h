#ifndef __TABLE_T_H__
#define __TABLE_T_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "errors.h"
#include "structs_unions.h"
#include "input_output.h"

void delete_country_t(table_t *table, size_t pos);

size_t table_t_delete_by_values(FILE *f, table_t *table, char field[MAX_STR_LEN], char value[MAX_STR_LEN]);

void table_t_clear(table_t *table);

void create_keys(table_t *table);

void table_t_add_country(table_t *table, FILE *f);

#endif // __TABLE_T_H__
