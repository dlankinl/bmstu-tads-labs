#ifndef __INPUT_OUTPUT_H__
#define __INPUT_OUTPUT_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "errors.h"
#include "structs_unions.h"

#define MAX_LEN 256

void split(char str[], country_t *country, size_t *len, char type[]);

void print_country_t(country_t country, int type);

void print_table_t(table_t table);

void print_keys(table_t table);

size_t file_count_elems(FILE *f, size_t *amount);

size_t file_read(FILE *f, size_t *amount, table_t *table);

size_t file_add_country(FILE *f, country_t country);

void print_menu(void);

size_t print_countries_with_continent_sport(table_t *table, char continent[], char sport[]);

void print_country_using_key(size_t index, table_t table);

void table_t_print_with_keys(table_t table);

size_t split_user_country_input(char str[]);

void clean_stdin(void);

void file_rewrite(FILE *f, table_t table);

#endif // __INPUT_OUTPUT_H__
