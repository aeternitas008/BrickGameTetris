#include "../inc/tetris.h"

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
  GameInfo_t stats;
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

  while (no_break) {
    if (state == GAMEOVER || state == EXIT_STATE) no_break = FALSE;

    sigact(get_signal(signal), &prms);
    // if (state == SPAWN) {
    //   *tetramino.type = tetramino.type + 1;
    // }
    if (state == MOVING || state == START) 
    // void userInput(UserAction_t action, bool hold);
    signal = GET_USER_INPUT;
  }
}

