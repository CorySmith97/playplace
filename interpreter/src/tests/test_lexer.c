#include "../../../core/core.h"
#include "../lexer.h"
#include <string.h>
#include <stdio.h>

void test_next_token() {
    Arena a;
    c_arena_init(&a, GB(1));

    Token expected_results[9] = {
      (Token){.tag = tok_assign, .loc = {.start = 0, .end = 1}},
      (Token){.tag = tok_plus, .loc = {.start = 1, .end = 2}},
      (Token){.tag = tok_lparen, .loc = {.start = 2, .end = 3}},
      (Token){.tag = tok_rparen, .loc = {.start = 3, .end = 4}},
      (Token){.tag = tok_lbrace, .loc = {.start = 4, .end = 5}},
      (Token){.tag = tok_rbrace, .loc = {.start = 5, .end = 6}},
      (Token){.tag = tok_comma, .loc = {.start = 6, .end = 7}},
      (Token){.tag = tok_semicolon, .loc = {.start = 7, .end = 8}},
      (Token){.tag = tok_eof, .loc = {.start = 8, .end = 9}},
    };
    Tokenizer t = tokenizer_create(&a, "src/tests/test_lexer.txt");
    printf("Input String: %s\nLength of string: %llu\n", t.input.data, t.input.len);

    bool quit = false;
    int counter = 0;
    while (!quit) {
        Token tok = next_token(&a, &t);
        //LOG(info, "Interation: %d, Read pos %d\n\tToken: %d. Expected: %d. Char: %c", counter, t.read_pos, tok.tag, expected_results[counter].tag, t.input.data[t.read_pos]);
        assert(tok.tag == expected_results[counter].tag, "Token Compare");
        if (tok.tag == tok_eof) {
            quit = true;
        }
        counter += 1;
    }
}

int main() {
    test_next_token();
}
