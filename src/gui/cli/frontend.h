#ifndef FRONTEND_H
#define FRONTEND_H

#include "../../brick_game/tetris/main.h"
// #include "../../brick_game/tetris/defines.h"

void PrintOverlay(void);
void PrintRectangle(int top_y, int bottom_y, int left_x, int right_x);
void PrintStats(GameInfo_t *stats);
void PrintField();
void PrintBoard(Board_t map);
void PrintGameOver(GameInfo_t *stats);
void PrintTetramino(Tetramino_t tetramino);
void ClearTetramino(Tetramino_t tetramino);

void PrintFrontNextTetr(Tetramino_t tetramino);
void PrintPause();
void ClearPause();
void UpdateTime(int hours, int minutes);
#endif