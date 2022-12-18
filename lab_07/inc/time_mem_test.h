#ifndef __TIME_MEM_TEST_H__
#define __TIME_MEM_TEST_H__

#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    size_t count_hash_find;
    size_t count_bst_find;
    size_t count_avl_find;
} compares_t;

typedef struct
{
    uint64_t hash_find;
    uint64_t bst_find;
    uint64_t avl_find;
} times_t;

uint64_t tick(void);

#endif // __TIME_MEM_TEST_H__