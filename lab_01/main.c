#include "number_t.h"

#define MAX_REAL_STR_LENGTH 39
#define MAX_INT_STR_LENGTH 31
#define MAX_POWER_LEN 7
#define EQUAL 2

int main(void)
{
    char real_str[MAX_REAL_STR_LENGTH], int_str[MAX_INT_STR_LENGTH];
    size_t len_real = 0, len_int = 0;
    int ret_code = 0;

    printf("\nФормат целого числа: +\\-m, где m - мантисса числа\n\nФормат действительного числа:\n+\\-m"
    "[.nE+\\-K], 1 <=(m + n) <= 30, K = [-99 999; 99 999]\n\n");
    printf("Правила ввода чисел:\n1. Каждое число должно начинаться со знака + или -.\n2. "
    "Наличие дробной части в действительном числе необязательно.\n3. Ввод осуществляется без пробелов.\n"
    "4. Мантисса числа может состоять только из цифр.\n5. Число порядка должно начинаться со знака +\\-.\n\n");

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

    number_normalization(&int_num);
    number_normalization(&real_num);

    symbol_shift(int_num.mantissa, strlen(int_num.mantissa), 0);
    symbol_shift(real_num.mantissa, strlen(real_num.mantissa), 0);

    number_t res_num;

    ret_code = division(&int_num, &real_num, &res_num);
    if (ret_code)
        return ret_code;

    delete_leading_zeros(res_num.mantissa);
    delete_last_zeros(res_num.mantissa);

    printf("Your result: %c0.%sE%c%d\n", res_num.sign_mantissa, res_num.mantissa, res_num.sign_power,
    res_num.power_int);

    return EXIT_SUCCESS;
}
