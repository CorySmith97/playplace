//
// Created by Cory Smith on 8/3/25.
//

#include "core.h"
#include <stdlib.h>

#define FNV_PRIME 16777619

u64 internal_hash(
    String8 *str
) {
    u64 hash = UINT64_MAX;
    for (u64 i = 0; i < str->len; i++) {
        hash *= FNV_PRIME;
        hash ^= str->data[i];
    }
}

Hashmap *hashmap_create(
    Arena *arena,
    u64 expected_max
) {
    Hashmap *map = c_arena_alloc(arena, sizeof(Hashmap));
    map->keys = NULL;
    map->keys_len = 0;
    map->data = c_arena_alloc(arena, sizeof(u64) * expected_max * 1.33);

    return map;
}

void hashmap_free(
    Hashmap *map
) {}

void hashmap_set(
    Hashmap *map,
    String8 key,
    void *value
) {}

void *hashmap_get(
    Hashmap *map,
    String8 *key
) {}

void hashmap_remove(
    Hashmap *map,
    String8 *key
) {}
