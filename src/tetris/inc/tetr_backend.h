#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

#include <ncurses.h>

#include "defines.h"
#include "fsm.h"
#include "objects.h"
// #include "string.h"

int lvlproc(board_t *map, game_stats_t *stats);
void add_proggress(board_t *map);
void stats_init(game_stats_t *stats);

void new_stats_init(game_stats_t *stats);

void tetraminopos_init(position *tetramino_pos);
void fill_finish(char *finish_line);
void shift_map(board_t *map);
void init_board(board_t *map);

bool check_collide(position *tetramino_pos, board_t *map);
bool check_finish_state(position *tetramino_pos, board_t *map);
bool check_level_compl(board_t *map);

#endif