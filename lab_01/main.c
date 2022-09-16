#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_ERROR 2
#define TOO_LONG_STR_ERROR 3
#define INVALID_CHARACTERS_ERROR 4
#define NOT_ENOUGH_MATHS_SIGNS_ERROR 5
#define INCORRECT_E_LETTER_AMOUNT_ERROR 6
#define INCORRECT_POINTS_AMOUNT_ERROR 7
#define INCORRECT_POINT_PLACE_ERROR 8
#define WRONG_FORMAT_ERROR 9
#define INCORRECT_MANTISSA_LEN_ERROR 10
#define INCORRECT_POWER_LEN_ERROR 11

#define MAX_REAL_STR_LENGTH 39
#define MAX_INT_STR_LENGTH 31
#define MAX_MANTISSA_LEN 32
#define MAX_POWER_LEN 7
#define NOT_IN_NUM 100

typedef struct
{
    char sign_mantissa;
    char mantissa[MAX_MANTISSA_LEN + 1];
    size_t point_pos;
    size_t E_pos;
    char sign_power;
    char power[MAX_POWER_LEN];
    int power_int;
} number_t;

int str_input(char str[], const size_t max_len, size_t *len)
{
    if (!fgets(str, max_len, stdin) && strlen(str) > 1)
        return INPUT_ERROR;

    *len = strlen(str);
    if (str[*len - 1] == '\n')
        str[*len - 1] = '\0';
    else
        return TOO_LONG_STR_ERROR;

    *len = strlen(str);
    return EXIT_SUCCESS;
}

int str_real_validation(char str[], const size_t len)
{
    size_t subtracts = 0, adds = 0, points = 0, E_letters = 0;
    if (str[0] != '+' && str[0] != '-')
    {
        printf("Error: число должно начинаться со знака '+' или '-'.\n");
        return WRONG_FORMAT_ERROR;
    }

    for (size_t i = 0; i < len; i++)
    {
        if ((str[i] > '9' || str[i] < '0') && str[i] != '.' && str[i] != '+' && str[i] != '-' && str[i] != 'E')
        {
            printf("Error: введены некорректные символы.\n");
            return INVALID_CHARACTERS_ERROR;
        }
    
        if (E_letters && !points && str[i] == '.')
        {
            printf("Error: точка не может находиться в записи порядка.\n");
            return INCORRECT_POINT_PLACE_ERROR;
        }

        if (str[i] == '-')
            subtracts++;
        else if (str[i] == '+')
            adds++;
        else if (str[i] == '.')
            points++;
        else if (str[i] == 'E')
        {
            E_letters++;
            if (i + 1 < len && str[i + 1] != '-' && str[i + 1] != '+')
            {
                printf("Error: число порядка должно начинаться со знака '+' или '-'.\n");
                return WRONG_FORMAT_ERROR;
            }
        }
    }

    if (adds + subtracts > 2)
    {
        printf("Error: по правилам записи должно быть 2 знака (мантисса и порядок)!\n");
        return NOT_ENOUGH_MATHS_SIGNS_ERROR;
    }
    else if (points != 1)
    {
        printf("Error: по правилам записи должна быть 1 точка!\n");
        return INCORRECT_POINTS_AMOUNT_ERROR;
    }
    else if (E_letters > 1)
    {
        printf("Error: по правилам записи не должно быть более одной буквы Е!\n");
        return INCORRECT_E_LETTER_AMOUNT_ERROR;
    }
 
    return EXIT_SUCCESS;
}

void number_t_str_to_int_power(number_t *number)
{
    int flag = 1;
    if (number->sign_power == '-')
        flag = -1;
    number->power_int = atoi(number->power) * flag;
}

int str_int_validation(char str[], const size_t len)
{
    for (size_t i = 0; i < len; i++)
        if ((str[i] > '9' || str[i] < '0') && str[i] != '+' && str[i] != '-')
        {
            printf("Error: введены некорректные символы.\n");
            return INVALID_CHARACTERS_ERROR;
        }

    return EXIT_SUCCESS;
}

size_t symbol_shift(char str[], size_t start, size_t end)
{
    size_t shifted_on = 0;
    for (size_t i = start - 1; i >= end; i--)
    {
        char tmp = str[i];
        str[i] = str[i - 1];
        str[i - 1] = tmp; 
        shifted_on++;
    }
    return shifted_on;
}

// void left_shift(char str[])
// {
//     for (size_t i = 0; i < strlen(str); i++)
//         str[i] = str[i + 1];
// }

void throw_out_zero(char str[], size_t start)
{
    for (size_t i = start; i < strlen(str); i++)
    {
        char tmp = str[i];
        str[i] = str[i + 1];
        str[i + 1] = tmp; 
    }
    str[strlen(str)] = '\0';
}

void delete_leading_zeros(number_t *number)
{
    while (number->mantissa[0] == '0' && number->mantissa[1] != '.')
        // left_shift(number->mantissa);
        throw_out_zero(number->mantissa, 0);
}

void decr_power(number_t *number)
{
    while (number->mantissa[2] == '0')
    {
        throw_out_zero(number->mantissa, 2);
        number->power_int--;
    }
}

int number_normalization(number_t *number)
{
    if (number->point_pos == 1 || (number->point_pos == 2 && number->mantissa[0] == '0' && number->mantissa[2] != '0'))
    {
        printf("Great\n");
        return EXIT_SUCCESS;
    }
    else if (number->mantissa[2] == '0')
    {
        printf("%s - before deleting, %d\n", number->mantissa, number->power_int);
        delete_leading_zeros(number);
        decr_power(number);
        printf("%s - string with deleted zeros, %d\n", number->mantissa, number->power_int);
        return EXIT_SUCCESS;
    }
    else
    {
        size_t end = 1;
        printf("%s - before normalization\n", number->mantissa);
        size_t point_shift = symbol_shift(number->mantissa, number->point_pos, end);
        number->mantissa[strlen(number->mantissa)] = '0';
        symbol_shift(number->mantissa, strlen(number->mantissa), end);
        number->point_pos = end + 1;
        if (strlen(number->mantissa) > MAX_MANTISSA_LEN)
            printf("OOOOPS\n");
        number->power_int += point_shift;
        printf("%s - after normalization, %d\n", number->mantissa, number->power_int);
        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}

int str_to_number_t(char str[], number_t *number)
{
    number->E_pos = NOT_IN_NUM;
    number->point_pos = NOT_IN_NUM;
    number->power_int = 0;
    number->sign_mantissa = str[0];
    size_t len = strlen(str);
    size_t i = 1;
    while (str[i] != 'E' && i < len)
    {
        if (i > 31)
        {
            printf("Error: неверная длина мантиссы (не более 30 цифр).\n");
            return INCORRECT_MANTISSA_LEN_ERROR;
        }
        number->mantissa[i - 1] = str[i];
        if (str[i] == '.')
            number->point_pos = i;
        i++;
    }
    number->mantissa[strlen(number->mantissa)] = '\0';
    
    if (str[i] == 'E')
    {    
        number->E_pos = i;
        number->sign_power = str[++i];
    }

    i++;
    size_t j = 0;
    while (str[i] != '\0')
    {
        if (j > 4)
        {
            printf("Error: неверная длина порядка (не более 5 цифр).\n");
            return INCORRECT_POWER_LEN_ERROR;
        }
        number->power[j] = str[i];
        i++;
        j++;
    }
    number->power[strlen(number->power)] = '\0';
    
    return EXIT_SUCCESS;
}

int main(void)
{
    char real_str[MAX_REAL_STR_LENGTH], int_str[MAX_INT_STR_LENGTH];
    size_t len_real = 0, len_int = 0;
    int ret_code = 0;

    printf("Введите, пожалуйста, целое число:\n |0                            |30\n");
    ret_code = str_input(int_str, MAX_INT_STR_LENGTH + 2, &len_int);
    if (ret_code)
        return ret_code;

    ret_code = str_int_validation(int_str, len_int);
    if (ret_code)
        return ret_code;

    printf("Введите, пожалуйста, вещественное число:\n |0                            |E^|   |\n");
    ret_code = str_input(real_str, MAX_REAL_STR_LENGTH + 2, &len_real);
    if (ret_code)
        return ret_code;

    ret_code = str_real_validation(real_str, len_real);
    if (ret_code)
        return ret_code;

    number_t real_num, int_num;

    ret_code = str_to_number_t(real_str, &real_num);
    if (ret_code)
        return ret_code;

    ret_code = str_to_number_t(int_str, &int_num);
    if (ret_code)
        return ret_code;

    number_t_str_to_int_power(&real_num);
    // printf("Power int: %d\n", real_num.power_int);
    
    printf("%c - sign; %s - mantissa; %zu - point_pos; %zu - e_pos; %d - power\n", real_num.sign_mantissa, real_num.mantissa, real_num.point_pos, real_num.E_pos, real_num.power_int);
    // printf("%c - sign; %s - mantissa; %zu - point_pos; %zu - e_pos; %d - power\n", int_num.sign_mantissa, int_num.mantissa, int_num.point_pos, int_num.E_pos, int_num.power_int);

    number_normalization(&real_num);

    // printf("Your int: %s\nYour real: %s\n", int_str, real_str);
    return EXIT_SUCCESS;
}
