#include "tetris.h"

int main(void) {
  setlocale(LC_CTYPE, "");
  WIN_INIT(50);
  print_overlay();
  game_loop();
  endwin();

  return SUCCESS;
}

void game_loop() {
  bool no_break = TRUE;
  state_t state = START;
  int signal = 0;

  params_t *prms = getPrmsInstance();

  board_t map;
  GameInfo_t stats;
  position tetramino_pos;
  struct timespec time;
  // state_t state = SPAWN;
  init_board(&map);
  tetraminopos_init(&tetramino_pos);
  tetramino_t tetramino = {0};
  tetramino.point = &tetramino_pos;
  tetramino.variant = 0;
  tetramino.type = 0;
  get_array_figures(tetramino.array_figures);
  map.tetramino = &tetramino;
  // get_tetramino(&tetramino);
  stats_init(&stats);
  prms->stats = &stats;
  prms->state = &state;
  prms->map = &map;
  prms->tetramino = &tetramino;
  prms->time = &time;

  while (no_break) {

    sigact(get_signal(signal));
    if (state == GAMEOVER || state == EXIT_STATE) no_break = FALSE;
    if (state == MOVING || state == START)
      signal = GET_USER_INPUT;
  }
}
