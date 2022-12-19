#include "hash_table_t.h"

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
    // strcpy(temp->name, word);
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
    // size_t cur_mx_dep;
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

// In hash

hash_elem_step_t **create_hash_table_step(size_t len)
{
    return (hash_elem_step_t **) malloc(len * 2 * sizeof(hash_elem_step_t *));
}

int add_element_hash_table_step(hash_elem_step_t **table, char word[MAX_LEN], size_t len)
{
    size_t hash = hash_func(word, len);
    size_t tmp = hash;

    hash_elem_step_t *temp = NULL;

    if (table[hash])
    {
        while (table[hash] && hash < len)
            hash++;
    }
    temp = (hash_elem_step_t *)malloc(sizeof(hash_elem_step_t));
    strcpy(temp->hash_value.name, word);
    temp->hash_index = tmp;
    table[hash] = temp;
    return EXIT_SUCCESS;
}

size_t wrong_hash_elements(hash_elem_step_t **table, size_t len)
{
    size_t count = 0;
    for (size_t i = 0; i < len; i++)
        if (table[i] && table[i]->hash_index != i)
        {
            count++;
            printf("%4zu (hash = %zu): ", i, table[i]->hash_index);
            printf("%s\n", table[i]->hash_value.name);
        }
    return count;
}

hash_elem_step_t **hash_table_step_restructure(hash_elem_t **table, size_t *len, size_t wrong_elems)
{
    // size_t cur_mx_dep;
    hash_elem_step_t **new;
    size_t divider;
    divider = nearest_bigger_prime(*len);
    new = create_hash_table_step(divider);

    for (size_t i = 0; i < *len * 2; i++)
        if (table[i])
            add_element_hash_table_step(new, table[i]->hash_value.name, divider);
    *len = divider;
    return new;
}

size_t hash_table_step_find(hash_elem_step_t **table, char word[MAX_LEN], size_t *counter, size_t len, uint64_t *time)
{
    size_t hash = hash_func(word, len);
    size_t tmp = hash;

    uint64_t start, end;
    start = tick();
    if (!strcmp(word, table[hash]->hash_value.name))
    {
        end = tick();
        *time = end - start;
        return EXIT_SUCCESS;
    }
    else
    {
        tmp++;
        while (tmp < len)
        {
            if (table[tmp])
            {
                if (strcmp(word, table[tmp]->hash_value.name))
                {
                    tmp++;
                    (*counter)++;
                } 
                else
                {
                    end = tick();
                    *time = end - start;
                    return EXIT_SUCCESS;
                }
            }
            else
                tmp++;
        }
    }
    return EXIT_FAILURE;
}

size_t hash_table_step_fill_from_file(FILE *f, hash_elem_step_t **table, size_t len)
{
    char word[MAX_LEN];
    for (size_t i = 0; i < len; i++)
    {
        if (fscanf(f, "%s", word) != 1)
            return FILE_READ_ERROR;

        add_element_hash_table_step(table, word, len);
    }
    return EXIT_SUCCESS;
}

void hash_table_step_print(hash_elem_step_t **table, size_t len)
{
    printf("%4s %10s\n", "KEY", "VALUE");

    for (size_t i = 0; i < len; i++)
        if (table[i])
        {
            printf("%4zu (hash = %zu): ", i, table[i]->hash_index);
            printf("%s\n", table[i]->hash_value.name);
        }
}

void hash_table_step_free(hash_elem_step_t **table, size_t len)
{
    for (size_t i = 0; i < len; i++)
        free(table[i]);
}
