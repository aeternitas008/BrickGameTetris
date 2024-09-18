#ifndef OBJECTS_H
#define OBJECTS_H

#include <ncurses.h>

#include "defines.h"

typedef struct {
  int x;
  int y;
} position;

typedef struct {
  position *point;
  int type;
  int variant;
  unsigned int figure[4][4];
  unsigned int array_figures[19][4][4];
} tetramino_t;

typedef struct {
  int field[ROWS_MAP][COLS_MAP];
} board_t;

#endif