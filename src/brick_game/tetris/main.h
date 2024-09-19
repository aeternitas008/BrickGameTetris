#ifndef MAIN_H
#define MAIN_H

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
} board_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  FELL,
  GAMEOVER,
  EXIT_STATE
} state_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct game_params {
  GameInfo_t *stats;
  state_t *state;
  board_t *map;
  struct timespec *time;
  tetramino_t *tetramino;
  int sig;
  int hold;
} params_t;

#endif