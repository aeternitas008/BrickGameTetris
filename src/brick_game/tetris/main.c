#include "backend.h"

// #include "../../gui/cli/tetr_frontend.h"
// #include <stdlib.h>

int main(void) {
  setlocale(LC_CTYPE, "");
  WIN_INIT(50);
  print_overlay();
  game_loop();
  endwin();
  return SUCCESS;
}

// void refresh_game(params_t *prms) {
//   init_board(prms->map);
//   prms->stats->score = 0;
//   prms->state = START;
// }

void game_loop() {
  bool no_break = TRUE;
  state_t state = START;
  int signal = 0;
  params_t *prms = getPrmsInstance();
  prms->state = &state;


  while (no_break) {
    if (state == MOVING || state == START) signal = GET_USER_INPUT;
    sigact(get_signal(signal));
    if (state == EXIT_STATE) no_break = FALSE;
    // if( state == GAMEOVER ) { refresh_game(prms); }
  }
}
