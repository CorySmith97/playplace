#include "core.h"
#include <string.h>

void c_array_string_push(
    Arena *a,
    ArrayString* as,
    const char* str
) {
    LOG(debug, "string: %s", str);
    if (as->len + 1 < as->capacity) {
        as->data[as->len] = str;
        LOG(debug, "in data: %s", as->data[as->len]);
        as->len++;
        return;
    }
    u64 new_cap = as->capacity ? as->capacity * 2 : 1;
    const char **tmp = (const char **)c_arena_alloc(a, new_cap);

    memcpy(tmp, as->data, as->len * sizeof(*as->data));
    tmp[as->len] = str;
    as->data = tmp;
    as->capacity = new_cap;
    as->len++;
}

ArrayString* c_array_string_create(
    Arena *a,
    u32 inital_size
) {
    ArrayString *as = c_arena_alloc(a, sizeof(ArrayString *));
    as->data = (const char **)c_arena_alloc(a, inital_size * sizeof(const char*));
    as->len = 0;
    as->capacity = inital_size;

    return as;
}
