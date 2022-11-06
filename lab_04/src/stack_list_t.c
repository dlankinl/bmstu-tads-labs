#include "../inc/stack_list_t.h"

size_t stack_list_print(stack_list_t stack)
{
    node_t *cur = stack.head;
    if (!cur)
    {
        printf("\nСтек пуст.\n\n");
        return EMPTY_STACK_ERROR;
    }

    while (cur)
    {
        printf("%d\n", cur->elem);
        cur = (node_t *)cur->next;
    }

    return EXIT_SUCCESS;
}

size_t stack_list_append(stack_list_t *stack, int elem)
{
    if (stack->len > MAX_STACK_SIZE)
    {
        printf("\nСтек полон.\n\n");
        return STACK_OVERFLOW;
    }

    node_t *cur = stack->head;

    if (!cur)
    {
        node_t *new_elem = malloc(sizeof(node_t));

        if (!new_elem)
        {
            printf("\nОшибка выделения памяти.\n\n");
            return ALLOC_ERROR;
        }

        new_elem->elem = elem;
        stack->head = new_elem;
    }

    while (cur->next)
        cur = (node_t *)cur->next;
    // cur = (node_t *)cur->next;

    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node)
        return ALLOC_ERROR;
    cur->next = (struct node_t *)new_node;
    new_node->elem = elem;

    stack->len++;
    return EXIT_SUCCESS;
}

size_t stack_list_add_elems(stack_list_t *stack, size_t amount)
{
    printf("\nВведите %zu элементов: ", amount);
    int num;
    size_t rc = EXIT_SUCCESS;
    for (size_t i = 0; i < amount; i++)
    {
        if (scanf("%d", &num) != 1)
        {
            printf("\nНекорректный ввод.\n\n");
            return INCORRECT_INPUT;
        }
        rc = stack_list_append(stack, num);
        if (rc)
            return rc;
    }
    return EXIT_SUCCESS;
}

// void stack_list_remove_elems(stack_list_t *stack, size_t amount);

// size_t stack_list_fill_random(stack_list_t *stack, size_t amount);

// size_t stack_list_descending_seq(stack_list_t *stack);