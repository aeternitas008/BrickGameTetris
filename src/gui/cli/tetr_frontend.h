#ifndef TETRIS_FRONTEND_H
#define TETRIS_FRONTEND_H

#include <string.h>

#include "../../brick_game/tetris/defines.h"
#include "../../brick_game/tetris/objects.h"
#include "../../brick_game/tetris/tetr_backend.h"

void print_overlay(void);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_stats(GameInfo_t *stats);
void print_field();
void print_board(board_t map);
void print_finished(board_t *game);
void print_gameover(GameInfo_t *stats);
void print_tetramino(tetramino_t tetramino);
void clear_tetramino(tetramino_t tetramino);

void print_next_tetr(tetramino_t tetramino);

#endif