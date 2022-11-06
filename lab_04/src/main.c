#include <stdlib.h>
#include <stdio.h>
#include "../inc/stack_array_t.h"
#include "../inc/stack_list_t.h"

int main(void)
{
    size_t stack_method = 0;
    size_t rc = EXIT_SUCCESS;

    printf("Выберите желаемую реализацию стека:\n"
           "1. Реализация стека массивом.\n"
           "2. Реализация стека списком.\n");
    if (scanf("%zu", &stack_method) != 1)
    {
        printf("Некорректный ввод.\n");
        return INCORRECT_INPUT;
    }

    if (stack_method == 1)
    {
        size_t cmd = 0;
        stack_array_t stack_array;
        int arr[MAX_STACK_SIZE];
        stack_array.ptr = arr - 1;
        stack_array.size = 0;
        while (1)
        {
            printf("\nВыберите желаемую команду:\n"
                   "1. Добавить несколько элементов в стек.\n"
                   "2. Удалить несколько элементов в стеке.\n"
                   "3. Вывести элементы стека.\n"
                   "4. Заполнить стек случайными числами.\n"
                   "5. Распечатать убывающие серии последовательности целых чисел в обратном порядке.\n"
                   "0. Завершить работу программы.\n");

            if (scanf("%zu", &cmd) != 1 || cmd > 5)
            {
                printf("\nНеверная команда.\n");
                return WRONG_CMD;
            }

            if (cmd == 1)
            {
                size_t amount;
                printf("\nВведите количество элементов для добавления: ");
                if (scanf("%zu", &amount) != 1)
                {
                    printf("\nНекорректный ввод.\n");
                    setbuf(stdin, NULL);
                }
                stack_array_add_elems(&stack_array, amount);
            }
            else if (cmd == 2)
            {
                size_t amount;
                printf("\nВведите количество удаляемых элементов: ");
                if (scanf("%zu", &amount) != 1)
                {
                    printf("\nНекорректный ввод.\n");
                    setbuf(stdin, NULL);
                }
                stack_array_remove_elems(&stack_array, amount);
            }
            else if (cmd == 3)
            {
                stack_array_print(&stack_array);
            }
            else if (cmd == 4)
            {
                size_t amount;
                printf("\nВведите количество добавляемых элементов: ");
                if (scanf("%zu", &amount) != 1)
                {
                    printf("\nНекорректный ввод.\n");
                    setbuf(stdin, NULL);
                }
                stack_array_fill_random(&stack_array, amount);
            }
            else if (cmd == 5)
            {
                stack_array_descending_seq(&stack_array);
            }
            else if (cmd == 0)
                return rc;
        }
    }
    else if (stack_method == 2)
    {
        stack_list_t stack_list;
        stack_list.head = NULL;
        stack_list.len = 0;
        size_t cmd;
        while (1)
        {
            printf("\nВыберите желаемую команду:\n"
                   "1. Добавить несколько элементов в стек.\n"
                   "2. Удалить несколько элементов в стеке.\n"
                   "3. Вывести элементы стека.\n"
                   "4. Заполнить стек случайными числами.\n"
                   "5. Распечатать убывающие серии последовательности целых чисел в обратном порядке.\n"
                   "0. Завершить работу программы.\n");

            if (scanf("%zu", &cmd) != 1 || cmd > 5)
            {
                printf("\nНеверная команда.\n");
                return WRONG_CMD;
            }

            if (cmd == 1)
            {
                size_t amount;
                printf("\nВведите количество элементов для добавления: ");
                if (scanf("%zu", &amount) != 1)
                {
                    printf("\nНекорректный ввод.\n");
                    setbuf(stdin, NULL);
                }
                stack_list_add_elems(&stack_list, amount);
            }
            else if (cmd == 3)
            {
                stack_list_print(stack_list);
            }
        }
    }

    return rc;
}