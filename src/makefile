CC := gcc
CFLAGS := -I inc -std=c99 -Wall -Werror -Wpedantic
# OBJS_FSMSWITCHCASE := out/frogger.o out/fsm.o out/backend.o out/frontend.o
OBJS_FSMTABLE := out/tetris.o out/backend.o out/frontend.o

tetris: $(OBJS_FSMTABLE)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

tetris_fsmtable: $(OBJS_FSMTABLE)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

out/tetris.o: brick_game/tetris/tetris.c
	$(CC) $(CFLAGS) -c $< -o $@

out/backend.o: brick_game/tetris/backend.c
	$(CC) $(CFLAGS) -c $< -o $@

out/frontend.o: gui/cli/frontend.c
	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	$(RM) out/*.o tetris tetris_fsmtable

cl_fri:
	@clang-format -i -style=google */*.c */*.h

cl_fr:
	clang-format -n -style=google */*.c */*.h

# # Запуск тестов
# test: $(TEST_TARGET)
# 	./$(TEST_TARGET)

# # Генерация отчёта покрытия кода
# coverage: test
# 	gcov $(SRCS) $(TEST_SRCS)
# 	lcov --capture --directory . --output-file coverage.info
# 	genhtml coverage.info --output-directory out

# Правила для сборки и запуска тестов
test: out/test.o $(OBJS_FSMTABLE)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	./test

# Компиляция тестов
out/test.o: test.c
	$(CC) $(CFLAGS) -c $< -o $@

# Генерация отчёта покрытия кода
coverage: test
	gcov $(OBJS_FSMTABLE:.o=.c) test.c
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out

# Очистка сгенерированных файлов
clean:
	$(RM) out/*.o tetris tetris_fsmtable test *.gcda *.gcno *.gcov coverage.info
	# rm -rf out

# test: test.c
# 	$(CC) $(CFLAGS) $^ -o $@ -lncurses
