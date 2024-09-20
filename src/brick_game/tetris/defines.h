#ifndef DEFINES_H
#define DEFINES_H

#define WIN_INIT(time)    \
  {                       \
    initscr();            \
    noecho();             \
    curs_set(0);          \
    keypad(stdscr, TRUE); \
    timeout(time);        \
  }

#define GET_USER_INPUT getch()

#define MVPRINTW(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)
#define CLEAR_BACKPOS(y, x) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), ' ')

#define SCORE_FILE "brick_game/tetris/score.txt"

#define INTRO_MESSAGE_LEN 21
#define INTRO_MESSAGE "Press ENTER to Start!"

#define MAX_LVL 10
#define BASE_DELAY 1000

#define SCORE_FOR_NXT_LVL 600

#define ROWS_MAP 20
#define COLS_MAP 10

#define BOARDS_BEGIN 2

#define TETRSTART_X (-1)
#define TETRSTART_Y (3)
#define INITIAL_TIMEOUT 100

#define BOARD_N (ROWS_MAP + MAP_PADDING * 2)
#define BOARD_M 30
#define HUD_WIDTH 12
#define MAP_PADDING 3

#define SUCCESS 0
// #define ERROR 1

#define NOSIG 8

#define ESCAPE_KEY 27
#define ENTER_KEY 10
#define R_KEY 35
#define P_KEY 112
#define P_KEY_SMALL 80

#define TETR_BLOCK "#"
#define BLOCK "■"

#endif