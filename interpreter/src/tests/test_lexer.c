#include "../../../core/core.h"
#include "../lexer.h"

typedef struct Token_Expect {
    Token_Types tag;
    union {
        char *literal;
        i32 number;
    } data;
} Token_Expect;

void test_ident_lookup() {
    Arena a;
    c_arena_init(&a, GB(1));

    Tokenizer t = tokenizer_create(&a, "src/tests/test_lexer.txt");

    Token tok = next_token(&a, &t);
    LOG(info, "tok: %d", tok.tag);
    assert(tok.tag == tok_let, "Let token test");
    tok = next_token(&a, &t);
    assert(tok.tag == tok_ident, "Ident token test");
    tok = next_token(&a, &t);
    assert(tok.tag == tok_assign, "Ident token test");
}

void test_next_token() {
    Arena a;
    c_arena_init(&a, GB(1));

    Token_Expect expected_results[] = {
      (Token_Expect){tok_let},
      (Token_Expect){tok_ident, "five"},
      (Token_Expect){tok_assign},
      (Token_Expect){tok_int, .data = {.number = 5}},
      (Token_Expect){tok_semicolon},
      (Token_Expect){tok_let},
      (Token_Expect){tok_ident, "ten"},
      (Token_Expect){tok_assign},
      (Token_Expect){tok_int, .data = {.number = 10}},
      (Token_Expect){tok_semicolon},
      (Token_Expect){tok_let},
      (Token_Expect){tok_ident, "add"},
      (Token_Expect){tok_assign},
      (Token_Expect){tok_function},
      (Token_Expect){tok_lparen},
      (Token_Expect){tok_ident, "x"},
      (Token_Expect){tok_comma},
      (Token_Expect){tok_ident, "y"},
      (Token_Expect){tok_rparen},
      (Token_Expect){tok_lbrace},
      (Token_Expect){tok_ident, "x"},
      (Token_Expect){tok_plus},
      (Token_Expect){tok_ident, "y"},
      (Token_Expect){tok_semicolon},
      (Token_Expect){tok_rbrace},
      (Token_Expect){tok_semicolon},
      (Token_Expect){tok_let},
      (Token_Expect){tok_ident, "result"},
      (Token_Expect){tok_assign},
      (Token_Expect){tok_ident, "add"},
      (Token_Expect){tok_lparen},
      (Token_Expect){tok_ident, "five"},
      (Token_Expect){tok_comma},
      (Token_Expect){tok_ident, "ten"},
      (Token_Expect){tok_rparen},
      (Token_Expect){tok_semicolon},
      (Token_Expect){tok_eof},
    };
    Tokenizer t = tokenizer_create(&a, "src/tests/test_lexer.txt");

    bool quit = false;
    int counter = 0;
    while (!quit) {
        Token tok = next_token(&a, &t);
        LOG(info, "Interation: %d, \n\tToken: %c..%c\n\tToken: %d Expected: %d.", counter, t.input.data[tok.loc.start], t.input.data[tok.loc.end], tok.tag, expected_results[counter].tag);
        assert(tok.tag == expected_results[counter].tag, "Token Compare");
        if (tok.tag == tok_eof) {
            quit = true;
        }
        counter += 1;
    }
}

int main() {
    test_ident_lookup();
    test_next_token();
}
