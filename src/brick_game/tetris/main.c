#include "backend.h"

void game_loop() {
  bool no_break = TRUE;
  int signal = 0;
  // params_t *prms = getPrmsInstance();


  params_t *prms = getPrmsInstance();
  state_t state = START;
  GameInfo_t stats;
  position tetramino_pos;
  struct timespec time;
  board_t map;
  init_board(&map);
  prms->map = &map;
  tetraminopos_init(&tetramino_pos);
  tetramino_t tetramino = {0};
  tetramino.point = &tetramino_pos;
  tetramino.variant = 0;
  tetramino.type = 0;
  get_array_figures(tetramino.array_figures);
  stats_init(&stats);
  prms->stats = &stats;
  prms->state = &state;
  prms->tetramino = &tetramino;
  prms->time = &time;

  while (no_break) {
    if (state == MOVING || state == START) signal = GET_USER_INPUT;
    sigact(get_signal(signal));
    if (state == EXIT_STATE) no_break = FALSE;
  }
}

int main(void) {
  setlocale(LC_CTYPE, "");
  WIN_INIT(INITIAL_TIMEOUT);
  print_overlay();
  game_loop();
  endwin();
  return SUCCESS;
}