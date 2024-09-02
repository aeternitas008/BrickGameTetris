#include <stdlib.h>

#include "../inc/objects.h"
#include "../inc/tetr_backend.h"


void get_tetramino(tetramino_t *tetramino) {
  int key = 0;
  if (tetramino->type == 1) {
    key = tetramino->variant % 2 + 1;
  } else if (tetramino->type == 2) {
    key = tetramino->variant % 2 + 3;
  } else if (tetramino->type == 3) {
    key = tetramino->variant % 2 + 5;
  } else if (tetramino->type == 4) {
    key = tetramino->variant + 7;
  } else if (tetramino->type == 5) {
    key = tetramino->variant + 11;
  } else if (tetramino->type == 6) {
    key = tetramino->variant + 15;
  }
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      tetramino->figure[x][y] = tetramino->array_figures[key][x][y];
    }
  }
}

void get_array_figures(unsigned int origin[19][4][4]) {
  printf("Inside get_matrix\n");
  unsigned int matrix[19][4][4] = {
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},

      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},

      {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},

      {{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}},

      {{0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}},

      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}},

      {{0, 0, 0, 1}, {0, 0, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}},

      {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}},

      {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}},

      {{0, 0, 0, 1}, {0, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},

      {{0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
      // J 11
      {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}},

      {{0, 0, 1, 1}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},

      {{0, 1, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},

      {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
      // T 15
      {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}},

      {{0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}},

      {{0, 0, 1, 0}, {0, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},

      {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
  };
  for (int n = 0; n < 19; n++) {
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        origin[n][x][y] = matrix[n][x][y];
      }
    }
  }
}


int check_new_variant(params_t prms) {
  tetramino_t tetramino_test = *prms.tetramino;
  tetramino_test.variant = (tetramino_test.variant + 1) % 4;
  get_tetramino(&tetramino_test);
  int result = check_tetramino(prms, tetramino_test);
  return result;
}

int check_tetramino(params_t prms, tetramino_t tetramino) {
  int result = 0;
  for(int x = 0; x < 4 && result == 0; x++) {
    for(int y = 0; y < 4 && result == 0; y++) {
      if (tetramino.figure[x][y] == 1 &&
          (tetramino.point->y + y > 9 
          || tetramino.point->y + y < 0 
          || tetramino.point->x + x < 0
          || tetramino.point->x + x > 19
          || prms.map->field[tetramino.point->x + x]
                           [tetramino.point->y + y] == 1)) {
        result = 1;
      }
    }
  }
  return result;
}

void init_board(board_t *map) {
  for (int x = 0; x < 20; x++) {
    for (int y = 0; y < 10; y++) {
      map->field[x][y] = 0;
    }
  }
}

void add_tetramino_on_board(params_t *prms) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (prms->tetramino->figure[x][y] == 1) {
        prms->map->field[prms->tetramino->point->x + x]
                        [prms->tetramino->point->y + y] = 1;
      }
    }
  }
}


int lvlproc(board_t *map, game_stats_t *stats) {
  // timeout(INITIAL_TIMEOUT - stats->speed * 15);

  // char levelname[LEVELNAME_MAX + 1] = {0};

  // sprintf(levelname, LEVEL_DIR "%d.txt", stats->level);

  // FILE *level = fopen(levelname, "r");

  int rc = SUCCESS;

  // if (level) {
  //   for (int i = 0; i < ROWS_MAP && !rc; i++) {
  //     if (fgets(map->field[i], COLS_MAP + 2, level) == NULL)
  //       rc = ERROR;
  //     else
  //       map->field[i][strcspn(map->field[i], "\n")] = '\0';
  //   }
  //   fclose(level);
  // } else
  //   rc = ERROR;

  return rc;
}

void add_proggress(board_t *map) {
  // int position = 0;

  // for (; map->finish[position] == '0'; position++) ;

  // for (int progress_cnt = BOARD_M / ; progress_cnt > 0; progress_cnt--)
  //     map->finish[position++] = '0';
}

bool check_finish_state(position *frog, board_t *map) {
  bool rc = FALSE;

  if (frog->y == 1) rc = TRUE;

  return rc;
}

bool check_level_compl(board_t *map) {
  bool rc = TRUE;
  for (int i = 0; i < BOARD_M && rc; i++) {
  }
  // if (map->finish[i] != '0')
  //     rc = FALSE;

  return rc;
}

bool check_collide(position *tetramino_pos, board_t *map) {
  bool rc = FALSE;

  if (tetramino_pos->y > MAP_PADDING &&
      tetramino_pos->y < ROWS_MAP + MAP_PADDING + 1 &&
      map->field[tetramino_pos->y - MAP_PADDING - 1][tetramino_pos->x - 1] ==
          ']')
    rc = TRUE;

  return rc;
}

void tetraminopos_init(position *tetramino_pos) {
  tetramino_pos->x = TETRSTART_X;
  tetramino_pos->y = TETRSTART_Y;
}

void fill_finish(char *finish_line) {
  for (int i = 0; i < BOARD_M; i++) finish_line[i] = ' ';

  finish_line[BOARD_M] = '\0';
}

void stats_init(game_stats_t *stats) {
  char *fname = "meta.txt";
  int N = 256;
  char buffer[N];
  FILE *fp = fopen(fname, "r");
  if (fp != NULL) {
    fgets(buffer, N, fp);
    char *score = strchr(buffer, ':');
    stats->high_score = atoi(++score);
    fgets(buffer, N, fp);
    char *level = strchr(buffer, ':');
    stats->level = atoi(++level);
    fclose(fp);
  } else {
    FILE *file = fopen(fname, "w");
    fprintf(file, "score:0\nlevel:1");
    fclose(file);
    stats->high_score = 0;
    stats->level = 1;
  }
  stats->level = 1;
  MVPRINTW(3, BOARD_M + 8, "%05d", stats->high_score);
  MVPRINTW(11, BOARD_M + 11, "%02d", stats->level);
  MVPRINTW(23, BOARD_M + 8, "%s", stats->current_time);
  stats->speed = 1;
  stats->score = 0;
  stats->won = FALSE;
}
void new_stats_init(game_stats_t *stats) {
  char *fname = "meta.txt";
  // int N = 256;
  // char buffer[N];
  // FILE *fp = fopen(fname, "r");
  // if (fp != NULL) {
  //   fgets(buffer, N, fp);
  //   char *score = strchr(buffer, ':');
  //   stats->high_score = atoi(++score);
  //   fgets(buffer, N, fp);
  //   char *level = strchr(buffer, ':');
  //   stats->level = atoi(++level);
  //   fclose(fp);
  // } else {
  if (stats->score > stats->high_score) {
    stats->high_score = stats->score;
    FILE *file = fopen(fname, "w");
    fprintf(file, "score:%d\nlevel:%d", stats->score, stats->level);
    fclose(file);
  }
  MVPRINTW(3, BOARD_M + 8, "%05d", stats->high_score);
  MVPRINTW(7, BOARD_M + 8, "%05d", stats->score);
  MVPRINTW(11, BOARD_M + 11, "%02d", stats->level);
}

// переписать свой код удаления линии на этот
void remove_line(board_t *map, int line) {
  for (int i = 1; i < ROWS_MAP; i += 2) {
    memmove(&map->field[i][1], &map->field[i][0], COLS_MAP * sizeof(char));
    map->field[i][0] = map->field[i][COLS_MAP];
  }
}

