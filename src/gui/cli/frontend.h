#ifndef FRONTEND_H
#define FRONTEND_H

#include "../../brick_game/tetris/main.h"
// #include "../../brick_game/tetris/defines.h"

void print_overlay(void);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_stats(GameInfo_t *stats);
void print_field();
void print_board(board_t map);
void print_gameover(GameInfo_t *stats);
void print_tetramino(tetramino_t tetramino);
void clear_tetramino(tetramino_t tetramino);

void print_next_tetr(tetramino_t tetramino);
void print_pause();
void clear_pause();
void update_time(int hours, int minutes);
#endif