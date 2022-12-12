#include "hash_table_t.h"

hash_table_t *create_table(size_t max_len)
{
    hash_elem_t *arr = NULL;
    arr = malloc(max_len * sizeof(hash_elem_t));
    hash_table_t *table = malloc(sizeof(hash_table_t));
    // table->arr = NULL;
    // table->arr = malloc(max_len * sizeof(hash_elem_t));
    // if (!table->arr)
    //     return NULL;
    table->arr = arr;
    table->size = max_len;
    table->divider = max_len;
    table->compares = 0;
    for (size_t i = 0; i < table->size; i++)
        // table->arr[i].word = malloc(sizeof(char *));
        table->arr[i].word = NULL;
    return table;
}

size_t hash_func(char *word, size_t divider)
{
    size_t len = strlen(word);
    size_t sum = 0;
    for (size_t i = 0; i < len; i++)
        sum += word[i];
    // printf("%zu - divider, %zu - sum, remainder = %zu, string %s\n", divider, sum, sum % divider, word);
    return sum % divider;
}

size_t table_add_elem(hash_table_t *table, char word[MAX_LEN])
{
    size_t hash = hash_func(word, table->divider);
    printf("%s - inside with hash = %zu\n", word, hash);
    if (table->arr[hash].word)
        table->arr[hash + table->divider].word = word;
    else
        table->arr[hash].word = word;
    return EXIT_SUCCESS;
}

void table_print(hash_table_t *table)
{
    for (size_t i = 0; i < table->size; i++)
    {
        if (!table->arr[i].word)
            printf("Ключ: %zu | Значение: (nil)\n", i);
        else
            printf("Ключ: %zu | Значение: %s\n", i, table->arr[i].word);

    }
}

size_t table_fill_from_file(FILE *f, hash_table_t *table, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        char *word = malloc(MAX_LEN * sizeof(char));
        if (fscanf(f, "%s", word) != 1)
            return FILE_READ_ERROR;
        table_add_elem(table, word);
    }
    return EXIT_SUCCESS;
}