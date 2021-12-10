#include <stdio.h>

#include "../test.h"
#include "set.h"

int main()
{
    const size_t size = 10;
    set_t set;
    set_make(&set, size);

    ASSERT(!set_contains(&set, 0), "0 should not be in the set");
    ASSERT(set.size == size, "new set should have a size");
    ASSERT(set.elements == 0, "new set should be empty");

    set_add(&set, 1);
    ASSERT(set_contains(&set, 1), "1 should be in the set");
    ASSERT(set.elements == 1, "set element count should be updated");

    set_add(&set, 2);
    ASSERT(set_contains(&set, 2), "2 should be in the set");

    set_add(&set, 11);
    ASSERT(set_contains(&set, 11), "11 should be in the set");

    set_print(&set);
    
    set_remove(&set, 1);
    ASSERT(!set_contains(&set, 1), "1 should not be in the set");
    ASSERT(set.elements == 2, "set element count should be updated");

    set_remove(&set, 11);
    ASSERT(!set_contains(&set, 11), "11 should not be in the set");

    set_print(&set);

    set_free(&set);
}
