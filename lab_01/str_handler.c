#include "str_handler.h"

int str_input(char str[], const size_t max_len, size_t *len)
{
    if (!fgets(str, max_len, stdin) && strlen(str) > 1)
        return INPUT_ERROR;

    *len = strlen(str);
    if (str[*len - 1] == '\n')
        str[*len - 1] = '\0';
    else
    {
        printf("Error: слишком длинная строка.\n");
        return TOO_LONG_STR_ERROR;
    }

    *len = strlen(str);
    if (!*len)
    {
        printf("Error: Вы ввели пустую строку.\n");
        return EMPTY_STRING_ERROR;
    }
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
        if (str[i] == ' ')
        {
            printf("Error: число не может содержать пробелы.\n");
            return WRONG_FORMAT_ERROR;
        }

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

            if (i + 1 < len && str[i + 1] == 'E')
            {
                printf("Error: по правилам записи не должно быть более одной буквы Е!\n");
                return INCORRECT_E_LETTER_AMOUNT_ERROR;
            }
            else if (i + 1 < len && str[i + 1] != '-' && str[i + 1] != '+')
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
    else if (points > 1)
    {
        printf("Error: по правилам записи не должно быть более одной точки!\n");
        return INCORRECT_POINTS_AMOUNT_ERROR;
    }
    else if (E_letters > 1)
    {
        printf("Error: по правилам записи не должно быть более одной буквы Е!\n");
        return INCORRECT_E_LETTER_AMOUNT_ERROR;
    }
 
    return EXIT_SUCCESS;
}

int str_int_validation(char str[], const size_t len)
{
    if (str[0] != '-' && str[0] != '+')
    {
        printf("Error: число должно начинаться со знака '+' или '-'.\n");
        return WRONG_FORMAT_ERROR;
    }

    for (size_t i = 1; i < len; i++)
        if (str[i] > '9' || str[i] < '0')
        {
            printf("Error: введены некорректные символы.\n");
            return INVALID_CHARACTERS_ERROR;
        }

    return EXIT_SUCCESS;
}

void symbol_shift(char str[], size_t start, size_t end)
{
    for (size_t i = start - 1; i > end; i--)
    {
        char tmp = str[i];
        str[i] = str[i - 1];
        str[i - 1] = tmp; 
    }
}

void num_shift(char str[], size_t start)
{
    size_t len = strlen(str);
    for (size_t i = start; i < len; i++)
        str[i] = str[i + 1];
    str[len] = '\0';
}

void throw_out_digit(char str[], size_t start)
{
    for (size_t i = start; i < strlen(str); i++)
    {
        char tmp = str[i];
        str[i] = str[i + 1];
        str[i + 1] = tmp; 
    }
    str[strlen(str)] = '\0';
}

void delete_leading_zeros(char str[])
{
    while (str[0] == '0' && strlen(str) != 1)
        throw_out_digit(str, 0);
}

size_t fill_ending_with_zeros(char str[], size_t start, size_t end)
{
    size_t count = 0;
    for (size_t i = start; i < end; i++)
    {
        str[i] = '0';
        count++;
    }
    str[end] = '\0';
    return count;
}

void delete_last_zeros(char str[])
{
    size_t i = MAX_MANTISSA_LEN - 4;
    while (str[i] == '0')
    {
        str[i] = '\0';
        i--;
    }
}