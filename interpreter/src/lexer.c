#include "lexer.h"
#include <stdint.h>


static void eat_whitespace(Tokenizer *t);
static Location read_idenitifer(Tokenizer *t);
static bool is_digit(u8 ch);
static bool is_letter(u8 ch);
static Location read_number(Tokenizer *t);
static u8 peek_char(Tokenizer *t);

typedef enum {
    ident_function,
    ident_let,
} Ident_Types;

String8 ident_lookup_table[] = {
    (String8){.data = (u8*)"let", 3},
    (String8){.data = (u8*)"fn", 2},
};

Token_Types ident_lookup(Tokenizer *t, Location l) {
    u8 current_char = t->input.data[l.start];
    switch(current_char) {
        case 'f': {
            if (t->input.data[l.end] == 'n') {
                return tok_function;
            }
        } break;
        case 'l': {
            bool is_let = false;
            String8 let = ident_lookup_table[ident_let];
            for (int i = 0; i < l.end - l.start; i++) {
                is_let = let.data[i] == t->input.data[l.start + i];
            }
            if (is_let) return tok_let;
        }
    }

    return tok_illegal;
}

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

    eat_whitespace(t);

    u8 current_char = t->input.data[t->read_pos];
    switch (current_char) {
        case '=': {
            if (peek_char(t) == '=') {
                tok->tag = tok_assign;
                tok->loc = (Location){t->read_pos, t->read_pos + 1};
                read_char(t);
            } else {
                tok->tag = tok_assign;
                tok->loc = (Location){.start = t->read_pos};
            }
        } break;
        case '+': {
            tok->tag = tok_plus;
            tok->loc = (Location){.start = t->read_pos};
        } break;
        case ',': {
            tok->tag = tok_comma;
            tok->loc = (Location){.start = t->read_pos};
        } break;
        case ';': {
            tok->tag = tok_semicolon;
            tok->loc = (Location){.start = t->read_pos};
        } break;
        case '(': {
            tok->tag = tok_lparen;
            tok->loc = (Location){.start = t->read_pos};
        } break;
        case ')': {
            tok->tag = tok_rparen;
            tok->loc = (Location){.start = t->read_pos};
        } break;
        case '{': {
            tok->tag = tok_lbrace;
            tok->loc = (Location){.start = t->read_pos};
        } break;
        case '}': {
            tok->tag = tok_rbrace;
            tok->loc = (Location){.start = t->read_pos};
        } break;
        case '!': {
            tok->tag = tok_bang;
            tok->loc = (Location){.start = t->read_pos};
        } break;
        case '-': {
            tok->tag = tok_minus;
            tok->loc = (Location){.start = t->read_pos};
        } break;
        case '*': {
            tok->tag = tok_asterisk;
            tok->loc = (Location){.start = t->read_pos};
        } break;
        case '/': {
            tok->tag = tok_slash;
            tok->loc = (Location){.start = t->read_pos};
        } break;
        case '<': {
            tok->tag = tok_lt;
            tok->loc = (Location){.start = t->read_pos};
        } break;
        case '>': {
            tok->tag = tok_gt;
            tok->loc = (Location){.start = t->read_pos};
        } break;
        case 0: {
            tok->tag = tok_eof;
            tok->loc = (Location){.start = t->read_pos};
        } break;
        default: {
            if (is_letter(current_char)) {
                tok->loc = read_idenitifer(t);
                tok->tag = ident_lookup(t, tok->loc);
            } else if (is_digit(current_char)){

            } else {
                tok->tag = tok_illegal;
            }
        } break;
    }

    read_char(t);
    return *tok;
}

static void eat_whitespace(Tokenizer *t) {
    u8 current_char = t->input.data[t->read_pos];
    while (current_char == '\n' || current_char == ' '|| current_char == '\r'|| current_char == '\t') {
        read_char(t);
    }
}

static bool is_digit(u8 ch) {
    if ('0' <= ch && ch <= '9') {
        return true;
    }

    return false;
}

static bool is_letter(u8 ch) {
    if ('A' <= ch && ch <= 'Z' || 'a' <= ch && ch <= 'z') {
        return true;
    }

    return false;
}

static u8 peek_char(Tokenizer *t) {
    if (t->read_pos + 1 < t->input.len) {
        return t->input.data[t->read_pos + 1];
    }

    return 0;
}

static Location read_number(Tokenizer *t) {
    u8 start = t->read_pos;
    u8 current_char = t->input.data[t->read_pos];
    while (is_digit(current_char)) {
        read_char(t);
    }
    return (Location){start, t->read_pos};
}

static Location read_idenitifer(Tokenizer *t) {
    u8 start = t->read_pos;
    u8 current_char = t->input.data[t->read_pos];
    while (is_letter(current_char)) {
        read_char(t);
    }
    return (Location){start, t->read_pos};
}
