#include "../inc/frog_backend.h"

int lvlproc(board_t *map, game_stats_t *stats)
{
    timeout(INITIAL_TIMEOUT - stats->speed * 15);
    
    char levelname[LEVELNAME_MAX + 1] = { 0 };

    sprintf(levelname, LEVEL_DIR"%d.txt", stats->level);
    
    FILE *level = fopen(levelname, "r");
    
    int rc = SUCCESS;

    if (level)
    {
        for (int i = 0; i < ROWS_MAP && !rc; i++)
        {
            if (fgets(map->field[i], COLS_MAP + 2, level) == NULL)
                rc = ERROR;
            else
                map->field[i][strcspn(map->field[i], "\n")] = '\0';
        }
        fclose(level);
    }
    else
        rc = ERROR;

    return rc;
}

void add_proggress(board_t *map)
{
    // int position = 0;

    // for (; map->finish[position] == '0'; position++) ;

    // for (int progress_cnt = BOARD_M / ; progress_cnt > 0; progress_cnt--)
    //     map->finish[position++] = '0'; 
}

bool check_finish_state(tetramino_pos *frog, board_t *map)
{
    bool rc = FALSE;

    if (frog->y == 1)
        rc = TRUE;

    return rc;
}

bool check_level_compl(board_t *map)
{
    bool rc = TRUE;
    for (int i = 0; i < BOARD_M && rc; i++)
    {}
        // if (map->finish[i] != '0')
        //     rc = FALSE;

    return rc;
}

bool check_collide(tetramino_pos *tetramino_pos, board_t *map)
{
    bool rc = FALSE;

    if (tetramino_pos->y > MAP_PADDING && tetramino_pos->y < ROWS_MAP + MAP_PADDING + 1 && \
        map->field[tetramino_pos->y - MAP_PADDING - 1][tetramino_pos->x - 1] == ']')
        rc = TRUE;

    return rc;
}

void tetraminopos_init(tetramino_pos *tetramino_pos)
{
    tetramino_pos->x = TETRSTART_X;
    tetramino_pos->y = TETRSTART_Y;
}

void fill_finish(char *finish_line)
{
    for (int i = 0; i < BOARD_M; i++)
        finish_line[i] = ' ';

    finish_line[BOARD_M] = '\0';
}

void stats_init(game_stats_t *stats)
{
    char* fname = "meta.txt";
    int N = 256;
    char buffer[N];
    FILE *fp = fopen(fname, "r");
    if (fopen("filename", "r") != NULL) {
        fgets(buffer, N, fp);
        char *score = strchr(buffer, ':');
        stats->high_score = (*score)++;
        fgets(buffer, N, fp);
        char *level = strchr(buffer, ':');
        stats->level = (*level)++;
    } else {
        FILE *file = fopen("meta.txt", "w");
        fprintf(file, "score:0\n level:1");
        fclose(file);
        stats->high_score = 0;
        stats->level = 1;
    }
        sprintf(buffer, "%04d", stats->high_score);
        MVPRINTW(3, BOARD_M + 8, buffer);
        sprintf(buffer, "%d", stats->level);
        MVPRINTW(11, BOARD_M + 12, buffer);
        stats->speed = 1;
        stats->score = 0;
        stats->won = FALSE;
}

void shift_map(board_t *map)
{
    for (int i = 1; i < ROWS_MAP; i += 2)
    {
        memmove(&map->field[i][1], &map->field[i][0], COLS_MAP * sizeof(char));
        map->field[i][0] = map->field[i][COLS_MAP];
    }
}

void remove_line(board_t *map, int line)
{
    for (int i = 1; i < ROWS_MAP; i += 2)
    {
        memmove(&map->field[i][1], &map->field[i][0], COLS_MAP * sizeof(char));
        map->field[i][0] = map->field[i][COLS_MAP];
    }
}
