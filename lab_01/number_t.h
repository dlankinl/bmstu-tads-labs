#ifndef __NUMBER_T_H__
#define __NUMBER_T_H__

#include <stdlib.h>
#include <stdio.h>

#include "errors.h"
#include "str_handler.h"

#define NOT_IN_NUM 100
#define TRUE 1
#define FALSE 0
#define MAX_MANTISSA_LEN 32

typedef struct
{
    char sign_mantissa;
    char mantissa[MAX_MANTISSA_LEN + 1];
    size_t point_pos;
    size_t E_pos;
    char sign_power;
    int power_int;
} number_t;

void number_normalization(number_t *number);

int str_to_number_t(char str[], number_t *number);

int is_left_greater(number_t *l_num, number_t *r_num);

int digits_subtraction(number_t *int_number, number_t *real_number);

int is_zero(number_t *number);

void push_back_zero(number_t *number);

int division(number_t *int_number, number_t *real_number, number_t *result_number);

#endif // __NUMBER_T_H__