#include "../inc/frog_frontend.h"
#include <wchar.h>
#include <locale.h>
#include <unistd.h>


void print_overlay(void)
{   
    init_pair (1, COLOR_CYAN, COLOR_BLACK);
    init_pair (2, COLOR_MAGENTA, COLOR_BLACK);
    attron (COLOR_PAIR(1));
    print_rectangle(0, BOARD_N + 1, 0, BOARD_M + 1);
    print_rectangle(0, BOARD_N + 1, BOARD_M + 2, BOARD_M + HUD_WIDTH + 5);

    for (int i = 1; i <= 4; i++) {
        int a = 0;
        if (i == 4) a = 3;
        print_rectangle(i + (i - 1) * 3, i * 4 + a, BOARD_M + 3, BOARD_M + HUD_WIDTH + 4);
    }
    print_rectangle(23, 26, BOARD_M + 3, BOARD_M + HUD_WIDTH + 4);

    MVPRINTW(2, BOARD_M + 5, "HIGH SCORE");
    MVPRINTW(3, BOARD_M + 8, "1927");
    
    MVPRINTW(6, BOARD_M + 8, "SCORE");
    MVPRINTW(7, BOARD_M + 8, "00000");
    
    MVPRINTW(10, BOARD_M + 8, "LEVEL");
    MVPRINTW(11, BOARD_M + 12, "0");

    MVPRINTW(14, BOARD_M + 8, "NEXT");
    MVPRINTW(15, BOARD_M + 4, "[■][■][ ][■]");
    MVPRINTW(16, BOARD_M + 4, "[■][■][■][■]");
    MVPRINTW(17, BOARD_M + 4, "[ ][ ][ ][■]");
    MVPRINTW(18, BOARD_M + 4, "[ ][ ][ ][■]");

    MVPRINTW(24, BOARD_M + 8, "TIME");
    MVPRINTW(25, BOARD_M + 8, "12:50");

    // MVPRINTW(21, 1, "[■][■][■][■][■][■][■][■][■][■]");
    // MVPRINTW(22, 1, "[■][■][■][■][■][■][■][■][■][■]");
    // MVPRINTW(23, 1, "[■][■][■][■][■][■][■][■][■][■]");
    // MVPRINTW(24, 1, "[■][■][■][■][■][■][■][■][■][■]");
    // MVPRINTW(25, 1, "[■][■][■][■][■][■][■][■][■][■]");
    // MVPRINTW(26, 1, "[■][■][■][■][■][■][■][■][■][■]");
    // MVPRINTW(27, 1, "[■][■][■][■][■][■][■][■][■][■]");
    
    // ▢▢▢▢

    MVPRINTW(BOARD_N / 2, (BOARD_M - INTRO_MESSAGE_LEN) / 2 + 1, INTRO_MESSAGE);
}

void print_levelerror(void)
{
    clear();
    MVPRINTW(0, 0, "An error occured openning level file!");
    MVPRINTW(2, 0, "Please check ./tests/ directory.");
    MVPRINTW(3, 0, "There should be 5 level files named level_(1-5).txt.");
    MVPRINTW(4, 0, "Also try to open the game nearby ./tests/ directory.");
    MVPRINTW(6, 0, "Press any key to exit.");
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x)
{
    MVADDCH(top_y, left_x, ACS_ULCORNER);

    int i = left_x + 1;

    for (;i < right_x; i++)
        MVADDCH(top_y, i, ACS_HLINE);
    MVADDCH(top_y, i, ACS_URCORNER);

    for (int i = top_y + 1; i < bottom_y; i++)
    {
        MVADDCH(i, left_x, ACS_VLINE);
        MVADDCH(i, right_x, ACS_VLINE);
    }

    MVADDCH(bottom_y, left_x, ACS_LLCORNER);
    i = left_x + 1;
    for (;i < right_x; i++)
        MVADDCH(bottom_y, i, ACS_HLINE);
    MVADDCH(bottom_y, i, ACS_LRCORNER);
}

// вывод статов
void print_stats(game_stats_t *stats)
{
    MVPRINTW(3, BOARD_M + 8, "%04d", stats->high_score);
    MVPRINTW(7, BOARD_M + 8, "%04d", stats->score);
    MVPRINTW(11, BOARD_M + 12, "%d", stats->level);
}

void print_field(board_t *game, tetramino_pos *tetramino_pos)
{
    for (int i = 4; i <= 23; i++) {
        MVPRINTW(i, 1, "[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]");
        refresh();
        napms(30);
    }
}

void print_board(board_t *game, tetramino_pos *tetramino_pos)
{
    PRINT_TETRAMINO(tetramino_pos->x, tetramino_pos->y);
}

void print_cars(board_t *game)
{
    for(int i = MAP_PADDING + 1; i < BOARD_N - MAP_PADDING + 1; i++)
    {
        if (i % 2 == (MAP_PADDING + 1) % 2)
        {
            for (int j = 1; j < BOARD_M + 1; j++)
                MVADDCH(i, j, ACS_BLOCK);
        }
        else
        {
            for (int j = 1; j < BOARD_M + 1; j++)
            {
                if (game->field[i - MAP_PADDING - 1][j - 1] == '0')
                    MVADDCH(i, j, ' ');
                else
                    MVADDCH(i, j, ']');
            }
        }
    }
}

void print_finished(board_t *game)
{
    for (int i = 0; i < BOARD_M; i++)
    {
        if (game->field[i][i] == '0')
            MVADDCH(1, i + 1, ACS_BLOCK);
        else
            MVADDCH(1, i + 1, ' ');
    }       
}
void print_banner(game_stats_t *stats)
{
    banner_t banner;

    memset(banner.matrix, 0, (BANNER_N + 1) * (BANNER_M + 1));

    clear();
    
    if (!(read_banner(stats, &banner)))
    {
        for (int i = 0; i < BANNER_N; i++)
            for (int j = 0; j < BANNER_M; j++)
                if (banner.matrix[i][j] == '#')
                    MVADDCH(i, j, ACS_BLOCK);
                else
                    MVADDCH(i, j, ' ');
        refresh();
        napms(2000);
    }
}

int read_banner(game_stats_t *stats, banner_t *banner)
{
    int rc = SUCCESS;
    FILE *file = NULL;

    // if (stats->lives)
    //     file = fopen(YOU_WON, "r");
    // else
    //     file = fopen(YOU_LOSE, "r");

    if (file)
    {
        for (int i = 0; i < BANNER_N - 1 && !rc; i++)
        {
            if (fgets(banner->matrix[i], BANNER_M + 2, file) == NULL)
                rc = ERROR;
            else
                banner->matrix[i][strcspn(banner->matrix[i], "\n")] = '\0';
        }

        fclose(file);
    }
    else
        rc = ERROR;

    return rc;
}