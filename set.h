#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct set_entry_t
{
    int val;
    struct set_entry_t *next;
} set_entry_t;

typedef struct
{
    set_entry_t **buckets;
    size_t size;
    size_t elements;
} set_t;

void set_make(set_t *set, const size_t size);
void set_free(set_t *set);

bool set_add(set_t *set, int val);
bool set_contains(set_t *set, int val);
bool set_remove(set_t *set, int val);

void set_print(set_t *set);

