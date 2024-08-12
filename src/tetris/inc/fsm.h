#ifndef FSM_H
#define FSM_H

#include <time.h>

#include "defines.h"
#include "objects.h"
#include "tetr_backend.h"
#include "tetr_frontend.h"

typedef enum {
  // MAIN = 0,
  START = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  REACH,
  FELL,
  GAMEOVER,
  EXIT_STATE
} state_t;

typedef enum {
  MOVE_UP = 0,
  MOVE_DOWN,
  MOVE_RIGHT,
  MOVE_LEFT,
  ESCAPE_BTN,
  ENTER_BTN,
  NOSIG,
  SPACE_BTN,
  P_BTN,
  R_BTN
} signals;

typedef struct game_params {
  game_stats_t *stats;
  state_t *state;
  board_t *map;
  bool *break_flag;
  struct timespec *time;
  tetramino_t *tetramino;
} params_t;

signals get_signal(int user_input);
void sigact(signals sig, state_t *state, game_stats_t *stats, board_t *map,
            tetramino_t *tetramino, struct timespec *time);
#endif