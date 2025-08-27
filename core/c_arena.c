//
// Created by Cory Smith on 7/25/25.
//
#include "core.h"
#include <stdlib.h>
#include <string.h>


Arena c_arena_alloc_init(
    usize size
) {
    return (Arena){.data = malloc(size), .size = size, .current = 0};
}

void c_arena_init(Arena *arena, usize size) {
    arena->size = size;
    arena->current = 0;
    arena->data = malloc(size);
}

void *c_arena_alloc(
    Arena *arena,
    usize size
) {
    if (arena->current + size > arena->size) {
        return NULL;
    }
    void *ptr = arena->data + arena->current;
    arena->current += size;
    return ptr;
}

void c_arena_reset(
    Arena *arena
) {
    arena->current = 0;
}

void c_arena_deinit(
    Arena *arena
) {
    free(arena->data);
}

void *c_arena_array_concat(
    Arena *arena,
    const void *a1, usize s1,
    const void *a2, usize s2
) {
    void *ret = c_arena_alloc(arena, (usize)s1 + s2);
    memcpy(ret, a1, s1);
    memcpy(ret + s1, a2, s2);

    return ret;
}


char **c_arena_string_array_concat(
    Arena *arena,
    const char **a1, usize s1,
    const char **a2, usize s2
) {
    usize total = s1 + s2;
    char **ret = c_arena_alloc(arena, total * sizeof(char*));
    if (!ret) return NULL;

    // Copy pointers from first array
    memcpy(ret, a1, s1 * sizeof(char*));
    // Copy pointers from second array
    memcpy(ret + s1, a2, s2 * sizeof(char*));

    return ret;
}
