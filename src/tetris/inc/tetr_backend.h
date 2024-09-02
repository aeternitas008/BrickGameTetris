#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

#include <ncurses.h>
#include <string.h>

#include "defines.h"
#include "fsm.h"
#include "objects.h"
// #include "string.h"

#include <time.h>
// #include "tetr_frontend.h"

#define NOSIG 8

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


typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
  char current_time[8];
} GameInfo_t;

typedef struct game_params {
  GameInfo_t *stats;
  state_t *state;
  board_t *map;
  bool *break_flag;
  struct timespec *time;
  tetramino_t *tetramino;
  int hold;
} params_t;

// typedef struct {
//   int score;
//   int high_score;
//   int level;
//   int speed;
//   char current_time[8];
// } game_stats_t;


UserAction_t get_signal(int user_input);
void sigact(UserAction_t sig, params_t *prms);

void add_tetramino_on_board(params_t *prms);

// int lvlproc(board_t *map, game_stats_t *stats);
void add_proggress(board_t *map);
void stats_init(GameInfo_t *stats);

void new_stats_init(GameInfo_t *stats);

void tetraminopos_init(position *tetramino_pos);
void fill_finish(char *finish_line);
void shift_map(board_t *map);
void init_board(board_t *map);

bool check_collide(position *tetramino_pos, board_t *map);
bool check_finish_state(position *tetramino_pos, board_t *map);
bool check_level_compl(board_t *map);

int check_new_variant(params_t prms);
int check_tetramino(params_t prms, tetramino_t tetramino);
void get_array_figures(unsigned int origin[19][4][4]);

void userInput(UserAction_t action, bool hold);
#endif