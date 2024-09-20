#include "backend.h"

void GameLoop() {
  bool no_break = TRUE;
  int signal = 0;
  Params_t *prms = GetPrmsInstance();
  State_t state = START;
  GameInfo_t stats;
  Position tetramino_pos;
  struct timespec time;
  Board_t map;
  InitBoard(&map);
  prms->map = &map;
  TetraminoPosInit(&tetramino_pos);
  Tetramino_t tetramino = {0};
  tetramino.point = &tetramino_pos;
  tetramino.variant = 0;
  tetramino.type = 0;
  GetArrayFigures(tetramino.array_figures);
  StatsInit(&stats);
  prms->stats = &stats;
  prms->state = &state;
  prms->tetramino = &tetramino;
  prms->time = &time;

  while (no_break) {
    if (state == MOVING || state == START) signal = GET_USER_INPUT;
    SigAct(GetSignal(signal));
    if (state == EXIT_STATE) no_break = FALSE;
  }
}

int main(void) {
  setlocale(LC_CTYPE, "");
  WIN_INIT(INITIAL_TIMEOUT);
  PrintOverlay();
  GameLoop();
  endwin();
  return SUCCESS;
}