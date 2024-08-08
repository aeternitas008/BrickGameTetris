#ifndef OBJECTS_H
#define OBJECTS_H

#include <ncurses.h>
#include "defines.h"

typedef struct
{
    int x;
    int y;
} tetramino_pos;

typedef struct
{
    char field[ROWS_MAP][COLS_MAP];
} board_t;

typedef struct
{
    char* figure[4][4];
} tetramino_t;

typedef struct
{
    int score;
    int high_score;
    int level;
    int speed;
    int fell;
    int won;
} game_stats_t;

typedef struct
{
    char matrix[BANNER_N + 1][BANNER_M + 1];
} banner_t;

#endif