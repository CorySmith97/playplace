#include "core.h"

#include <stdio.h>

String8 *read_entire_file_as_string8(Arena *a, const char *file_path) {
    String8 *s = c_arena_alloc(a, sizeof(String8));

    FILE *f = fopen(file_path, "r");
    fseek(f, 0L, SEEK_END);
    int size = ftell(f);
    fseek(f, 0L, SEEK_SET);
    s->data = c_arena_alloc(a, size + 1);
    s->len = size + 1;
    fread(s->data, sizeof(u8), size, f);

    s->data[size] = '\0';
    return s;
}
