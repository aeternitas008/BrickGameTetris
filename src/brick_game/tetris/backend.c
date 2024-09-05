#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

#include "objects.h"
#include "tetr_backend.h"

#include "tetris.h"

static params_t s_prms;

params_t *getPrmsInstance() { return &s_prms; }

void get_tetramino(tetramino_t *tetramino) {
  int key = 0;
  if (tetramino->type == 1) {
    key = tetramino->variant % 2 + 1;
  } else if (tetramino->type == 2) {
    key = tetramino->variant % 2 + 3;
  } else if (tetramino->type == 3) {
    key = tetramino->variant % 2 + 5;
  } else if (tetramino->type == 4) {
    key = tetramino->variant + 7;
  } else if (tetramino->type == 5) {
    key = tetramino->variant + 11;
  } else if (tetramino->type == 6) {
    key = tetramino->variant + 15;
  }
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      tetramino->figure[x][y] = tetramino->array_figures[key][x][y];
    }
  }
}

void get_array_figures(unsigned int origin[19][4][4]) {
  printf("Inside get_matrix\n");
  unsigned int matrix[19][4][4] = {
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},

      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},

      {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},

      {{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}},

      {{0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}},

      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}},

      {{0, 0, 0, 1}, {0, 0, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}},

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
  for (int n = 0; n < 19; n++) {
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        origin[n][x][y] = matrix[n][x][y];
      }
    }
  }
}

int check_new_variant(params_t prms) {
  tetramino_t tetramino_test = *prms.tetramino;
  tetramino_test.variant = (tetramino_test.variant + 1) % 4;
  get_tetramino(&tetramino_test);
  int result = check_tetramino(prms, tetramino_test);
  return result;
}

int check_tetramino(params_t prms, tetramino_t tetramino) {
  int result = 0;
  for (int x = 0; x < 4 && result == 0; x++) {
    for (int y = 0; y < 4 && result == 0; y++) {
      if (tetramino.figure[x][y] == 1 &&
          (tetramino.point->y + y > 9 || tetramino.point->y + y < 0 ||
           tetramino.point->x + x < 0 || tetramino.point->x + x > 19 ||
           prms.map->field[tetramino.point->x + x][tetramino.point->y + y] ==
               1)) {
        result = 1;
      }
    }
  }
  return result;
}

void init_board(board_t *map) {
  for (int x = 0; x < 20; x++) {
    for (int y = 0; y < 10; y++) {
      map->field[x][y] = 0;
    }
  }
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

void add_proggress(board_t *map) {
  // int position = 0;

  // for (; map->finish[position] == '0'; position++) ;

  // for (int progress_cnt = BOARD_M / ; progress_cnt > 0; progress_cnt--)
  //     map->finish[position++] = '0';
}


void userInput(UserAction_t action, bool hold) {
  params_t *s_prms = getPrmsInstance();
  s_prms->sig = action;
  s_prms->hold = hold;
}

bool check_finish_state(position *frog, board_t *map) {
  bool rc = FALSE;

  if (frog->y == 1) rc = TRUE;

  return rc;
}

bool check_level(board_t *map) {
  bool rc = TRUE;
  for (int i = 0; i < BOARD_M && rc; i++) {
  }
  // if (map->finish[i] != '0')
  //     rc = FALSE;

  return rc;
}

bool check_collide(position *tetramino_pos, board_t *map) {
  bool rc = FALSE;

  if (tetramino_pos->y > MAP_PADDING &&
      tetramino_pos->y < ROWS_MAP + MAP_PADDING + 1 &&
      map->field[tetramino_pos->y - MAP_PADDING - 1][tetramino_pos->x - 1] ==
          ']')
    rc = TRUE;

  return rc;
}

void tetraminopos_init(position *tetramino_pos) {
  tetramino_pos->x = TETRSTART_X;
  tetramino_pos->y = TETRSTART_Y;
}

void fill_finish(char *finish_line) {
  for (int i = 0; i < BOARD_M; i++) finish_line[i] = ' ';

  finish_line[BOARD_M] = '\0';
}

void stats_init(GameInfo_t *stats) {
  char *fname = "meta.txt";
  int N = 256;
  char buffer[N];
  FILE *fp = fopen(fname, "r");
  if (fp != NULL) {
    fgets(buffer, N, fp);
    char *score = strchr(buffer, ':');
    stats->high_score = atoi(++score);
    fgets(buffer, N, fp);
    char *level = strchr(buffer, ':');
    stats->level = atoi(++level);
    fclose(fp);
  } else {
    FILE *file = fopen(fname, "w");
    fprintf(file, "score:0\nlevel:1");
    fclose(file);
    stats->high_score = 0;
    stats->level = 1;
  }
  stats->level = 1;
  MVPRINTW(3, BOARD_M + 8, "%05d", stats->high_score);
  MVPRINTW(11, BOARD_M + 11, "%02d", stats->level);
  // MVPRINTW(23, BOARD_M + 8, "%s", stats->current_time);
  stats->speed = 1;
  stats->score = 0;
  // stats->won = FALSE;
}
void new_stats_init(GameInfo_t *stats) {
  char *fname = "meta.txt";
  // int N = 256;
  // char buffer[N];
  // FILE *fp = fopen(fname, "r");
  // if (fp != NULL) {
  //   fgets(buffer, N, fp);
  //   char *score = strchr(buffer, ':');
  //   stats->high_score = atoi(++score);
  //   fgets(buffer, N, fp);
  //   char *level = strchr(buffer, ':');
  //   stats->level = atoi(++level);
  //   fclose(fp);
  // } else {
  if (stats->score > stats->high_score) {
    stats->high_score = stats->score;
    FILE *file = fopen(fname, "w");
    fprintf(file, "score:%d\nlevel:%d", stats->score, stats->level);
    fclose(file);
  }
  MVPRINTW(3, BOARD_M + 8, "%05d", stats->high_score);
  MVPRINTW(7, BOARD_M + 8, "%05d", stats->score);
  MVPRINTW(11, BOARD_M + 11, "%02d", stats->level);
}

// переписать свой код удаления линии на этот
void remove_line(board_t *map, int line) {
  for (int i = 1; i < ROWS_MAP; i += 2) {
    memmove(&map->field[i][1], &map->field[i][0], COLS_MAP * sizeof(char));
    map->field[i][0] = map->field[i][COLS_MAP];
  }
}


// #define _POSIX_C_SOURCE 199309L

// for ubuntu
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

typedef void (*action)(params_t *prms);


action fsm_table[8][10] = {
    {start, game_pause, exitstate, NULL, NULL, NULL, NULL, NULL, NULL},
    {spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn},
    {check, game_pause, exitstate, moveleft, moveright, moveup, movedown, turn_right,
     check},
    {shifting, shifting, exitstate, shifting, shifting, shifting, shifting,
     shifting, shifting},
    {reach, reach, reach, reach, reach, reach, reach, reach, check},
    {reach, reach, reach, reach, reach, reach, reach, reach, check},
    // {collide, collide, collide, collide, collide, collide, collide},
    {gameover, gameover, gameover, gameover, gameover, gameover, gameover,
     gameover, gameover},
    {exitstate, exitstate, exitstate, exitstate, exitstate, exitstate,
     exitstate, check, check}};

// tetramino_t get_tetramino(tetramino_t* matrix_tetram[7][4], int x, int y) {
//   tetramino_t result_tetramino;
//   if (x == 0) fill_tetramino(matrix_tetram[x][]);

//   }
// }

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

void sigact(UserAction_t sig) {
  action act = NULL;
  // params_t prms;
  // prms.stats = stats;
  // prms.state = state;
  // prms.map = map;
  // prms.tetramino = map->tetramino;
  // prms.time = time;
  // prms.time =
  // if (*state != FILE_ERROR_STATE)
  userInput(sig, sig == Down);
  params_t *prms = getPrmsInstance();
  act = fsm_table[*prms->state][sig];
  if (act) act(prms);
}

UserAction_t get_signal(int user_input) {
  UserAction_t rc = NOSIG;

  if (user_input == ENTER_KEY)
    rc = Start;
  else if (user_input == P_KEY_SMALL || user_input == P_KEY)
    rc = Pause;
  else if (user_input == ESCAPE_KEY)
    rc = Terminate;
  else if (user_input == KEY_LEFT)
    rc = Left;
  else if (user_input == KEY_RIGHT)
    rc = Right;
  else if (user_input == KEY_UP)
    rc = Up;
  else if (user_input == KEY_DOWN)
    rc = Down;
  else if (user_input == ' ')
    rc = Action;
  return rc;
}

// void set_high_score() {}

// void save_high_score() {}

int offset(params_t *prms, struct timespec *current_time) {
  int seconds = (current_time->tv_sec - (*prms).time->tv_sec) * 1000;
  int nanoseconds = (current_time->tv_nsec - (*prms).time->tv_nsec) / 1e6;
  int total_offset = seconds + nanoseconds;
  // MVPRINTW(6, 40, "%d", seconds);
  return total_offset;
}

void shifting(params_t *prms) {
  // shift_map(prms->map);
  int hours = ((long int)prms->time->tv_sec / 3600) % 24 + 3;
  int minutes = (long int)prms->time->tv_sec % 3600 / 60;
  MVPRINTW(23, BOARD_M + 8, "%02d:%02d", hours, minutes);
  struct timespec current_time;
  clock_gettime(CLOCK_REALTIME, &current_time);
  
  int base_delay = 1000;
  // difficult level
  int diff = base_delay * pow(0.8, prms->stats->level - 1);
  if (offset(prms, &current_time) >= diff) {
    movedown(prms);
    (*prms).time->tv_sec = current_time.tv_sec;
    (*prms).time->tv_nsec = current_time.tv_nsec;
  }

  if (*prms->state != SPAWN) {
    *prms->state = MOVING;
  }
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

  if (*prms->state != SPAWN) {
    *prms->state = SHIFTING;
  }
}

void start(params_t *prms) {
  print_field();
  tetraminopos_init(prms->tetramino->point);
  clock_gettime(CLOCK_REALTIME, prms->time);
  stats_init(prms->stats);
  *prms->state = SPAWN;
}

void spawn(params_t *prms) {
  prms->tetramino->variant = 0;
  tetraminopos_init(prms->tetramino->point);
  get_tetramino(prms->tetramino);
  print_board(*prms->map);
  print_tetramino(*prms->tetramino);
  if (check_tetramino(*prms, *prms->tetramino) == 1) {
    *prms->state = GAMEOVER;
  } else {
    print_next_tetramino(prms);
    MVPRINTW(8, 33, "%02d", (*prms).tetramino->type);
    *prms->state = MOVING;
  }
}

void moveup(params_t *prms) {
  // stub
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

bool is_block_nearby(params_t *prms, int num) {
  bool result = 1;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (prms->tetramino->figure[x][y] == 1 &&
          (prms->tetramino->point->y + y >= 9 ||
           prms->map->field[prms->tetramino->point->x + x]
                           [prms->tetramino->point->y + y + num] == 1)) {
        result = 0;
      }
    }
  }
  return result;
}

bool is_block_right(params_t *prms) { return is_block_nearby(prms, 1); }

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

void movedown(params_t *prms) {
  if (is_not_block_below(prms)) {
    do {
        clear_tetramino(*prms->tetramino);
        prms->tetramino->point->x += 1;
        print_tetramino(*prms->tetramino);
    } while (prms->hold && is_not_block_below(prms));
    refresh();
    prms->hold = 0;
}
  if (!is_not_block_below(prms)) {
    add_tetramino_on_board(prms);
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

void turn_right(params_t *prms) {
  if (check_new_variant(*prms) == 0) {
    prms->tetramino->variant = (prms->tetramino->variant + 1) % 4;
    clear_tetramino(*prms->tetramino);
    get_tetramino(prms->tetramino);
    print_tetramino(*prms->tetramino);
  }
  *prms->state = MOVING;
}

void game_pause(params_t *prms) {
  MVPRINTW(1, 2, "Press ENTER or P to continue");
  MVPRINTW(2, 8, "or ESC to exit");

  int user_input = 0;
  while (user_input != ESCAPE_KEY && user_input != P_KEY &&
         user_input != ENTER_KEY) {
    user_input = GET_USER_INPUT;
  }
  MVPRINTW(1, 2, "                            ");
  MVPRINTW(2, 8, "              ");
  UserAction_t signal = get_signal(user_input);
  if (signal == Terminate) {
    *prms->state = EXIT_STATE;
  } else {
    *prms->state = MOVING;
  }
}

void reach(params_t *prms) {
  prms->stats->score += 1;
  add_proggress(prms->map);
  {
    tetraminopos_init(prms->tetramino->point);
    print_finished(prms->map);
    *prms->state = SPAWN;
  }
}

// void fell(params_t *prms) {
//   if (prms->stats->fell) {
//     tetraminopos_init(prms->tetramino->point);
//     *prms->state = MOVING;
//   } else
//     *prms->state = GAMEOVER;
// }

void gameover(params_t *prms) { print_gameover(prms->stats); }

void exitstate(params_t *prms) { *prms->state = EXIT_STATE; }