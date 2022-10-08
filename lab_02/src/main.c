#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/sort.h"
#include "../inc/errors.h"
#include "../inc/structs_unions.h"
#include "../inc/table_t.h"

// #define M 10

// void split(char str[], country_t *country, size_t *len, char type[])
// {
//     char tmp[MAX_LEN];
//     strcpy(tmp, str);
//     char *istr = strtok(tmp, " ");
//     int flag = 0;
//     while (istr != NULL && *len < 5)
//     {
//         flag = 1;
//         if (*len == 0)
//             strcpy(country->country, istr);
//         else if (*len == 1)
//             country->population = atoi(istr);
//         else if (*len == 2)
//             strcpy(country->capital, istr);
//         else if (*len == 3)
//             strcpy(country->continent, istr);
//         else if (*len == 4)
//             strcpy(country->vaccination, istr);
//         ++(*len);
//         istr = strtok(NULL, " ");
//     }
//     if (flag)
//     {
//         if (strcmp(istr, "excursion") == 0)
//         {
//             strcpy(type, "excursion");
//             country->holiday_type.type = 1;
//             istr = strtok(NULL, " ");
//             ++(*len);
//             while (istr != NULL)
//             {
//                 if (*len == 6)
//                     country->holiday_type.kind_t.excursion.objects = atoi(istr);
//                 else if (*len == 7)
//                     strcpy(country->holiday_type.kind_t.excursion.main_type, istr);
//                 ++(*len);
//                 istr = strtok(NULL, " ");
//             }
//         }
//         else if (strcmp(istr, "beach") == 0)
//         {
//             strcpy(type, "beach");
//             country->holiday_type.type = 2;
//             istr = strtok(NULL, " ");
//             ++(*len);
//             while (istr != NULL)
//             {
//                 if (*len == 6)
//                     strcpy(country->holiday_type.kind_t.beach.main_season, istr);
//                 else if (*len == 7)
//                     country->holiday_type.kind_t.beach.air_temp = atoi(istr);
//                 else if (*len == 8)
//                     country->holiday_type.kind_t.beach.water_temp = atoi(istr);
//                 else if (*len == 9)
//                     country->holiday_type.kind_t.beach.fly_time = atoi(istr);

//                 ++(*len);
//                 istr = strtok(NULL, " ");
//             }
//         }
//         else if (strcmp(istr, "sport") == 0)
//         {
//             strcpy(type, "sport");
//             country->holiday_type.type = 3;
//             istr = strtok(NULL, " ");
//             ++(*len);
//             while (istr != NULL)
//             {
//                 if (*len == 6)
//                     strcpy(country->holiday_type.kind_t.sport.sport_kind, istr);
//                 else if (*len == 7)
//                     country->holiday_type.kind_t.sport.min_price = atoi(istr);
//                 ++(*len);
//                 istr = strtok(NULL, " ");
//             }
//         }
//     }
// }

// void print_country_t(country_t country, int type)
// {
//     printf("%s %zu %s %s %s ", country.country, country.population, country.capital, country.continent, country.vaccination);
//     if (type == 1)
//         printf("%zu %s\n", country.holiday_type.kind_t.excursion.objects, country.holiday_type.kind_t.excursion.main_type);
//     else if (type == 2)
//         printf("%s %d %d %zu\n", country.holiday_type.kind_t.beach.main_season, country.holiday_type.kind_t.beach.air_temp, country.holiday_type.kind_t.beach.water_temp, country.holiday_type.kind_t.beach.fly_time);
//     else if (type == 3)
//         printf("%s %zu\n", country.holiday_type.kind_t.sport.sport_kind, country.holiday_type.kind_t.sport.min_price);
// }

// void print_table_t(table_t table)
// {
//     size_t size = table.size;
//     for (size_t i = 0; i < size; i++)
//         print_country_t(table.countries[i], table.countries[i].holiday_type.type);
// }

// void create_keys(table_t *table)
// {
//     for (size_t i = 0; i < table->size; i++)
//     {
//         table->keys[i].index = i;
//         strcpy(table->keys[i].country, table->countries[i].country);
//     }
// }

// void print_keys(table_t table)
// {
//     for (size_t i = 0; i < table.size; i++)
//         printf("%zu: %s\n", table.keys[i].index, table.keys[i].country);
// }

// size_t file_count_elems(FILE *f, size_t *amount)
// {
//     char str[MAX_LEN];
//     while (!feof(f))
//     {
//         if (!fgets(str, MAX_LEN, f))
//             return FILE_ERROR;
//         ++(*amount);
//     }
//     return EXIT_SUCCESS;
// }

// size_t file_read(FILE *f, size_t *amount, table_t *table)
// {
//     *amount = 0;
//     file_count_elems(f, amount);
//     rewind(f);
//     char str[MAX_LEN];
//     printf("\n");
//     for (size_t i = 0; i < *amount; i++)
//     {
//         fgets(str, MAX_LEN, f);
//         str[strlen(str) - 1] = 0;
//         size_t len = 0;
//         country_t country;
//         char type[MAX_STR_LEN];
//         split(str, &country, &len, type);

//         table->countries[i] = country;
//         table->size += 1;
//     }
//     rewind(f);

//     create_keys(table);
//     return EXIT_SUCCESS;
// }

// int comparator(const void *ptr_left, const void *ptr_right)
// {
//     country_t *country_l = (country_t *)ptr_left;
//     country_t *country_r = (country_t *)ptr_right;
//     return strcmp(country_l->country, country_r->country);
// }

// int comparator_keys(const void *ptr_left, const void *ptr_right)
// {
//     keys_t *key_l = (keys_t *)ptr_left;
//     keys_t *key_r = (keys_t *)ptr_right;
//     return strcmp(key_l->country, key_r->country);
// }

// void table_t_qsort(table_t *table)
// {
//     qsort(table->countries, table->size, sizeof(country_t), (int(*) (const void *, const void *)) comparator);
//     create_keys(table);
// } 

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

// size_t file_add_country(FILE *f, country_t country)
// {
//     fprintf(f, "%s %zu %s %s %s ", country.country, country.population, country.capital, country.continent, country.vaccination);
//     if (country.holiday_type.type == 1)
//         fprintf(f, "%s %zu %s\n", "excursion", country.holiday_type.kind_t.excursion.objects, country.holiday_type.kind_t.excursion.main_type);
//     else if (country.holiday_type.type == 2)
//         fprintf(f, "%s %s %d %d %zu\n", "beach", country.holiday_type.kind_t.beach.main_season, country.holiday_type.kind_t.beach.air_temp, country.holiday_type.kind_t.beach.water_temp, country.holiday_type.kind_t.beach.fly_time);
//     else if (country.holiday_type.type == 3)
//         fprintf(f, "%s %s %zu\n", "sport", country.holiday_type.kind_t.sport.sport_kind, country.holiday_type.kind_t.sport.min_price);
//     return EXIT_SUCCESS;
// }

// void table_t_add_country(table_t *table, FILE *f)
// {
//     printf("\nВведите необходимые данные в строку:\n\n"
//            "1. Название страны.\n"
//            "2. Население (в млн.).\n"
//            "3. Столица.\n"
//            "4. Название материка.\n"
//            "5. Необходимость вакцинации (No, Yes).\n\n"
//            "6.1. Экскурсия (excursion).\n"
//            "6.1.1. Количество достопримечательностей.\n"
//            "6.1.2. Тип экскурсии (history, art, nature).\n\n"
//            "6.2. Пляжный отдых (beach).\n"
//            "6.2.1. Лучшее время года для посещения (winter, spring, summer, autumn).\n"
//            "6.2.2. Температура воздуха в это время года.\n"
//            "6.2.3. Температура воды в это время года.\n"
//            "6.2.4. Время перелёта (в часах).\n\n"
//            "6.3. Спортивный отдых (sport).\n"
//            "6.3.1. Вид спорта (alpine_ski, climbing, surfing).\n"
//            "6.3.2. Минимальная стоимость (в рублях).\n\n");
    
//     char str[MAX_LEN + 1];
//     fgets(str, MAX_LEN + 1, stdin);
//     str[strlen(str) - 1] = 0;
//     country_t country;
//     memset(&country, 0, sizeof(country_t));
//     size_t len = 0;
//     char type[MAX_STR_LEN];
//     split(str, &country, &len, type);
//     table->size += 1;
//     table->countries[table->size - 1] = country;
//     file_add_country(f, country);
//     create_keys(table);
// }

// void table_t_choice_sort(table_t *table)
// {
//     size_t min;
//     country_t c;

//     for (size_t i = 0; i < table->size - 1; i++)
//     {
//         min = i;
//         for (size_t j = i + 1; j < table->size; j++)
//             if (strcmp(table->countries[j].country, table->countries[min].country) < 0)
//                 min = j;

//         c = table->countries[i];
//         table->countries[i] = table->countries[min];
//         table->countries[min] = c;
//     }
//     create_keys(table);
// }

// void keys_t_choice_sort(table_t *table)
// {
//     size_t min;
//     char tmp[MAX_STR_LEN];
//     size_t tmp_ind;

//     for (size_t i = 0; i < table->size - 1; i++)
//     {
//         min = i;
//         for (size_t j = i + 1; j < table->size; j++)
//             if (strcmp(table->keys[j].country, table->keys[min].country) < 0)
//                 min = j;

//         strcpy(tmp, table->keys[i].country);
//         strcpy(table->keys[i].country, table->keys[min].country);
//         strcpy(table->keys[min].country, tmp);
//         tmp_ind = table->keys[i].index;
//         table->keys[i].index = table->keys[min].index;
//         table->keys[min].index = tmp_ind;
//     }
// }

// void keys_t_qsort(table_t *table)
// {
//     qsort(table->keys, table->size, sizeof(keys_t), (int(*) (const void *, const void *)) comparator_keys);
// }

// void table_t_clear(table_t *table)
// {
//     table->size = 0;
// }

// void print_menu(void)
// {
//     printf("\nСписок команд:\n\n"
//            "1. Прочитать файл.\n"
//            "2. Распечатать таблицу.\n"
//            "3. Сортировка таблицы выбором (по названию страны).\n"
//            "4. Сортировка таблицы функцией qsort (по названию страны).\n"
//            "5. Сортировка ключей выбором (по названию страны).\n"
//            "6. Сортировка ключей функцией qsort (по названию страны).\n"
//            "7. Вывести упорядоченный массив ключей (по названию страны).\n"
//            "8. Вывести упорядоченную таблицу, используя упорядоченный массив ключей.\n"
//            "9. Добавить страну в конец файла.\n"
//            "10. Вывести список стран, на материках которых можно заняться данным видом спорта.\n"
//            "11. Удалить страну по заданному полю и его значению.\n"
//            "0. Приостановить работу программы.\n\n"
//            "Введите желаемую команду: ");
// }

// size_t print_countries_with_continent_sport(table_t *table, char continent[], char sport[])
// {
//     size_t flag = 0;
//     printf("\n");
//     for (size_t i = 0; i < table->size; i++)
//     {
//         if (strcmp(table->countries[i].continent, continent) == 0 && strcmp(table->countries[i].holiday_type.kind_t.sport.sport_kind, sport) == 0)
//         {
//             flag = 1;
//             printf("- ");
//             print_country_t(table->countries[i], table->countries[i].holiday_type.type);
//         }
//     }
//     if (!flag)
//         return NOT_SUITABLES_ERROR;
//     return EXIT_SUCCESS;
// }

// void delete_country_t(table_t *table, size_t pos)
// {
//     country_t tmp;
//     for (size_t i = pos; i < table->size - 1; i++)
//     {
//         tmp = table->countries[i];
//         table->countries[i] = table->countries[i + 1];
//         table->countries[i + 1] = tmp;
//     }
//     memset(&(table->countries[table->size - 1]), 0, sizeof(country_t));
//     table->size--;
// }

// void print_country_using_key(size_t index, table_t table)
// {
//     printf("%s %zu %s %s %s ", table.countries[index].country, table.countries[index].population, table.countries[index].capital, table.countries[index].continent, table.countries[index].vaccination);
//     if (table.countries[index].holiday_type.type == 1)
//         printf("%zu %s\n", table.countries[index].holiday_type.kind_t.excursion.objects, table.countries[index].holiday_type.kind_t.excursion.main_type);
//     else if (table.countries[index].holiday_type.type == 2)
//         printf("%s %d %d %zu\n", table.countries[index].holiday_type.kind_t.beach.main_season, table.countries[index].holiday_type.kind_t.beach.air_temp, table.countries[index].holiday_type.kind_t.beach.water_temp, table.countries[index].holiday_type.kind_t.beach.fly_time);
//     else if (table.countries[index].holiday_type.type == 3)
//         printf("%s %zu\n", table.countries[index].holiday_type.kind_t.sport.sport_kind, table.countries[index].holiday_type.kind_t.sport.min_price);
// }

// void table_t_print_with_keys(table_t table)
// {
//     printf("\n");
//     for (size_t i = 0; i < table.size; i++)
//         print_country_using_key(table.keys[i].index, table);
// }

// void file_rewrite(FILE *f, table_t table)
// {
//     for (size_t i = 0; i < table.size; i++)
//         file_add_country(f, table.countries[i]);
// }

// size_t table_t_delete_by_values(FILE *f, table_t *table, char field[MAX_STR_LEN], char value[MAX_STR_LEN])
// {
//     for (size_t i = 0; i < table->size; i++)
//     {
//         if (strcmp("country", field) == 0)
//         {
//             if (strcmp(table->countries[i].country, value) == 0)
//             {
//                 delete_country_t(table, i);
//                 i--;
//             }
//         }
//         else if (strcmp("population", field) == 0)
//         {
//             size_t ch_value = atoi(value);
//             if (!ch_value)
//             {
//                 printf("Введите число!\n");
//                 return INCORRECT_INPUT;
//             }
//             if (table->countries[i].population == ch_value)
//             {
//                 delete_country_t(table, i);
//                 i--;
//             }
//         }
//         else if (strcmp("capital", field) == 0)
//         {
//             if (strcmp(table->countries[i].capital, value) == 0)
//             {
//                 delete_country_t(table, i);
//                 i--;
//             }
//         }
//         else if (strcmp("continent", field) == 0)
//         {
//             if (strcmp(table->countries[i].continent, value) == 0)
//             {
//                 delete_country_t(table, i);
//                 i--;
//             }
//         }
//         else if (strcmp("vaccination", field) == 0)
//         {
//             if (strcmp(table->countries[i].vaccination, value) == 0)
//             {
//                 delete_country_t(table, i);
//                 i--;
//             }
//         }
//         else if (strcmp("objects", field) == 0)
//         {
//             size_t ch_value = atoi(value);
//             if (!ch_value)
//             {
//                 printf("Введите число!\n");
//                 return INCORRECT_INPUT;
//             }
//             if (table->countries[i].holiday_type.kind_t.excursion.objects == ch_value)
//             {
//                 delete_country_t(table, i);
//                 i--;
//             }
//         }
//         else if (strcmp("main_type", field) == 0)
//         {
//             if (strcmp(table->countries[i].holiday_type.kind_t.excursion.main_type, value) == 0)
//             {
//                 delete_country_t(table, i);
//                 i--;
//             }
//         }
//         else if (strcmp("main_season", field) == 0)
//         {
//             if (strcmp(table->countries[i].holiday_type.kind_t.beach.main_season, value) == 0)
//             {
//                 delete_country_t(table, i);
//                 i--;
//             }
//         }
//         else if (strcmp("air_temp", field) == 0)
//         {
//             int ch_value = atoi(value);
//             if (!ch_value)
//             {
//                 printf("Введите число!\n");
//                 return INCORRECT_INPUT;
//             }
//             if (table->countries[i].holiday_type.kind_t.beach.air_temp == ch_value)
//             {
//                 delete_country_t(table, i);
//                 i--;
//             }
//         }
//         else if (strcmp("water_temp", field) == 0)
//         {
//             int ch_value = atoi(value);
//             if (!ch_value)
//             {
//                 printf("Введите число!\n");
//                 return INCORRECT_INPUT;
//             }
//             if (table->countries[i].holiday_type.kind_t.beach.water_temp == ch_value)
//             {
//                 delete_country_t(table, i);
//                 i--;
//             }
//         }
//         else if (strcmp("fly_time", field) == 0)
//         {
//             size_t ch_value = atoi(value);
//             if (!ch_value)
//             {
//                 printf("Введите число!\n");
//                 return INCORRECT_INPUT;
//             }
//             if (table->countries[i].holiday_type.kind_t.beach.fly_time == ch_value)
//             {
//                 delete_country_t(table, i);
//                 i--;
//             }
//         }
//         else if (strcmp("sport_kind", field) == 0)
//         {
//             if (strcmp(table->countries[i].holiday_type.kind_t.sport.sport_kind, value) == 0)
//             {
//                 delete_country_t(table, i);
//                 i--;
//             }
//         }
//         else if (strcmp("min_price", field) == 0)
//         {
//             size_t ch_value = atoi(value);
//             if (!ch_value)
//             {
//                 printf("Введите число!\n");
//                 return INCORRECT_INPUT;
//             }
//             if (table->countries[i].holiday_type.kind_t.sport.min_price == ch_value)
//             {
//                 delete_country_t(table, i);
//                 i--;
//             }
//         }
//         else
//         {
//             printf("Поле не существует!\n");
//             return FIELD_DOES_NOT_EXIST;
//         }
//     }
//     file_rewrite(f, *table);

//     return EXIT_SUCCESS;
// }

// void clean_stdin(void)
// {
//     int c;
//     do 
//     {
//         c = getchar();
//     } 
//     while (c != '\n' && c != EOF);
// }

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        size_t cmd = 0;
        size_t rc = 0;
        
        size_t amount = 0;
        table_t table;
        size_t is_file_loaded = 0;
        FILE *f = NULL;
        while (1)
        {
            print_menu();

            if (scanf("%zu", &cmd) != 1)
            {
                printf("Неверный ввод!\n");
                return INCORRECT_INPUT;
            }

            if (cmd == 1)
            {
                FILE *f = NULL;
                f = fopen(argv[1], "r");
                if (!f)
                {
                    printf("Невозможно открыть файл.\n");
                    return FILE_ERROR;
                }
                memset(&table, 0, sizeof(table_t));
                if (!file_read(f, &amount, &table))
                    is_file_loaded = 1;
                create_keys(&table);
                fclose(f);
            }
            else if (cmd == 2)
            {
                if (is_file_loaded)
                    print_table_t(table);
                else
                    printf("Сначала загрузите данные из файла!\n");
            }
            else if (cmd == 3)
            {
                if (is_file_loaded)
                    table_t_choice_sort(&table);
                else
                    printf("Сначала загрузите данные из файла!\n");
            }
            else if (cmd == 4)
            {
                if (is_file_loaded)
                {
                    table_t_qsort(&table);
                    create_keys(&table);
                }
                else
                    printf("Сначала загрузите данные из файла!\n");
            }
            else if (cmd == 5)
            {
                if (is_file_loaded)
                    keys_t_choice_sort(&table);
                else
                    printf("Сначала загрузите данные из файла!\n");
            }
            else if (cmd == 6)
            {
                if (is_file_loaded)
                    keys_t_qsort(&table);
                else
                    printf("Сначала загрузите данные из файла!\n");
            }
            else if (cmd == 7)
            {
                if (is_file_loaded)
                    print_keys(table);
                else
                    printf("Сначала загрузите данные из файла!\n");
            }
            else if (cmd == 8)
            {
                if (is_file_loaded)
                    table_t_print_with_keys(table);
                else
                    printf("Сначала загрузите данные из файла!\n");
            }
            else if (cmd == 9)
            {
                if (is_file_loaded)
                {
                    clean_stdin();
                    f = fopen(argv[1], "a");
                    if (!f)
                        return FILE_ERROR;
                    table_t_add_country(&table, f);
                    fclose(f);
                }
                else
                    printf("Сначала загрузите данные из файла!\n");
            }
            else if (cmd == 10)
            {
                if (is_file_loaded)
                {
                    char continent[MAX_STR_LEN];
                    char sport[MAX_STR_LEN];
                    if (scanf("%s %s", continent, sport) != 2)
                        printf("Неверный ввод!\n");
                    rc = print_countries_with_continent_sport(&table, continent, sport);
                    if (rc)
                        printf("Стран, находящихся на указанном материке, с данным видом спорта в таблице нет!");
                }
                else
                    printf("Сначала загрузите данные из файла!\n");
            }
            else if (cmd == 11)
            {
                if (is_file_loaded)
                {
                    char field[MAX_STR_LEN];
                    char value[MAX_STR_LEN];
                    if (scanf("%s %s", field, value) != 2)
                        printf("Неверный ввод!\n");
                    f = fopen(argv[1], "w");
                    if (!f)
                    {
                        printf("Невозможно открыть файл.\n");
                        return FILE_ERROR;
                    }
                    table_t_delete_by_values(f, &table, field, value);
                    fclose(f);
                }
                else
                    printf("Сначала загрузите данные из файла!\n");
            }
            else if (cmd == 0)
            {
                printf("Завершение работы...\n");
                break;
            }
            else
                printf("Такой команды не существует!\n");
        }
    }
    else
    {
        printf("Не указан обрабатываемый файл.\n");
        return WRONG_ARGS;
    }
}