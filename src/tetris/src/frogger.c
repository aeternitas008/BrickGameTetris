#include "../inc/frogger.h"
#include "../inc/fsm.h"

int main(void)
{
    setlocale(LC_CTYPE, "");
    WIN_INIT(50);
    print_overlay();
    game_loop();
    endwin();

    return SUCCESS;
}

void game_loop()
{
    board_t map;
    game_stats_t stats;
    tetramino_pos tetramino_pos;;
    bool no_break = TRUE;
    int signal = 0;
    state_t state = START;

    stats_init(&stats);

    while (no_break)
    {
        if (state == GAMEOVER || state == EXIT_STATE)
            no_break = FALSE;

        sigact(get_signal(signal), &state, &stats, &map, &tetramino_pos);

        if (state == MOVING || state == START)
            signal = GET_USER_INPUT;
    }

    // if (state == FILE_ERROR_STATE)
    // {
    //     print_levelerror();
    //     nodelay(stdscr, FALSE);
    //     getch();
    // }
}