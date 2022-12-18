#include "hash_table_t.h"

// hash_table_t *create_table(size_t max_len)
// {
//     hash_elem_t *arr = NULL;
//     arr = malloc(max_len * sizeof(hash_elem_t));
//     hash_table_t *table = malloc(sizeof(hash_table_t));
//     table->arr = arr;
//     table->size = max_len;
//     table->divider = max_len;
//     table->compares = 0;
//     for (size_t i = 0; i < table->size; i++)
//         // table->arr[i].word = malloc(sizeof(char *));
//         table->arr[i].word = NULL;
//     return table;
// }

// size_t hash_func(char *word, size_t divider)
// {
//     size_t len = strlen(word);
//     size_t sum = 0;
//     for (size_t i = 0; i < len; i++)
//         sum += word[i];
//     // printf("%zu - divider, %zu - sum, remainder = %zu, string %s\n", divider, sum, sum % divider, word);
//     return sum % divider;
// }

// size_t table_add_elem(hash_table_t *table, char word[MAX_LEN])
// {
//     size_t hash = hash_func(word, table->divider);
//     hash_elem_t *new = &(table->arr[hash]);
//     // printf("%s - inside with hash = %zu\n", word, hash);
//     if (table->arr[hash].word)
//     {
//         while (new->next)
//             new = new->next;
//         // new = malloc(sizeof(hash_elem_t *));
//         // new->word = word;
//         // new->next = NULL;
//         // table->arr[hash].next = new;
//         // printf("%s with hash %zu\n", table->arr[hash].next->word, hash);
//         new->next = add_node(word);
//         printf("%s - word in list\n", new->word);
//     }
//     else
//         table->arr[hash].word = word;
//     return EXIT_SUCCESS;
// }

// hash_elem_t *add_node(char word[MAX_LEN])
// {
//     hash_elem_t *tmp = malloc(sizeof(hash_elem_t));
//     tmp->word = malloc(MAX_LEN * sizeof(char));
//     strcpy(tmp->word, word);
//     tmp->next = NULL;
//     return tmp;
// }

// void table_print(hash_table_t *table)
// {
//     for (size_t i = 0; i < table->size; i++)
//     {
//         if (!table->arr[i].word)
//         // if (!table->arr[i].data->word)
//             printf("Ключ: %zu | Значение: (nil)\n", i);
//         else
//         {
//             printf("Ключ: %zu | Значение: %s\n", i, table->arr[i].word);
//             // size_t i = 0;
//             // while (table->arr[i].next)
//             // {
//                 // table->arr[i] = table->arr[i].next;
//                 // hash_elem_t *tmp = table->arr[i].next;
//                 // printf(", %s", tmp->word);
//                 // i++;
//             // }
//             // printf("\n");
//         }
//     }
// }

// size_t table_fill_from_file(FILE *f, hash_table_t *table, size_t len)
// {
//     for (size_t i = 0; i < len; i++)
//     {
//         char *word = malloc(MAX_LEN * sizeof(char));
//         if (fscanf(f, "%s", word) != 1)
//             return FILE_READ_ERROR;
//         table_add_elem(table, word);
//     }
//     return EXIT_SUCCESS;
// }




size_t hash_func(char *word, size_t divider)
{
    size_t len = strlen(word);
    size_t sum = 0;
    for (size_t i = 0; i < len; i++)
        sum += word[i];
    return sum % divider;
}

int add_element_hash_table(hash_elem_t **table, char word[MAX_LEN], size_t len)
{
    size_t hash = hash_func(word, len);

    hash_elem_t *temp = table[hash];

    if (table[hash])
    {
        while (temp->next)
            temp = temp->next;
        temp->next = push_node(word, len);
    }
    else
        table[hash] = push_node(word, len);

    return EXIT_SUCCESS;
}

void del_element_hash_table(hash_elem_t **table, char word[MAX_LEN], size_t len)
{
    size_t hash = hash_func(word, len);
    hash_elem_t *to_del;

    if (!table[hash])
    {
        printf("Такого слова нет.\n");
        return;
    }

    if (!strcmp(word, table[hash]->hash_value.name))
    {
        to_del = table[hash];
        table[hash] = table[hash]->next;
        free(to_del);
        return;
    }

    hash_elem_t *temp = table[hash];
    while (temp->next)
    {
        to_del = temp->next;
        if (!strcmp(word, to_del->hash_value.name))
        {
            temp->next = to_del->next;
            free(to_del);
            break;
        }
        temp = temp->next;
    }
}

size_t hash_table_find(hash_elem_t **table, char word[MAX_LEN], size_t *counter, size_t len, uint64_t *time)
{
    size_t hash = hash_func(word, len);

    uint64_t start, end;
    start = tick();
    while (table[hash])
    {
        if (!strcmp(word, table[hash]->hash_value.name))
        {
            end = tick();
            *time = end - start;
            return EXIT_SUCCESS;
        }
        (*counter)++;
        table[hash] = table[hash]->next;
    }
    return EXIT_FAILURE;
}

size_t hash_table_fill_from_file(FILE *f, hash_elem_t **table, size_t len)
{
    char word[MAX_LEN];
    for (size_t i = 0; i < len; i++)
    {
        if (fscanf(f, "%s", word) != 1)
            return FILE_READ_ERROR;
        add_element_hash_table(table, word, len);
    }
    return EXIT_SUCCESS;
}

void hash_table_print(hash_elem_t **table, size_t len)
{
    hash_elem_t *temp;

    printf("%4s %10s\n", "KEY", "VALUE");

    for (size_t i = 0; i < len; i++)
    {
        if (table[i])
        {
            printf("%4zu: ", i);
            temp = table[i];
            while (temp)
            {
                printf("%s -> ", temp->hash_value.name);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}

hash_elem_t *push_node(char word[MAX_LEN], size_t len)
{
    hash_elem_t *temp = (hash_elem_t *)malloc(sizeof(hash_elem_t));

    strcpy(temp->hash_value.name, word);
    strcpy(temp->name1, word);
    temp->hash_index = hash_func(word, len);
    temp->next = NULL;

    return temp;
}

void hash_table_free(hash_elem_t **table, size_t len)
{
    hash_elem_t *prev = NULL;
    for (size_t i = 0; i < len; i++)
        if (table[i])
            while (table[i])
            {
                prev = table[i];
                table[i] = table[i]->next;
                free(prev);
            }
}

hash_elem_t **create_hash_table(size_t len)
{
    return (hash_elem_t **) malloc(len * sizeof(hash_elem_t *));
}

size_t count_collisions(hash_elem_t **table, size_t len)
{
    size_t collisions = 0;
    hash_elem_t *temp;
    for (size_t i = 0; i < len; i++)
    {
        if (table[i] && table[i]->next)
        {
            temp = table[i];
            while (temp)
            {
                temp = temp->next;
                collisions++;
            }
            collisions--;
        }
    }
    return collisions;
}

size_t max_depth(hash_elem_t **table, size_t len)
{
    size_t mx_dep = 0;
    size_t cur_dep = 0;
    hash_elem_t *temp;
    for (size_t i = 0; i < len; i++)
    {
        if (table[i] && table[i]->next)
        {
            temp = table[i];
            while (temp)
            {
                temp = temp->next;
                cur_dep++;
            }
            if (cur_dep > mx_dep)
                mx_dep = cur_dep;
            cur_dep = 0;
        }
    }
    return mx_dep;
}

int is_prime(int num)
{
    for (int i = num - 1; i > 1; i--)
        if (num % i == 0)
            return 0;
    return 1;
}

size_t nearest_bigger_prime(size_t num)
{
    num++;
    while (!is_prime(num))
        num++;
    return num;
}

hash_elem_t **hash_table_restructure(hash_elem_t **table, size_t *len, size_t mx_dep)
{
    size_t cur_mx_dep;
    hash_elem_t **new;
    size_t divider;
    divider = nearest_bigger_prime(*len);
    new = create_hash_table(divider);

    hash_elem_t *temp;
    for (size_t i = 0; i < *len; i++)
    {
        if (table[i])
        {
            temp = table[i];
            while (temp)
            {
                add_element_hash_table(new, temp->hash_value.name, divider);
                temp = temp->next;
            }
        }
    }    
    *len = divider;
    return new;
}

