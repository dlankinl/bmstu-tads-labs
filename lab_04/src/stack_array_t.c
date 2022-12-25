#include "../inc/stack_array_t.h"

size_t stack_array_print(stack_array_t *stack)
{
    if (stack->size == 0)
    {
        printf("\nСтек пуст.\n\n");
        return EMPTY_STACK_ERROR;
    }

    int *tmp = stack->ptr;
    size_t sz = stack->size;
    printf("\n");
    while (sz)
    {
        printf("%d\n", *tmp--);
        sz--;
    }

    return EXIT_SUCCESS;
}

size_t stack_array_add_elems(stack_array_t *stack, size_t amount)
{
    if (stack->size + amount > MAX_STACK_SIZE)
    {
        printf("\nВ стеке недостаточно памяти.\n");
        return STACK_OVERFLOW;
    }
    for (size_t i = 0; i < amount; i++)
    {
        stack->ptr++;
        if (scanf("%d", stack->ptr) != 1)
        {
            printf("\nНекорректный ввод.\n");
            return INCORRECT_INPUT;
        }
        stack->size++;
    }
    return EXIT_SUCCESS;
}

void stack_array_remove_elems(stack_array_t *stack, size_t amount)
{
    if (stack->size + amount > MAX_STACK_SIZE)
        amount = MAX_STACK_SIZE;
    else if (amount > stack->size)
        amount = stack->size;

    while (amount)
    {
        stack->ptr--;
        stack->size--;
        amount--;
    }
}

size_t stack_array_fill_random(stack_array_t *stack, size_t amount)
{
    if (stack->size + amount > MAX_STACK_SIZE)
    {
        printf("\nВ стеке недостаточно памяти.\n");
        return STACK_OVERFLOW;
    }

    srand(time(NULL));
    for (size_t i = 0; i < amount; i++)
    {
        stack->ptr++;
        stack->size++;
        *stack->ptr = rand() % 100;
        if (rand() % 2)
            *stack->ptr *= -1;
    }
    return EXIT_SUCCESS;
}

size_t stack_array_descending_seq(stack_array_t *stack)
{
    if (stack->size == 0)
    {
        printf("\nСтек пуст.\n\n");
        return EMPTY_STACK_ERROR;
    }

    int prev, flag = 0;
    int *tmp = stack->ptr;
    size_t sz = stack->size;
    printf("\n");
    while (sz > 1)
    {
        prev = *tmp;
        flag = 0;

        sz--;
        tmp--;

        while (sz && *tmp < prev)
        {
            printf("%d ", prev);
            prev = *tmp;
            tmp--;
            sz--;
            flag++;
        }

        if (flag)
            printf("%d\n", prev);
    }
    return EXIT_SUCCESS;
}