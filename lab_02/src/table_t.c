#include "../inc/table_t.h"

void delete_country_t(table_t *table, size_t pos)
{
    country_t tmp;
    for (size_t i = pos; i < table->size - 1; i++)
    {
        tmp = table->countries[i];
        table->countries[i] = table->countries[i + 1];
        table->countries[i + 1] = tmp;
    }
    memset(&(table->countries[table->size - 1]), 0, sizeof(country_t));
    table->size--;
}

size_t table_t_delete_by_values(FILE *f, table_t *table, char field[MAX_STR_LEN], char value[MAX_STR_LEN])
{
    for (size_t i = 0; i < table->size; i++)
    {
        if (strcmp("country", field) == 0)
        {
            if (strcmp(table->countries[i].country, value) == 0)
            {
                delete_country_t(table, i);
                i--;
            }
        }
        else if (strcmp("population", field) == 0)
        {
            size_t ch_value = atoi(value);
            if (!ch_value)
            {
                printf("Введите число!\n");
                return INCORRECT_INPUT;
            }
            if (table->countries[i].population == ch_value)
            {
                delete_country_t(table, i);
                i--;
            }
        }
        else if (strcmp("capital", field) == 0)
        {
            if (strcmp(table->countries[i].capital, value) == 0)
            {
                delete_country_t(table, i);
                i--;
            }
        }
        else if (strcmp("continent", field) == 0)
        {
            if (strcmp(table->countries[i].continent, value) == 0)
            {
                delete_country_t(table, i);
                i--;
            }
        }
        else if (strcmp("vaccination", field) == 0)
        {
            if (strcmp(table->countries[i].vaccination, value) == 0)
            {
                delete_country_t(table, i);
                i--;
            }
        }
        else if (strcmp("objects", field) == 0)
        {
            size_t ch_value = atoi(value);
            if (!ch_value)
            {
                printf("Введите число!\n");
                return INCORRECT_INPUT;
            }
            if (table->countries[i].holiday_type.kind_t.excursion.objects == ch_value)
            {
                delete_country_t(table, i);
                i--;
            }
        }
        else if (strcmp("main_type", field) == 0)
        {
            if (strcmp(table->countries[i].holiday_type.kind_t.excursion.main_type, value) == 0)
            {
                delete_country_t(table, i);
                i--;
            }
        }
        else if (strcmp("main_season", field) == 0)
        {
            if (strcmp(table->countries[i].holiday_type.kind_t.beach.main_season, value) == 0)
            {
                delete_country_t(table, i);
                i--;
            }
        }
        else if (strcmp("air_temp", field) == 0)
        {
            int ch_value = atoi(value);
            if (!ch_value)
            {
                printf("Введите число!\n");
                return INCORRECT_INPUT;
            }
            if (table->countries[i].holiday_type.kind_t.beach.air_temp == ch_value)
            {
                delete_country_t(table, i);
                i--;
            }
        }
        else if (strcmp("water_temp", field) == 0)
        {
            int ch_value = atoi(value);
            if (!ch_value)
            {
                printf("Введите число!\n");
                return INCORRECT_INPUT;
            }
            if (table->countries[i].holiday_type.kind_t.beach.water_temp == ch_value)
            {
                delete_country_t(table, i);
                i--;
            }
        }
        else if (strcmp("fly_time", field) == 0)
        {
            size_t ch_value = atoi(value);
            if (!ch_value)
            {
                printf("Введите число!\n");
                return INCORRECT_INPUT;
            }
            if (table->countries[i].holiday_type.kind_t.beach.fly_time == ch_value)
            {
                delete_country_t(table, i);
                i--;
            }
        }
        else if (strcmp("sport_kind", field) == 0)
        {
            if (strcmp(table->countries[i].holiday_type.kind_t.sport.sport_kind, value) == 0)
            {
                delete_country_t(table, i);
                i--;
            }
        }
        else if (strcmp("min_price", field) == 0)
        {
            size_t ch_value = atoi(value);
            if (!ch_value)
            {
                printf("Введите число!\n");
                return INCORRECT_INPUT;
            }
            if (table->countries[i].holiday_type.kind_t.sport.min_price == ch_value)
            {
                delete_country_t(table, i);
                i--;
            }
        }
        else
        {
            printf("Поле не существует!\n");
            return FIELD_DOES_NOT_EXIST;
        }
    }
    file_rewrite(f, *table);

    return EXIT_SUCCESS;
}

void table_t_clear(table_t *table)
{
    table->size = 0;
}

void create_keys(table_t *table)
{
    for (size_t i = 0; i < table->size; i++)
    {
        table->keys[i].index = i;
        strcpy(table->keys[i].country, table->countries[i].country);
    }
}

void table_t_add_country(table_t *table, FILE *f)
{
    printf("\nВведите необходимые данные в строку:\n\n"
           "1. Название страны.\n"
           "2. Население (в млн.).\n"
           "3. Столица.\n"
           "4. Название материка.\n"
           "5. Необходимость вакцинации (No, Yes).\n\n"
           "6.1. Экскурсия (excursion).\n"
           "6.1.1. Количество достопримечательностей.\n"
           "6.1.2. Тип экскурсии (history, art, nature).\n\n"
           "6.2. Пляжный отдых (beach).\n"
           "6.2.1. Лучшее время года для посещения (winter, spring, summer, autumn).\n"
           "6.2.2. Температура воздуха в это время года.\n"
           "6.2.3. Температура воды в это время года.\n"
           "6.2.4. Время перелёта (в часах).\n\n"
           "6.3. Спортивный отдых (sport).\n"
           "6.3.1. Вид спорта (alpine_ski, climbing, surfing).\n"
           "6.3.2. Минимальная стоимость (в рублях).\n\n");
    
    char str[MAX_LEN + 1];
    fgets(str, MAX_LEN + 1, stdin);
    str[strlen(str) - 1] = 0;
    country_t country;
    memset(&country, 0, sizeof(country_t));
    size_t len = 0;
    char type[MAX_STR_LEN];
    split(str, &country, &len, type);
    table->size += 1;
    table->countries[table->size - 1] = country;
    file_add_country(f, country);
    create_keys(table);
}