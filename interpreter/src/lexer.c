#include "lexer.h"
#include <stdint.h>


Tokenizer tokenizer_create(Arena *a, const char *file_path) {
    Tokenizer *t = c_arena_alloc(a, sizeof(Tokenizer));

    String8 *s = read_entire_file_as_string8(a, file_path);
    t->input = *s;
    t->file_path = file_path;

    return *t;
}

static u8 read_char(Tokenizer *t) {
    u8 return_val;
    if (t->read_pos >= t->input.len) {
        return UINT32_MAX;
    }
    return_val = t->input.data[t->read_pos];

    t->read_pos += 1;
    return return_val;
}

Token next_token(Arena *a, Tokenizer *t) {
    Token *tok = (Token*)c_arena_alloc(a, sizeof(Token));

    u8 current_char = t->input.data[t->read_pos];
    switch (current_char) {
        case '=': {
            tok->tag = tok_assign;
            tok->loc = (Location){.start = t->read_pos, .end = t->read_pos + 1};
        } break;
        case '+': {
            tok->tag = tok_plus;
            tok->loc = (Location){.start = t->read_pos, .end = t->read_pos + 1};
        } break;
        case ',': {
            tok->tag = tok_comma;
            tok->loc = (Location){.start = t->read_pos, .end = t->read_pos + 1};
        } break;
        case ';': {
            tok->tag = tok_semicolon;
            tok->loc = (Location){.start = t->read_pos, .end = t->read_pos + 1};
        } break;
        case '(': {
            tok->tag = tok_lparen;
            tok->loc = (Location){.start = t->read_pos, .end = t->read_pos + 1};
        } break;
        case ')': {
            tok->tag = tok_rparen;
            tok->loc = (Location){.start = t->read_pos, .end = t->read_pos + 1};
        } break;
        case '{': {
            tok->tag = tok_lbrace;
            tok->loc = (Location){.start = t->read_pos, .end = t->read_pos + 1};
        } break;
        case '}': {
            tok->tag = tok_rbrace;
            tok->loc = (Location){.start = t->read_pos, .end = t->read_pos + 1};
        } break;
        case 0: {
            LOG(debug, "Hitting the case 0");
            tok->tag = tok_eof;
            tok->loc = (Location){.start = t->read_pos, .end = t->read_pos + 1};
        } break;
    }

    read_char(t);
    return *tok;
}

static void eat_whitespace(Tokenizer *t) {
}

static u8 peek_char(Tokenizer *t) {
    if (t->read_pos + 1 < t->input.len) {
        return t->input.data[t->read_pos + 1];
    }

    return 0;
}
