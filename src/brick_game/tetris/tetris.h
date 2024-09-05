#ifndef TETRIS_H
#define TETRIS_H

#include <locale.h>

#include "tetr_backend.h"
#include "../../gui/cli/tetr_frontend.h"

void game_loop();

void get_tetramino(tetramino_t *tetramino);
#endif