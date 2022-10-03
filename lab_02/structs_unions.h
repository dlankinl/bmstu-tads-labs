#ifndef __STRUCTS_UNIONS_H__
#define __STRUCTS_UNIONS_H__

#include <stddef.h>
#include <stdbool.h>

#define MAX_MAIN_TYPE_LEN 7
#define MAX_SEASON_LEN 6
#define MAX_SPORT_KIND_LEN 10
#define MAX_STR_LEN 63
#define MAX_AMOUNT 500

typedef struct
{
    size_t objects;
    char main_type[MAX_MAIN_TYPE_LEN + 1];
} excursion_t;

typedef struct
{
    char main_season[MAX_SEASON_LEN + 1];
    int air_temp;
    int water_temp;
    size_t fly_time;
} beach_t;

typedef struct
{
    char sport_kind[MAX_SPORT_KIND_LEN + 1];
    size_t min_price;
} sport_t;

// typedef union
// {
//     excursion_t excursion;
//     beach_t beach;
//     sport_t sport;
// } holiday_t;

typedef struct
{
    size_t type;
    union kind
    {
        excursion_t excursion;
        beach_t beach;
        sport_t sport;
    } kind_t;
} holiday_t;

typedef struct
{
    char country[MAX_STR_LEN + 1];
    size_t population;
    char capital[MAX_STR_LEN + 1];
    char continent[MAX_STR_LEN + 1];
    size_t vaccination;
    holiday_t holiday_type;
} country_t;

typedef struct
{
    size_t index;
    char country[MAX_STR_LEN + 1];
} keys_t;

typedef struct
{
    country_t countries[MAX_AMOUNT];
    keys_t keys[MAX_AMOUNT];
    size_t size;
} table_t;



#endif // __STRUCTS_UNIONS_H__
