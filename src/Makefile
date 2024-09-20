CC = gcc
FLAG_C = -c
FLAG_ER = -Wall -Werror -Wextra -std=c11
TET_LIB_C = ./brick_game/tetris/backend.c
FRONTEND_C = ./gui/cli/frontend.c
MAIN_C = ./brick_game/tetris/main.c
TET_LIB_O = brick_game/tetris/backend.o
FRONTEND_O = gui/cli/frontend.o
FLAG_TEST = -lcheck -lm  -I/opt/homebrew/include

all: clean uninstall tetris

tetris: tetris_lib.a $(FRONTEND_O) $(MAIN_C)
	$(CC) $(FLAG_ER) -o tetris $(MAIN_C) $(FRONTEND_O) tetris_lib.a -lncurses

install: tetris
	mkdir ./game
	cp tetris ./game

uninstall:
	-rm -rf ./game

tetris_lib.a: $(TET_LIB_O) $(FRONTEND_O)
	ar rc tetris_lib.a $(TET_LIB_O) $(FRONTEND_O)
	ranlib tetris_lib.a

$(TET_LIB_O): $(TET_LIB_C)
	$(CC) $(FLAG_C) $(FLAG_ER) $(TET_LIB_C) -o $(TET_LIB_O)

$(FRONTEND_O): $(FRONTEND_C)
	$(CC) $(FLAG_C) $(FLAG_ER) $(FRONTEND_C) -o $(FRONTEND_O)

clean: uninstall
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg
	-rm -f test tests greport Doxyfile tetris.install.tar.gz
	-rm -rf report test.d*
	find . -name "*.o" -type f -delete


test: clean tetris_lib.a
	$(CC) -g --coverage $(FLAG_ER) test.c -o test tetris_lib.a -lncurses $(FLAG_TEST)
	./test

gcov_report: test
	$(CC) --coverage $(TET_LIB_C) $(FRONTEND_C) test.c -o greport $(FLAG_TEST) -lncurses
	./greport
	lcov -t "test" -o tetris.info --no-external -c -d .
	genhtml -o ./report tetris.info
	open ./report/index.html

dist:
	tar -czf tetris.install.tar.gz ./*

dvi:
	doxygen -g

style:
	find .. -name "*.c" -exec clang-format -i -style=google {} \;
	find .. -name "*.h" -exec clang-format -i -style=google {} \;

style_test:
	cp ../materials/linters/.clang-format .
	find .. -name "*.c" -exec clang-format -n -style=google {} \;
	find .. -name "*.h" -exec clang-format -n -style=google {} \;
	rm -rf .clang-format

