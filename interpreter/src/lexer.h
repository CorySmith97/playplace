#pragma once
#include "../../core/core.h"

// Based off monkey lang. The toy language of Thorston Ball. Read the book.

typedef enum {
    tok_eof,
    tok_illegal,
    tok_assign,
    tok_plus,
    tok_ident,
    tok_int,
    tok_comma,
    tok_semicolon,
    tok_lparen,
    tok_rparen,
    tok_lbrace,
    tok_rbrace,
    tok_function,
    tok_let,

    // Advance tokens
    tok_eq,
    tok_bang,
    tok_minus,
    tok_asterisk,
    tok_slash,
    tok_lt,
    tok_gt,
} Token_Types;

typedef struct Location {
    usize start, end;
} Location;

typedef struct Token {
    Token_Types tag;
    Location loc;
} Token;

typedef struct ArrayToken {
    Token* data;
    u32 len;
    u32 capacity;
} ArrayToken;

typedef struct Tokenizer {
    const char *file_path;
    String8 input;
    u64 read_pos;
} Tokenizer;

Tokenizer tokenizer_create(Arena *a, const char *file_path);
Token next_token(Arena *a, Tokenizer *t);

ArrayToken tokenize(Tokenizer *l);
Token_Types ident_lookup(Tokenizer *t, Location l);
