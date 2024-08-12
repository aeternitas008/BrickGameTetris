CC := gcc
CFLAGS := -I inc -std=c99 -Wall -Werror -Wpedantic
# OBJS_FSMSWITCHCASE := out/frogger.o out/fsm.o out/backend.o out/frontend.o
OBJS_FSMTABLE := out/tetris.o out/fsm_matrix.o out/backend.o out/frontend.o

tetris: $(OBJS_FSMTABLE)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

tetris_fsmtable: $(OBJS_FSMTABLE)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

out/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) out/*.o tetris tetris_fsmtable

cl_fri:
	@clang-format -i -style=google */*.c */*.h

cl_fr:
	clang-format -n -style=google */*.c */*.h