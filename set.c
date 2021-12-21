#include <assert.h>
#include <stdio.h>

#include "set.h"

static int _hash_internal(set_t *set, int k)
{
    k = abs(k);
    return k % set->size;
}

void set_make(set_t *set, const size_t size)
{
    set->buckets = malloc(sizeof(set_entry_t *) * size);
    set->size = size;
    set->elements = 0;
}

static void set_entry_free(set_entry_t *entry)
{
    if (entry == NULL)
    {
        return;
    }

    set_entry_free(entry->next);
    free(entry);
}

void set_free(set_t *set)
{
    assert(set->buckets);

    for (size_t i = 0; i < set->size; ++i)
    {
        set_entry_free(set->buckets[i]);
    }

    set->size = 0;
    set->elements = 0;
    free(set->buckets);
}

bool set_add(set_t *set, int val)
{
    int k = _hash_internal(set, val);
    set_entry_t *cur = set->buckets[k];

    while (cur != NULL)
    {
        if (cur->val == val) {
            return false;
        }

        cur = cur->next;
    }

    set_entry_t *entry = malloc(sizeof(set_entry_t));
    entry->val = val;
    entry->next = set->buckets[k];
    set->buckets[k] = entry;
    set->elements++;
    return true;
}

bool set_contains(set_t *set, int val)
{
    int k = _hash_internal(set, val);
    set_entry_t *cur = set->buckets[k];

    while (cur != NULL)
    {
        if (cur->val == val)
        {
            return true;
        }

        cur = cur->next;
    }

    return false;
}

bool set_remove(set_t *set, int val)
{
    int k = _hash_internal(set, val);
    set_entry_t *cur = set->buckets[k], *prev;

    while (cur != NULL)
    {
        if (cur->val == val)
        {
            if (prev != NULL)
            {
                prev->next = cur->next;
            }

            if (cur == set->buckets[k])
            {
                set->buckets[k] = NULL;
            }
            free(cur);

            set->elements--;
            return true;
        }

        prev = cur;
        cur = cur->next;
    }

    return false;
}

static void set_print_entry(set_entry_t *entry)
{
    if (entry == NULL)
    {
        return;
    }

    printf("%d ", entry->val);
    set_print_entry(entry->next);
}

void set_print(set_t *set)
{
    printf("{ ");

    for (size_t i = 0; i < set->size; ++i)
    {
        set_print_entry(set->buckets[i]);
    }

    printf("}\n");
}
