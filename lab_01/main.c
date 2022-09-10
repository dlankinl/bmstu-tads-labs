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

#define MAX_STR_LENGTH 38

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

int E_position(char str[], size_t len, size_t *pos)
{
    for (size_t i = 0; i < len; i++)
        if (str[i] == 'E')
        {
            *position = i;
            return EXIT_SUCCESS;
        }
    return EXIT_FAILURE;
}

int str_validation(char str[], const size_t len, size_t E_position)
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

    if (adds + subtracts != 2)
    {
        printf("Error: по правилам записи должно быть 2 знака (мантисса и порядок)!\n");
        return NOT_ENOUGH_MATHS_SIGNS_ERROR;
    }
    else if (points != 1)
    {
        printf("Error: по правилам записи должна быть 1 точка!\n");
        return INCORRECT_POINTS_AMOUNT_ERROR;
    }
    else if (E_letters != 1)
    {
        printf("Error: по правилам записи число вводится в экспоненциальной форме!\n");
        return INCORRECT_E_LETTER_AMOUNT_ERROR;
    }

    return EXIT_SUCCESS;
}

int main(void)
{
    char str[MAX_STR_LENGTH];
    size_t len = 0;
    size_t E_position = 0;
    int ret_code = 0;
    ret_code = str_input(str, MAX_STR_LENGTH, &len);
    if (!ret_code)
        if (!E_position(str, len, &E_position))
            ret_code = str_validation(str, len, E_position);
    else
        return ret_code;

    if (ret_code)
        return ret_code;

    printf("Your input: %s\n", str);
    return EXIT_SUCCESS;
}

