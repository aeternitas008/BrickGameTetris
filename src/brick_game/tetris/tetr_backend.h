#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

#include <ncurses.h>
#include <string.h>

#include "defines.h"
#include "objects.h"

#include <time.h>

static const unsigned int TETRAMINO_FIGURES[19][4][4] = {
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
      
      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
      
      {{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}},
      
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}},
      {{0, 0, 0, 1}, {0, 0, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}},
      // L
      {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}},
      {{0, 0, 0, 1}, {0, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
      // J 11
      {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}},
      {{0, 0, 1, 1}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
      {{0, 1, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
      // T 15
      {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
  };

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

UserAction_t get_signal(int user_input);
void sigact(UserAction_t sig);

void add_tetramino_on_board(params_t *prms);
void stats_init(GameInfo_t *stats);

void new_stats_init(GameInfo_t *stats);

void tetraminopos_init(position *tetramino_pos);
void init_board(board_t *map);

bool check_collide(position *tetramino_pos, board_t *map);

int check_new_variant(params_t prms);
int check_tetramino(params_t prms, tetramino_t tetramino);
void get_array_figures(unsigned int origin[19][4][4]);


params_t *getPrmsInstance();

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

void get_tetramino(tetramino_t *tetramino);

void start(params_t *prms);
void spawn(params_t *prms);
void moveup(params_t *prms);
void movedown(params_t *prms);
void moveright(params_t *prms);
void moveleft(params_t *prms);
void shifting(params_t *prms);
// void pause_game(params_t *prms);

void fell(params_t *prms);
void gameover(params_t *prms);
void exitstate(params_t *prms);
void check(params_t *prms);
void turn_right(params_t *prms);
void game_pause(params_t *prms);
#endif