#include <stdio.h>
#include "../../core/core.h"

int main() {
    Arena a = c_arena_alloc_init(GB(1));

    String8 *s = read_entire_file_as_string8(&a, "src/test.txt");

    printf("Hello from the interpreter: size of file: %llu,  %s\n", s->len, s->data);
}
