#include "../inc/tetris.h"
// #define _POSIX_C_SOURCE 199309L
// struct timeval {
//    time_t      tv_sec;   // Number of whole seconds of elapsed time
//    long int    tv_usec;  // Number of microseconds of rest of elapsed time minus tv_sec. Always less than one million
// };

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

void get_array_figures(unsigned int  origin[19][4][4]) {
  printf("Inside get_matrix\n");
  unsigned int  matrix[19][4][4] = {
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

int main(void) {
  setlocale(LC_CTYPE, "");
  WIN_INIT(50);
  print_overlay();
  game_loop();
  endwin();

  return SUCCESS;
}

void game_loop() {
  board_t map;
  game_stats_t stats;
  position tetramino_pos;
  bool no_break = TRUE;
  int signal = 0;
  state_t state = START;
  struct timespec time;
  init_board(&map);
  tetraminopos_init(&tetramino_pos);
  tetramino_t tetramino = {0};
  tetramino.point = &tetramino_pos;
  tetramino.variant = 0;
  tetramino.type = 0;
  get_array_figures(tetramino.array_figures);
  map.tetramino = &tetramino;
  // get_tetramino(&tetramino);
  *stats.current_time = '\0';
  stats_init(&stats);
  params_t prms;
  prms.stats = &stats;
  prms.state = &state;
  prms.map = &map;
  prms.tetramino = &tetramino;
  prms.time = &time;
  
  // get_matrix(tetramino.array_figures);

  while (no_break) {
    if (state == GAMEOVER || state == EXIT_STATE) no_break = FALSE;
    
    sigact(get_signal(signal), &state, &prms);
    // if (state == SPAWN) {
    //   *tetramino.type = tetramino.type + 1;
    // }
    if (state == MOVING || state == START) signal = GET_USER_INPUT;
  }

  // if (state == FILE_ERROR_STATE)
  // {
  //     print_levelerror();
  //     nodelay(stdscr, FALSE);
  //     getch();
  // }
}