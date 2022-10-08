#include "../inc/input_output.h"

void split(char str[], country_t *country, size_t *len, char type[])
{
    char tmp[MAX_LEN];
    strcpy(tmp, str);
    char *istr = strtok(tmp, " ");
    int flag = 0;
    while (istr != NULL && *len < 5)
    {
        flag = 1;
        if (*len == 0)
            strcpy(country->country, istr);
        else if (*len == 1)
            country->population = atoi(istr);
        else if (*len == 2)
            strcpy(country->capital, istr);
        else if (*len == 3)
            strcpy(country->continent, istr);
        else if (*len == 4)
            strcpy(country->vaccination, istr);
        ++(*len);
        istr = strtok(NULL, " ");
    }
    if (flag)
    {
        if (strcmp(istr, "excursion") == 0)
        {
            strcpy(type, "excursion");
            country->holiday_type.type = 1;
            istr = strtok(NULL, " ");
            ++(*len);
            while (istr != NULL)
            {
                if (*len == 6)
                    country->holiday_type.kind_t.excursion.objects = atoi(istr);
                else if (*len == 7)
                    strcpy(country->holiday_type.kind_t.excursion.main_type, istr);
                ++(*len);
                istr = strtok(NULL, " ");
            }
        }
        else if (strcmp(istr, "beach") == 0)
        {
            strcpy(type, "beach");
            country->holiday_type.type = 2;
            istr = strtok(NULL, " ");
            ++(*len);
            while (istr != NULL)
            {
                if (*len == 6)
                    strcpy(country->holiday_type.kind_t.beach.main_season, istr);
                else if (*len == 7)
                    country->holiday_type.kind_t.beach.air_temp = atoi(istr);
                else if (*len == 8)
                    country->holiday_type.kind_t.beach.water_temp = atoi(istr);
                else if (*len == 9)
                    country->holiday_type.kind_t.beach.fly_time = atoi(istr);

                ++(*len);
                istr = strtok(NULL, " ");
            }
        }
        else if (strcmp(istr, "sport") == 0)
        {
            strcpy(type, "sport");
            country->holiday_type.type = 3;
            istr = strtok(NULL, " ");
            ++(*len);
            while (istr != NULL)
            {
                if (*len == 6)
                    strcpy(country->holiday_type.kind_t.sport.sport_kind, istr);
                else if (*len == 7)
                    country->holiday_type.kind_t.sport.min_price = atoi(istr);
                ++(*len);
                istr = strtok(NULL, " ");
            }
        }
    }
}

void print_country_t(country_t country, int type)
{
    printf("%s %zu %s %s %s ", country.country, country.population, country.capital, country.continent, country.vaccination);
    if (type == 1)
        printf("%zu %s\n", country.holiday_type.kind_t.excursion.objects, country.holiday_type.kind_t.excursion.main_type);
    else if (type == 2)
        printf("%s %d %d %zu\n", country.holiday_type.kind_t.beach.main_season, country.holiday_type.kind_t.beach.air_temp, country.holiday_type.kind_t.beach.water_temp, country.holiday_type.kind_t.beach.fly_time);
    else if (type == 3)
        printf("%s %zu\n", country.holiday_type.kind_t.sport.sport_kind, country.holiday_type.kind_t.sport.min_price);
}

void print_table_t(table_t table)
{
    size_t size = table.size;
    for (size_t i = 0; i < size; i++)
        print_country_t(table.countries[i], table.countries[i].holiday_type.type);
}

void print_keys(table_t table)
{
    for (size_t i = 0; i < table.size; i++)
        printf("%zu: %s\n", table.keys[i].index, table.keys[i].country);
}

size_t file_count_elems(FILE *f, size_t *amount)
{
    char str[MAX_LEN];
    while (!feof(f))
    {
        if (!fgets(str, MAX_LEN, f))
            return FILE_ERROR;
        ++(*amount);
    }
    return EXIT_SUCCESS;
}

size_t file_read(FILE *f, size_t *amount, table_t *table)
{
    *amount = 0;
    file_count_elems(f, amount);
    rewind(f);
    char str[MAX_LEN];
    printf("\n");
    for (size_t i = 0; i < *amount; i++)
    {
        fgets(str, MAX_LEN, f);
        str[strlen(str) - 1] = 0;
        size_t len = 0;
        country_t country;
        char type[MAX_STR_LEN];
        split(str, &country, &len, type);

        table->countries[i] = country;
        table->size += 1;
    }
    rewind(f);

    // create_keys(table);
    return EXIT_SUCCESS;
}

size_t file_add_country(FILE *f, country_t country)
{
    if (fprintf(f, "%s %zu %s %s %s ", country.country, country.population, country.capital, country.continent, country.vaccination) < 0)
        return WRITE_ERROR;
    if (country.holiday_type.type == 1)
    {
        if (fprintf(f, "%s %zu %s\n", "excursion", country.holiday_type.kind_t.excursion.objects, country.holiday_type.kind_t.excursion.main_type) < 0)
            return WRITE_ERROR;
    }
    else if (country.holiday_type.type == 2)
    {
        if (fprintf(f, "%s %s %d %d %zu\n", "beach", country.holiday_type.kind_t.beach.main_season, country.holiday_type.kind_t.beach.air_temp, country.holiday_type.kind_t.beach.water_temp, country.holiday_type.kind_t.beach.fly_time) < 0)
            return WRITE_ERROR;
    }
    else if (country.holiday_type.type == 3)
    {
        if (fprintf(f, "%s %s %zu\n", "sport", country.holiday_type.kind_t.sport.sport_kind, country.holiday_type.kind_t.sport.min_price) < 0)
            return WRITE_ERROR;
    }
    return EXIT_SUCCESS;
}

void print_menu(void)
{
    printf("\nСписок команд:\n\n"
           "1. Прочитать файл.\n"
           "2. Распечатать таблицу.\n"
           "3. Сортировка таблицы выбором (по названию страны).\n"
           "4. Сортировка таблицы функцией qsort (по названию страны).\n"
           "5. Сортировка ключей выбором (по названию страны).\n"
           "6. Сортировка ключей функцией qsort (по названию страны).\n"
           "7. Вывести упорядоченный массив ключей (по названию страны).\n"
           "8. Вывести упорядоченную таблицу, используя упорядоченный массив ключей.\n"
           "9. Добавить страну в конец файла.\n"
           "10. Вывести список стран, на материках которых можно заняться данным видом спорта.\n"
           "11. Удалить страну по заданному полю и его значению.\n"
           "0. Приостановить работу программы.\n\n"
           "Введите желаемую команду: ");
}

size_t print_countries_with_continent_sport(table_t *table, char continent[], char sport[])
{
    size_t flag = 0;
    printf("\n");
    for (size_t i = 0; i < table->size; i++)
    {
        if (strcmp(table->countries[i].continent, continent) == 0 && strcmp(table->countries[i].holiday_type.kind_t.sport.sport_kind, sport) == 0)
        {
            flag = 1;
            printf("- ");
            print_country_t(table->countries[i], table->countries[i].holiday_type.type);
        }
    }
    if (!flag)
        return NOT_SUITABLES_ERROR;
    return EXIT_SUCCESS;
}

void print_country_using_key(size_t index, table_t table)
{
    printf("%s %zu %s %s %s ", table.countries[index].country, table.countries[index].population, table.countries[index].capital, table.countries[index].continent, table.countries[index].vaccination);
    if (table.countries[index].holiday_type.type == 1)
        printf("%zu %s\n", table.countries[index].holiday_type.kind_t.excursion.objects, table.countries[index].holiday_type.kind_t.excursion.main_type);
    else if (table.countries[index].holiday_type.type == 2)
        printf("%s %d %d %zu\n", table.countries[index].holiday_type.kind_t.beach.main_season, table.countries[index].holiday_type.kind_t.beach.air_temp, table.countries[index].holiday_type.kind_t.beach.water_temp, table.countries[index].holiday_type.kind_t.beach.fly_time);
    else if (table.countries[index].holiday_type.type == 3)
        printf("%s %zu\n", table.countries[index].holiday_type.kind_t.sport.sport_kind, table.countries[index].holiday_type.kind_t.sport.min_price);
}

void table_t_print_with_keys(table_t table)
{
    printf("\n");
    for (size_t i = 0; i < table.size; i++)
        print_country_using_key(table.keys[i].index, table);
}

// size_t split_user_country_input(char str[])
// {
//     char *istr = strtok(str, " ");
//     while (istr != NULL)
//     {
//         printf("%s\n", istr);
//         istr = strtok(NULL, " ");
//     }
//     return EXIT_SUCCESS;
// }

void clean_stdin(void)
{
    int c;
    do 
    {
        c = getchar();
    } 
    while (c != '\n' && c != EOF);
}

void file_rewrite(FILE *f, table_t table)
{
    for (size_t i = 0; i < table.size; i++)
        file_add_country(f, table.countries[i]);
}