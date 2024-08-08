#include "../inc/fsm.h"

// This is a finite state machine realisation based on matrix of "actions".
/*
    Function sigact() takes an action function from fsm_table.
    Game state defines an index of line in matrix (where to get).
    User signal defines an index of column in matrix (what to get).

    Pros: 
        1) By instantly taking needed action, speed of processing is higher than switch-case realisation.
        2) Code is easy to read.
        3) Flexible (easy to add new state)
    Cons:
        1) More memory usage.
*/

typedef struct game_params
{
    game_stats_t *stats;
    state_t *state;
    board_t *map;
    tetramino_pos *tetramino_pos;
    bool *break_flag;
} params_t;

typedef void (*action)(params_t *prms);

void start(params_t *prms);
void spawn(params_t *prms);
void moveup(params_t *prms);
void movedown(params_t *prms);
void moveright(params_t *prms);
void moveleft(params_t *prms);
void shifting(params_t *prms);
void reach(params_t *prms);
// void collide(params_t *prms);
void gameover(params_t *prms);
void exitstate(params_t *prms);
void check(params_t *prms);

action fsm_table[7][7] = {
    {start, NULL, NULL, NULL, exitstate, start, NULL},
    {spawn, spawn, spawn, spawn, spawn, spawn, spawn},
    {moveup, movedown, moveright, moveleft, exitstate, check, check},
    {shifting, shifting, shifting, shifting, shifting, shifting, shifting},
    {reach, reach, reach, reach, reach, reach, reach},
    // {collide, collide, collide, collide, collide, collide, collide},
    {gameover, gameover, gameover, gameover, gameover, gameover, gameover},
    {exitstate, exitstate, exitstate, exitstate, exitstate, exitstate, exitstate}
};

void sigact(signals sig, state_t *state, game_stats_t *stats,board_t *map, tetramino_pos *tetramino_pos)
{
    action act = NULL;
    params_t prms;
    prms.stats = stats;
    prms.state = state;
    prms.map = map;
    prms.tetramino_pos = tetramino_pos;

    // if (*state != FILE_ERROR_STATE)
    act = fsm_table[*state][sig];

    

    if (act)
        act(&prms);
}

signals get_signal(int user_input)
{
    signals rc = NOSIG;

    if (user_input == KEY_UP)
        rc = MOVE_UP;
    else if (user_input == KEY_DOWN)
        rc = MOVE_DOWN;
    else if (user_input == KEY_LEFT)
        rc = MOVE_LEFT;
    else if (user_input == KEY_RIGHT)
        rc = MOVE_RIGHT;
    else if (user_input == ESCAPE)
        rc = ESCAPE_BTN;
    else if (user_input == ENTER_KEY)
        rc = ENTER_BTN;
    else if (user_input == ENTER_KEY)
        rc = ENTER_BTN;
    else if (user_input == SPACE_KEY)
        rc = SPACE_BTN;

    return rc;
}

void set_high_score() {

}

void save_high_score() {
    
}

void shifting(params_t *prms)
{
    shift_map(prms->map);

    // if (check_collide(prms->tetramino_pos, prms->map))
    //     *prms->state = FELL;
    // else
    // {
    if (prms->tetramino_pos->x != BOARD_N - 3) {
        movedown(prms);
    }
    napms(300);
    *prms->state = MOVING;

        // print_board(prms->map, prms->tetramino_pos);
        // print_stats(prms->stats);
    // }

    // MVPRINTW(3, BOARD_M + 8, "OK");
}

void check(params_t *prms)
{
    if (check_collide(prms->tetramino_pos, prms->map))
        *prms->state = FELL;
    else if (check_finish_state(prms->tetramino_pos, prms->map))
        *prms->state = REACH;
    else
        *prms->state = SHIFTING;
}

void tetramino_fell(tetramino_pos *tetramino_pos) {
    while (tetramino_pos->x <= 22) {
        napms(400);
        MVPRINTW(tetramino_pos->x, tetramino_pos->y, " ");
        MVPRINTW(++(*tetramino_pos).x, tetramino_pos->y, "@");
        refresh();
    }
}

void start(params_t *prms)
{
    // if (!lvlproc(prms->map, prms->stats))
    // {
        // set_board();
    print_field();
    // MVPRINTW(3, BOARD_M + 8, "OK");
    tetraminopos_init(prms->tetramino_pos);
    // print_board(prms->map, prms->tetramino_pos);
    // tetramino_fell(prms->tetramino_pos);
    *prms->state=SPAWN;
    // }
}


void spawn(params_t *prms)
{
    if (prms->stats->level > LEVEL_CNT)
        *prms->state = GAMEOVER;
    else
    {
        // if (!lvlproc(prms->map, prms->stats))
        // {
            // fill_finish(prms->map->finish);
            // print_finished(prms->map);
            print_board(prms->map, prms->tetramino_pos);
            tetraminopos_init(prms->tetramino_pos);
            // tetramino_fell(prms->tetramino_pos);
            *prms->state = MOVING;
        // }
        // MVPRINTW(3, BOARD_M + 8, "OK");
        // else
        //     *prms->state = FILE_ERROR_STATE;
    }
}

void moveup(params_t *prms)
{
    // if (prms->tetramino_pos->y != 1)
    // {
    //     CLEAR_BACKPOS(prms->tetramino_pos->y, prms->tetramino_pos->x);
    //     prms->tetramino_pos->y -= 2;
    // }

    // check(prms);
}

void movedown(params_t *prms)
{
    if (prms->tetramino_pos->x != BOARD_N - 3)
    {
        CLEAR_BACKPOS(prms->tetramino_pos->x, prms->tetramino_pos->y);
        prms->tetramino_pos->x += 1;
        PRINT_TETRAMINO(prms->tetramino_pos->x, prms->tetramino_pos->y);

        refresh();
    }

    check(prms);
}

void moveright(params_t *prms)
{
    if (prms->tetramino_pos->y < BOARD_M - 1)
    {
        CLEAR_BACKPOS(prms->tetramino_pos->x, prms->tetramino_pos->y);
        prms->tetramino_pos->y += 3;
        PRINT_TETRAMINO(prms->tetramino_pos->x, prms->tetramino_pos->y);
        refresh();
    }

    check(prms);
}

void moveleft(params_t *prms)
{
    if (prms->tetramino_pos->y > 2)
    {
        CLEAR_BACKPOS(prms->tetramino_pos->x, prms->tetramino_pos->y);
        prms->tetramino_pos->y -= 3;
        PRINT_TETRAMINO(prms->tetramino_pos->x, prms->tetramino_pos->y);
        refresh();
    }

    check(prms);
}

void reach(params_t *prms)
{
    prms->stats->score += 1;
    add_proggress(prms->map);
    // if (check_level_compl(prms->map))
    // {
    //     prms->stats->level++;
    //     prms->stats->speed++;
    //     *prms->state = SPAWN;
    // }
    // else
    {
        tetraminopos_init(prms->tetramino_pos);
        print_finished(prms->map);
        *prms->state = SPAWN;
    }
}

void fell(params_t *prms)
{
    if (prms->stats->fell)
    {
        // prms->stats->lives--;
        tetraminopos_init(prms->tetramino_pos);
        *prms->state = MOVING;
    }
    else
        *prms->state = GAMEOVER;
}

void gameover(params_t *prms)
{
    print_banner(prms->stats);
}

void exitstate(params_t *prms)
{
    *prms->state = EXIT_STATE;
}