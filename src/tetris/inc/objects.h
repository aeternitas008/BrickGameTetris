#ifndef OBJECTS_H
#define OBJECTS_H

#include <ncurses.h>

#include "defines.h"

typedef struct {
  int x;
  int y;
} position;

typedef struct {
  position *point;
  int type;
  int variant;
  unsigned int figure[4][4];
  unsigned int array_figures[19][4][4];
} tetramino_t;

typedef struct {
  int field[ROWS_MAP][COLS_MAP];
  tetramino_t *tetramino;
} board_t;

// typedef struct {
//   int score;
//   int high_score;
//   int level;
//   int speed;
//   int fell;
//   int won;
//   char current_time[8];
// } game_stats_t;


// typedef struct {
//     int **field;
//     int **next;
//     int score;
//     int high_score;
//     int level;
//     int speed;
//     int pause;
//   char current_time[8];
// } GameInfo_t;

typedef struct {
  char matrix[BANNER_N + 1][BANNER_M + 1];
} banner_t;

#endif