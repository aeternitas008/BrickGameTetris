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

// For ubuntu need to realise clock_gettime
// #define _POSIX_C_SOURCE 199309L
//  #define CLOCK_REALTIME 0
// int clock_gettime(int clk_id, struct timespec *tp) {
//   struct timeval now;
//   int rv = gettimeofday(&now, NULL);
//   if (rv == 0) {
//     tp->tv_sec = now.tv_sec;
//     tp->tv_nsec =
//         now.tv_usec * 1000;  // Конвертируем микросекунды в наносекунды
//   }
//   return rv;
// }

#endif