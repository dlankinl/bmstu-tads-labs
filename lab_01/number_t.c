#include "number_t.h"
// #include "str_handler.h"

void number_normalization(number_t *number)
{
    size_t len = strlen(number->mantissa);

    if (number->point_pos != NOT_IN_NUM)
    {
        num_shift(number->mantissa, number->point_pos - 1);
        number->power_int += -1 * (len - number->point_pos);
    }

    size_t start = number->point_pos != NOT_IN_NUM ? len - 1 : len;

    size_t added = fill_ending_with_zeros(number->mantissa, start, MAX_MANTISSA_LEN - 1);
    number->power_int -= added;
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
        {
            number->point_pos = i;
            if (str[i + 1] == 'E')
                number->mantissa[i] = '0';
        }
        i++;
    }
    number->mantissa[strlen(number->mantissa)] = '\0';
    
    if (str[i] == 'E')
    {    
        number->E_pos = i;
        number->sign_power = str[++i];
    }
    else
        return EXIT_SUCCESS;

    i++;
    size_t j = 0;
    size_t multiplier = 1;
    i = strlen(str) - 1;
    while (str[i] != '+' && str[i] != '-')
    {
        if (j > 4)
        {
            printf("Error: неверная длина порядка (не более 5 цифр).\n");
            return INCORRECT_POWER_LEN_ERROR;
        }
        number->power_int += ((str[i] - '0') * multiplier);
        multiplier *= 10;
        i--;
        j++;
    }
    if (str[i] == '-')
        number->power_int *= -1;
    
    return EXIT_SUCCESS;
}

int is_left_greater(number_t *l_num, number_t *r_num)
{
    for (size_t i = 0; i < strlen(l_num->mantissa); i++)
    {
        if ((l_num->mantissa[i] - '0') - (r_num->mantissa[i] - '0') > 0)
            return TRUE;
        else if ((l_num->mantissa[i] - '0') - (r_num->mantissa[i] - '0') < 0)
            return FALSE;
    }
    return EXIT_SUCCESS;
}

int digits_subtraction(number_t *int_number, number_t *real_number)
{
    if (is_left_greater(int_number, real_number))
    {
        for (int i = strlen(real_number->mantissa) - 1; i >= 0; i--)
        {
            if (int_number->mantissa[i] - real_number->mantissa[i] >= 0)
                int_number->mantissa[i] -= real_number->mantissa[i] - '0';
            else
            {
                int j = i - 1;

                while (int_number->mantissa[j] == '0')
                    j--;
                int_number->mantissa[j]--;

                for (j = j + 1; j < i; j++)
                    int_number->mantissa[j] += 9;

                int_number->mantissa[i] += 10 - (real_number->mantissa[i] - '0');
            }
        }
        return 1;
    }
    return 0;
}

int is_zero(number_t *number)
{
    size_t count = 0;
    for (size_t i = 0; i < strlen(number->mantissa); i++)
        if (number->mantissa[i] == '0')
            count++;
    if (count == strlen(number->mantissa))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void push_back_zero(number_t *number)
{
    for (int i = 0; i < MAX_MANTISSA_LEN - 2; i++)
        number->mantissa[i] = number->mantissa[i + 1];
    number->mantissa[MAX_MANTISSA_LEN - 1] = '0';
}

int division(number_t *int_number, number_t *real_number, number_t *result_number)
{
    if (is_zero(real_number))
    {
        printf("Error: деление на 0.\n");
        return ZERO_DIVISION_ERROR;
    }
    else if (is_zero(int_number))
    {
        strcpy(result_number->mantissa, "0");
        result_number->sign_mantissa = '+';
        result_number->power_int = 0;
        result_number->sign_power = '+';
        return EXIT_SUCCESS;
    }

    if (abs(int_number->power_int - real_number->power_int) > 99999)
    {
        printf("Error: переполнение порядка.\n");
        return POWER_OVERFLOW_ERROR;
    }

    result_number->mantissa[0] = '0';
    int digit = 0;

    if (!is_left_greater(int_number, real_number)) // изменяем порядок так, чтобы мантисса целого числа была больше
    {
        push_back_zero(int_number);
        int_number->power_int--;
    }

    size_t i;
    for (i = 1; i < MAX_MANTISSA_LEN - 1; i++) //
    {
        if (is_zero(int_number))
        {
            result_number->mantissa[i] = '\0';
            digit = 0;
            break;
        }

        int flag = 0;
        if (is_left_greater(int_number, real_number))
        {
            digit = 0;
            while (digits_subtraction(int_number, real_number))
                digit++;
            flag = 1;
        }
        push_back_zero(int_number);
        
        if (flag)
            result_number->mantissa[i] = '0' + digit;
        else
            result_number->mantissa[i] = '0';
    }

    result_number->mantissa[MAX_MANTISSA_LEN - 1] = '\0'; //

    digit = 0;

    while (digits_subtraction(int_number, real_number))
        digit++;

    push_back_zero(int_number);

    if (i == MAX_MANTISSA_LEN - 1 && digit >= 5) //
        result_number->mantissa[MAX_MANTISSA_LEN - 1] += 1;

    for (; i < MAX_MANTISSA_LEN - 1; i++) //
        result_number->mantissa[i] = '0';

    result_number->mantissa[MAX_MANTISSA_LEN - 1] = '\0'; //

    int carry = 0;

    for (int i = MAX_MANTISSA_LEN - 2; i >= 0; i--)
    {
        result_number->mantissa[i] += carry;

        if (result_number->mantissa[i] == ':')  // знак : имеет код 58 в таблице ASCII и следует за цифрой 9
        {
            result_number->mantissa[i] = '0';
            carry = 1;
        }
        else
            carry = 0;
    }

    if (result_number->mantissa[0] == '1')
    {
        for (i = MAX_MANTISSA_LEN - 2; i > 0; i--)
            result_number->mantissa[i] = result_number->mantissa[i - 1];

        result_number->mantissa[0] = '0';
    }
    else
        carry = 0;

    result_number->mantissa[MAX_MANTISSA_LEN - 2] = '\0'; //

    result_number->power_int = int_number->power_int - real_number->power_int + carry + 1;

    if (int_number->sign_mantissa == real_number->sign_mantissa)
        result_number->sign_mantissa = '+';
    else
        result_number->sign_mantissa = '-';
    
    return EXIT_SUCCESS;
}
