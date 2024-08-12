#ifndef TETRIS_H
#define TETRIS_H

#include <locale.h>

#include "tetr_backend.h"
#include "tetr_frontend.h"

void game_loop();

// void get_matrix(u_int8_t*[19][4][4]);
// void get_matrix(u_int8_t[19][4][4]);
void get_tetramino(tetramino_t *tetramino);
#endif