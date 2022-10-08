#ifndef __STR_HANDLER_H__
#define __STR_HANDLER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"

#define MAX_MANTISSA_LEN 32

int str_input(char str[], const size_t max_len, size_t *len);

int str_real_validation(char str[], const size_t len);

int str_int_validation(char str[], const size_t len);

void symbol_shift(char str[], size_t start, size_t end);

void num_shift(char str[], size_t start);

void throw_out_digit(char str[], size_t start);

void delete_leading_zeros(char str[]);

size_t fill_ending_with_zeros(char str[], size_t start, size_t end);

void delete_last_zeros(char str[]);

#endif // __STR_HANDLER_H__