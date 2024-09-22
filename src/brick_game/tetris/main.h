#ifndef MAIN_H
#define MAIN_H

#include <ncurses.h>

#include "defines.h"

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  Position *point;
  int type;
  int variant;
  unsigned int figure[4][4];
  unsigned int array_figures[19][4][4];
} Tetramino_t;

typedef struct {
  int field[ROWS_MAP][COLS_MAP];
} Board_t;

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
  GAMEOVER,
  EXIT_STATE
} State_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct GameParams {
  GameInfo_t *stats;
  State_t *state;
  Board_t *map;
  struct timespec *time;
  Tetramino_t *tetramino;
  int sig;
  int hold;
} Params_t;

// For ubuntu if need to realise clock_gettime
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