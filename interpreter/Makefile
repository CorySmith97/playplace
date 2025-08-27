CC:=clang

MAIN_SRC=src/main.c
INTER_SRC=src/lexer.c
CORE_SRC:=../core/c_main.c

BUILD_DIR:=bin
C_FLAGS=-g -Wall -Wextra -Wno-unused-parameter -Wno-return-type

INTER_LINK=-L./bin/ -lcore

core:
	$(CC) $(C_FLAGS) -o $(BUILD_DIR)/libcore.dylib -fPIC -shared $(CORE_SRC)

all:
	clang -o bin/app $(MAIN_SRC) $(INTER_SRC) $(INTER_LINK)

test_lex:
	clang -o bin/test_lex $(INTER_SRC) src/tests/test_lexer.c $(INTER_LINK)
