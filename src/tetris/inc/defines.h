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

// #define PRINT_TETRAMINO(x, y)
//   mvprintw(BOARDS_BEGIN + (x), BOARDS_BEGIN + (y), "@")
#define MVPRINTW(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)
#define CLEAR_BACKPOS(y, x) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), ' ')

#define YOU_WON "tests/game_progress/you_won.txt"
#define YOU_LOSE "tests/game_progress/you_lose.txt"
#define LEVEL_DIR "tests/levels/level_"
#define INTRO_MESSAGE "Press ENTER to start!"
#define INTRO_MESSAGE_LEN 21
#define LEVEL_CNT 5
#define LEVELNAME_MAX 25

#define MAX_WIN_COUNT 10

#define ROWS_MAP 20
#define COLS_MAP 10

#define BOARDS_BEGIN 2

#define TETRSTART_X (0)
#define TETRSTART_Y (0)
#define INITIAL_TIMEOUT 150

#define BOARD_N (ROWS_MAP + MAP_PADDING * 2)
#define BOARD_M 30
#define HUD_WIDTH 12
#define MAP_PADDING 3

#define BANNER_N 10
#define BANNER_M 100

#define SUCCESS 0
#define ERROR 1

#define NO_INPUT -1

#define ESCAPE_KEY 27
#define ENTER_KEY 10
#define SPACE_KEY 49
#define R_KEY 35
#define P_KEY 112
#define P_KEY_SMALL 80

#define MY_BLOCK = "▢";

#endif