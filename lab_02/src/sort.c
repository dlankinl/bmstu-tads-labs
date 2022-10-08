#include "../inc/sort.h"

int comparator(const void *ptr_left, const void *ptr_right)
{
    country_t *country_l = (country_t *)ptr_left;
    country_t *country_r = (country_t *)ptr_right;
    return strcmp(country_l->country, country_r->country);
}

int comparator_keys(const void *ptr_left, const void *ptr_right)
{
    keys_t *key_l = (keys_t *)ptr_left;
    keys_t *key_r = (keys_t *)ptr_right;
    return strcmp(key_l->country, key_r->country);
}

void table_t_qsort(table_t *table)
{
    qsort(table->countries, table->size, sizeof(country_t), (int(*) (const void *, const void *)) comparator);
    // create_keys(table);
} 

void table_t_choice_sort(table_t *table)
{
    size_t min;
    country_t c;

    for (size_t i = 0; i < table->size - 1; i++)
    {
        min = i;
        for (size_t j = i + 1; j < table->size; j++)
            if (strcmp(table->countries[j].country, table->countries[min].country) < 0)
                min = j;

        c = table->countries[i];
        table->countries[i] = table->countries[min];
        table->countries[min] = c;
    }
    // create_keys(table);
}

void keys_t_choice_sort(table_t *table)
{
    size_t min;
    char tmp[MAX_STR_LEN];
    size_t tmp_ind;

    for (size_t i = 0; i < table->size - 1; i++)
    {
        min = i;
        for (size_t j = i + 1; j < table->size; j++)
            if (strcmp(table->keys[j].country, table->keys[min].country) < 0)
                min = j;

        strcpy(tmp, table->keys[i].country);
        strcpy(table->keys[i].country, table->keys[min].country);
        strcpy(table->keys[min].country, tmp);
        tmp_ind = table->keys[i].index;
        table->keys[i].index = table->keys[min].index;
        table->keys[min].index = tmp_ind;
    }
}

void keys_t_qsort(table_t *table)
{
    qsort(table->keys, table->size, sizeof(keys_t), (int(*) (const void *, const void *)) comparator_keys);
}