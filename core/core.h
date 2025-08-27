//
// Created by Cory Smith on 7/25/25.
//

#ifndef CORE_H
#define CORE_H

#define POSIX

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;
typedef size_t usize;

#define MB(s) ((s) * 1024)
#define GB(s) ((s) * 1024 * 1024)

#define panic(fmt) \
    do {    \
    fprintf(stderr, "Panic at %s:%d\n\tMessage: %s\n\n", __FILE__, __LINE__, fmt); \
    exit(1); \
    }while (0)

// ARENA
// @todo:cs This needs to have alignment stuff accounted for. I keep ignoring it because I'm a lazy bear.
typedef struct Arena {
    void* data;
    u64 size;
    u64 current;
} Arena;

extern Arena c_arena_alloc_init(usize size);
extern void  c_arena_init(Arena *arena, usize size);
extern void *c_arena_alloc(Arena *arena, usize size);
extern void  c_arena_reset(Arena *arena);
extern void  c_arena_deinit(Arena *arena);
extern void *c_arena_array_concat(Arena *arena, const void *a1, usize s1, const void *a2, usize s2);
extern char **c_arena_string_array_concat(Arena *arena, const char **a1, usize s1, const char **a2, usize s2);

// STRINGS

// char string with known length
typedef struct String8 String8;
struct String8 {
    u8 *data;
    u64 len;
};


String8 *c_string8_create(Arena *arena);
void     c_string8_destroy(String8 *string);

// MATH

typedef struct Vec2 {
    f32 x, y;
} Vec2;
typedef struct Vec3 {
    f32 x, y, z;
} Vec3;
typedef struct Vec4 {
    f32 x, y, z, w;
} Vec4;
typedef struct Mat4 {
    f32 m[16];
} Mat4;

extern Vec2 c_vec2_add(Vec2 a, Vec2 b);
extern Vec2 c_vec2_sub(Vec2 a, Vec2 b);
extern Vec2 c_vec2_scale(Vec2 a, f32 scale);
extern f32  c_vec2_dot(Vec2 a, Vec2 b);

extern Vec3 c_vec3_add(Vec3 a, Vec3 b);
extern Vec3 c_vec3_sub(Vec3 a, Vec3 b);
extern Vec3 c_vec3_scale(Vec3 a, f32 scale);
extern f32  c_vec3_dot(Vec3 a, Vec3 b);
extern Vec3 c_vec3_cross(Vec3 a, Vec3 b);

extern Vec4 c_vec4_add(Vec4 a, Vec4 b);
extern Vec4 c_vec4_sub(Vec4 a, Vec4 b);
extern Vec4 c_vec4_scale(Vec4 a, f32 scale);
extern f32  c_vec4_dot(Vec4 a, Vec4 b);
extern Vec4 c_vec4_cross(Vec4 a, Vec4 b);

extern Mat4 c_mat4_mul(Mat4 a, Mat4 b);
extern Mat4 c_mat4_inv(Mat4 a);
extern Mat4 c_mat4_mul_inv(Mat4 a, Mat4 b);
extern Mat4 c_mat4_inv_inv(Mat4 a, Mat4 b);
extern Mat4 c_mat4_transpose(Mat4 a);
extern Mat4 c_mat4_transpose_inv(Mat4 a);
extern Mat4 c_mat4_look_at(Vec3 eye, Vec3 at, Vec3 up);
extern Mat4 c_mat4_ortho(Vec3 min, Vec3 max);
extern Mat4 c_mat4_identity();


// ARRAYLISTS

typedef struct ArrayI32 ArrayI32;
typedef struct ArrayF32 ArrayF32;
typedef struct ArrayVec2 ArrayVec2;
typedef struct ArrayVec3 ArrayVec3;
typedef struct ArrayVec4 ArrayVec4;

typedef struct ArrayString {
    const char** data;
    u32 len;
    u32 capacity;
} ArrayString;

extern ArrayString *c_array_string_create(Arena*, u32);
extern void         c_array_string_push(Arena*, ArrayString*, const char*);

// LOGGING

#define LOG_LEVEL_GEN(ENUM) ENUM,
#define LOG_STRING_GEN(STRING) #STRING,

#define FOREACH_LOG_LEVEL(LOG_LEVEL) \
    LOG_LEVEL(warn)                  \
    LOG_LEVEL(info)                  \
    LOG_LEVEL(error)                 \
    LOG_LEVEL(debug)

#define FOREACH_LOG_LEVEL_COLOR(LOG_LEVEL)\
    LOG_LEVEL(\e[35m)                  \
    LOG_LEVEL(\e[36m)                  \
    LOG_LEVEL(\e[31m)                  \
    LOG_LEVEL(\e[33m)

enum LogLevel {
    FOREACH_LOG_LEVEL(LOG_LEVEL_GEN)
};

static const char* log_level_str[] = {
    FOREACH_LOG_LEVEL(LOG_STRING_GEN)
};

static const char* log_color_str[] = {
    FOREACH_LOG_LEVEL_COLOR(LOG_STRING_GEN)
};

#ifdef POSIX
    #define LOG(_LEVEL, _STR, ...) (printf("%s[%s]\e[0m " _STR "\n", log_color_str[_LEVEL], log_level_str[_LEVEL],  ##__VA_ARGS__))
#else
    #define LOG(_LEVEL, _STR, ...) (printf("[%s] " _STR "\n",  log_level_str[_LEVEL],  ##__VA_ARGS__))
#endif

typedef struct Hashmap {
    void *data;
    u64 data_size;
    String8 *keys;
    u64 keys_len;
} Hashmap;

extern Hashmap *hashmap_create(Arena *arena);
extern void     hashmap_free(Hashmap *map);
extern void     hashmap_set(Hashmap *map, String8 key, void *value);
extern void    *hashmap_get(Hashmap *map, String8 key);
extern void     hashmap_remove(Hashmap *map, String8 key);

// FILES

extern String8 *read_entire_file_as_string8(Arena *a, const char *file_path);

// TEST

// Detect leaks. Note allocations.
typedef struct Testing_Allocator {
    Arena a;
} Testing_Allocator;

// Global testing allocator
static Testing_Allocator Test = {
    //.a = {
    //    .data = (void*)[GB(1)],
    //}
};

#define assert(expr, test_name) do {                      \
  if ( ! (expr) ){                             \
  fprintf(stderr, "[TEST] %s\nAssertion failed: %s(): %d: \n", test_name, __FILE__, __LINE__);                 \
    abort();                                   \
  } else {LOG(info, "[TEST] %s: PASS\n", test_name);}} while ( 0 );


#endif //CORE_H
