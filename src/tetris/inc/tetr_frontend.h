#ifndef TETRIS_FRONTEND_H
#define TETRIS_FRONTEND_H

#include <string.h>

#include "defines.h"
#include "fsm.h"
#include "objects.h"

void print_overlay(void);
void print_levelerror(void);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_stats(game_stats_t *stats);
void print_field();
void print_board(board_t *game);
void print_cars(board_t *game);
void print_finished(board_t *game);
void print_banner(game_stats_t *stats);
int read_banner(game_stats_t *stats, banner_t *banner);
void print_tetramino(tetramino_t tetramino);
void clear_tetramino(tetramino_t tetramino);

#endif