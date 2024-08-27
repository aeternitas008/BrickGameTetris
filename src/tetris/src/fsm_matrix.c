#include <sys/time.h>
#include <time.h>

#include "../inc/fsm.h"
#include "../inc/tetris.h"

#include <math.h>
// #define _POSIX_C_SOURCE 199309L
#define CLOCK_REALTIME 0
// This is a finite state machine realisation based on matrix of "actions".
/*
    Function sigact() takes an action function from fsm_table.
    Game state defines an index of line in matrix (where to get).
    User signal defines an index of column in matrix (what to get).

    Pros:
        1) By instantly taking needed action, speed of processing is higher than
   switch-case realisation. 2) Code is easy to read. 3) Flexible (easy to add
   new state) Cons: 1) More memory usage.
*/

// struct timespec {
//     time_t tv_sec;  /* seconds */
//     long   tv_nsec; /* nanoseconds */
// };

int clock_gettime(int clk_id, struct timespec *tp) {
  struct timeval now;
  int rv = gettimeofday(&now, NULL);

  if (rv == 0) {
    tp->tv_sec = now.tv_sec;
    tp->tv_nsec =
        now.tv_usec * 1000;  // Конвертируем микросекунды в наносекунды
  }
  return rv;
}

typedef void (*action)(params_t *prms);

void start(params_t *prms);
void spawn(params_t *prms);
void moveup(params_t *prms);
void movedown(params_t *prms);
void moveright(params_t *prms);
void moveleft(params_t *prms);
void shifting(params_t *prms);
void reach(params_t *prms);
// void collide(params_t *prms);
void gameover(params_t *prms);
void exitstate(params_t *prms);
void check(params_t *prms);
void turn_right(params_t *prms);
void pause(params_t *prms);

action fsm_table[7][10] = {
    {start, NULL, NULL, NULL, exitstate, start, NULL, NULL},
    {spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn},
    {moveup, movedown, moveright, moveleft, exitstate, check, check, turn_right,
     pause},
    {shifting, shifting, shifting, shifting, shifting, shifting, shifting,
     turn_right, pause},
    {reach, reach, reach, reach, reach, reach, reach},
    // {collide, collide, collide, collide, collide, collide, collide},
    {gameover, gameover, gameover, gameover, gameover, gameover, gameover},
    {exitstate, exitstate, exitstate, exitstate, exitstate, exitstate,
     exitstate}};

// tetramino_t get_tetramino(tetramino_t* matrix_tetram[7][4], int x, int y) {
//   tetramino_t result_tetramino;
//   if (x == 0) fill_tetramino(matrix_tetram[x][]);

//   }
// }

typedef enum {
  // MAIN = 0,
  O = 0,
  I,
  S,
  Z,
  L,
  J,
  T,
} tetramino_state_t;

void print_next_tetramino(params_t *prms) {
  prms->tetramino->type++;
  get_tetramino(prms->tetramino);
  print_next_tetr(*prms->tetramino);
  prms->tetramino->type--;
  get_tetramino(prms->tetramino);
}

void get_next_tetramino(params_t *prms) {
  prms->tetramino->type++;
  get_tetramino(prms->tetramino);
}

// action tetr_matrix[7][4] = {
//   {}
// }

void sigact(signals sig, state_t *state, params_t *prms) {
  action act = NULL;
  // params_t prms;
  // prms.stats = stats;
  // prms.state = state;
  // prms.map = map;
  // prms.tetramino = map->tetramino;
  // prms.time = time;
  // prms.time =
  // if (*state != FILE_ERROR_STATE)
  act = fsm_table[*state][sig];

  if (act) act(prms);
}

signals get_signal(int user_input) {
  signals rc = NOSIG;

  if (user_input == KEY_UP)
    rc = MOVE_UP;
  else if (user_input == KEY_DOWN)
    rc = MOVE_DOWN;
  else if (user_input == KEY_LEFT)
    rc = MOVE_LEFT;
  else if (user_input == KEY_RIGHT)
    rc = MOVE_RIGHT;
  else if (user_input == ESCAPE_KEY)
    rc = ESCAPE_BTN;
  else if (user_input == ENTER_KEY)
    rc = ENTER_BTN;
  else if (user_input == ' ')
    rc = SPACE_BTN;
  else if (user_input == P_KEY_SMALL || user_input == P_KEY)
    rc = P_BTN;
  mvprintw(7, 40, "%03d %03d", user_input, rc);
  return rc;
}

void set_high_score() {}

void save_high_score() {}

int offset(params_t *prms, struct timespec *current_time) {
  int seconds = (current_time->tv_sec - (*prms).time->tv_sec) * 1000 ;
  int nanoseconds =
      (current_time->tv_nsec - (*prms).time->tv_nsec) / 1e6;
  int total_offset = seconds + nanoseconds;
  // MVPRINTW(6, 40, "%d", seconds);
  return total_offset;
}

void shifting(params_t *prms) {
  // shift_map(prms->map);
  int hours = ((long int)prms->time->tv_sec / 3600) % 24 + 3;
  int minutes = (long int)prms->time->tv_sec % 3600 / 60;
  sprintf(prms->stats->current_time, "%02d:%02d", hours, minutes);
  // stats_init(prms->stats);
  // if (check_collide(prms->tetramino_pos, prms->map))
  //     *prms->state = FELL;
  // else
  // {
  struct timespec current_time;
  clock_gettime(CLOCK_REALTIME, &current_time);
  int base_delay = 1000;
  int diff = base_delay*pow(0.9, prms->stats->level - 1);
  // MVPRINTW(30,20, "%d", diff);
  if (offset(prms, &current_time) >= diff) {
    movedown(prms);
    (*prms).time->tv_sec = current_time.tv_sec;
    (*prms).time->tv_nsec = current_time.tv_nsec;
  }

  *prms->state = MOVING;

  // print_board(prms->map, prms->tetramino_pos);
  // print_stats(prms->stats);
  // }

  // MVPRINTW(3, BOARD_M + 8, "OK");
}

int has_full_line(board_t map, int *line) {
  int checker = 0;
  *line = 0;
  for (int x = 0; x < 20 && checker < 10; x++) {
    checker = 0;
    for (int y = 0; y < 10; y++) {
      if (map.field[x][y] == 1) {
        checker += 1;
      }
    }
    if (checker == 10) *line = x;
  }
  return *line;
}

void check_lines(int *count, params_t *prms) {
  int line = 0;
  while (has_full_line(*prms->map, &line)) {
    (*count)++;
    for (int k = line; k > 0; k--) {
      for (int y = 0; y < 10; y++) {
        prms->map->field[k][y] = prms->map->field[k - 1][y];
      }
    }
  }
}

void check(params_t *prms) {
  // if (check_collide(prms->tetramino->point, prms->map))
  //   *prms->state = FELL;
  // else if (check_finish_state(prms->tetramino->point, prms->map))
  //   *prms->state = REACH;
  // else
  int count = 0;
  check_lines(&count, prms);
  if (count == 1) prms->stats->score += 100;
  if (count == 2) prms->stats->score += 300;
  if (count == 3) prms->stats->score += 700;
  if (count == 4) prms->stats->score += 1500;
  if (prms->stats->level < 10)
    prms->stats->level = prms->stats->score / 600 + 1;
  new_stats_init(prms->stats);
  refresh();
  if (*prms->state == SPAWN) {
    *prms->state = SPAWN;
  } else {
    *prms->state = SHIFTING;
  }
}
// void tetramino_fell(tetramino_pos *tetramino_pos) {
//   while (tetramino_pos->x <= 22) {
//     MVPRINTW(tetramino_pos->x++, tetramino_pos->y, " ");
//     PRINT_TETRAMINO(tetramino_pos);
//     refresh();
//   }
// }

void start(params_t *prms) {
  // if (!lvlproc(prms->map, prms->stats))
  // {
  // set_board();
  print_field();
  // MVPRINTW(3, BOARD_M + 8, "OK");
  tetraminopos_init(prms->tetramino->point);
  clock_gettime(CLOCK_REALTIME, prms->time);
  stats_init(prms->stats);
  // print_board(prms->map, prms->tetramino_pos);
  *prms->state = SPAWN;
  // }
}

void spawn(params_t *prms) {
  // if (prms->stats->level > LEVEL_CNT)
  //   *prms->state = GAMEOVER;
  // else {
  tetraminopos_init(prms->tetramino->point);
  prms->tetramino->variant = 0;
  get_tetramino(prms->tetramino);
  print_board(prms->map);
  print_tetramino(*prms->tetramino);
  print_next_tetramino(prms);
  // get_next_tetramino(prms);
  MVPRINTW(8, 33, "%02d", (*prms).tetramino->type);
  int sum = 0;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) { 
      if (prms->map->field[i][j] == 1) {
        sum++;
      }
    }
  }
  MVPRINTW(34, 20, "%d", sum);
  // MVPRINTW(8, 33, "%02d", (*prms).tetramino->type);
  // (*prms).tetramino->type = (prms->tetramino->type + 1) % 7;
  // MVPRINTW(8, 37, "%02d", (*prms).tetramino->type);
  // tetramino_fell(prms->tetramino_pos);
  *prms->state = MOVING;
  // }
}

void moveup(params_t *prms) {
  //
}

bool is_not_block_below(params_t *prms) {
  bool result = 1;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (prms->tetramino->figure[x][y] == 1 &&
          (prms->tetramino->point->x + x >= 19)) {
        result = 0;
      } else if (prms->tetramino->figure[x][y] == 1 &&
                 prms->map->field[prms->tetramino->point->x + x + 1]
                                 [prms->tetramino->point->y + y] == 1)
        result = 0;
    }
  }
  return result;
}

bool is_block_right(params_t *prms) {
  bool result = 1;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (prms->tetramino->figure[x][y] == 1 &&
          (prms->tetramino->point->y + y >= 9 ||
           prms->map->field[prms->tetramino->point->x + x]
                           [prms->tetramino->point->y + y - 1] == 1)) {
        result = 0;
      }
    }
  }
  return result;
}

bool is_block_left(params_t *prms) {
  bool result = 1;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (prms->tetramino->figure[x][y] == 1 &&
          (prms->tetramino->point->y + y <= 0 ||
           prms->map->field[prms->tetramino->point->x + x]
                           [prms->tetramino->point->y + y - 1] == 1)) {
        result = 0;
      }
    }
  }
  return result;
}

void add_tetramino_on_board(params_t *prms) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (prms->tetramino->figure[x][y] == 1) {
        prms->map->field[prms->tetramino->point->x + x]
                        [prms->tetramino->point->y + y] = 1;
      }
    }
  }
}

void movedown(params_t *prms) {
  if (is_not_block_below(prms)) {
    clear_tetramino(*prms->tetramino);
    prms->tetramino->point->x += 1;
    MVPRINTW(9, 33, "%02d %02d %02d", prms->tetramino->point->x,
             prms->tetramino->point->y, (*prms).tetramino->type);
    print_tetramino(*prms->tetramino);
    refresh();
  } else {
    add_tetramino_on_board(prms);
    tetraminopos_init(prms->tetramino->point);
    prms->tetramino->type = (prms->tetramino->type + 1) % 7;
    *prms->state = SPAWN;
  }
  check(prms);
}

void moveright(params_t *prms) {
  if (is_block_right(prms)) {
    clear_tetramino(*prms->tetramino);
    prms->tetramino->point->y += 1;
    print_tetramino(*prms->tetramino);
    refresh();
  }
  check(prms);
}

void moveleft(params_t *prms) {
  if (is_block_left(prms)) {
    clear_tetramino(*prms->tetramino);
    prms->tetramino->point->y -= 1;
    print_tetramino(*prms->tetramino);
    refresh();
  }

  check(prms);
}

// void movefast(params_t *prms) {
//   if (prms->tetramino_pos->y > 2) {
//     CLEAR_BACKPOS(prms->tetramino_pos->x, prms->tetramino_pos->y);
//     prms->tetramino_pos->y -= 3;
//     PRINT_TETRAMINO(prms->tetramino_pos->x, prms->tetramino_pos->y);
//     refresh();
//   }

//   check(prms);
// }

void turn_right(params_t *prms) {
  prms->tetramino->variant = (prms->tetramino->variant + 1) % 4;
  clear_tetramino(*prms->tetramino);
  get_tetramino(prms->tetramino);
  print_tetramino(*prms->tetramino);
  *prms->state = MOVING;
}

void pause(params_t *prms) {
  MVPRINTW(1, 2, "Press ENTER or P to continue");
  MVPRINTW(2, 8, "or ESC to exit");

  int user_input = 0;
  while (user_input != ESCAPE_KEY && user_input != P_KEY &&
         user_input != ENTER_KEY) {
    user_input = GET_USER_INPUT;
  }
  MVPRINTW(1, 2, "                            ");
  MVPRINTW(2, 8, "              ");
  signals signal = get_signal(user_input);
  if (signal == ESCAPE_BTN) {
    *prms->state = EXIT_STATE;
  } else {
    *prms->state = MOVING;
  }
}

void reach(params_t *prms) {
  prms->stats->score += 1;
  add_proggress(prms->map);
  // if (check_level_compl(prms->map))
  // {
  //     prms->stats->level++;
  //     prms->stats->speed++;
  //     *prms->state = SPAWN;
  // }
  // else
  {
    tetraminopos_init(prms->tetramino->point);
    print_finished(prms->map);
    *prms->state = SPAWN;
  }
}

void fell(params_t *prms) {
  if (prms->stats->fell) {
    // prms->stats->lives--;
    tetraminopos_init(prms->tetramino->point);
    *prms->state = MOVING;
  } else
    *prms->state = GAMEOVER;
}

void gameover(params_t *prms) { print_banner(prms->stats); }

void exitstate(params_t *prms) { *prms->state = EXIT_STATE; }