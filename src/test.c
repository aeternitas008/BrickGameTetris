#include <check.h>

#include "brick_game/tetris/backend.h"
#include "brick_game/tetris/main.h"

// Инициализация доски
START_TEST(test_init_board) {
  Board_t map;
  InitBoard(&map);

  for (int x = 0; x < 20; x++) {
    for (int y = 0; y < 10; y++) {
      ck_assert_int_eq(map.field[x][y], 0);
    }
  }
}
END_TEST

// Инициализация доски
START_TEST(test_variation_tetramino) {
  Board_t map;
  Tetramino_t tetramino;
  Position pos = {17, 0};

  InitBoard(&map);
  GetArrayFigures(tetramino.array_figures);
  tetramino.type = 2;
  tetramino.variant = 1;
  GetTetramino(&tetramino);
  tetramino.type = 3;
  GetTetramino(&tetramino);
  tetramino.type = 4;
  GetTetramino(&tetramino);
  tetramino.type = 5;
  GetTetramino(&tetramino);
  tetramino.type = 6;
  GetTetramino(&tetramino);
  tetramino.point = &pos;

  Params_t prms = {.tetramino = &tetramino, .map = &map};
  int result = CheckTetramino(prms, tetramino);
  int result2 = CheckNewVariant(prms);
  ck_assert_int_eq(result, 0);  
  ck_assert_int_eq(result2, 0);  

TetraminoPosInit(tetramino.point);
  ck_assert_int_eq(tetramino.point->x, -1);  
  ck_assert_int_eq(tetramino.point->y, 3);  
}
END_TEST

// Инициализация доски
START_TEST(test_states_and_moves) {
  Board_t map;
  Tetramino_t tetramino;
  Position pos = {15, 0};

  InitBoard(&map);
  GetArrayFigures(tetramino.array_figures);
  tetramino.variant = 1;
  tetramino.type = 6;
  GetTetramino(&tetramino);
  tetramino.point = &pos;
  GameInfo_t stats = {0};
    State_t state = MOVING;
  Params_t prms = {.map = &map, .tetramino = &tetramino, .hold = 0, .state = &state, .stats = &stats};
  MoveDown(&prms);
  MoveLeft(&prms);
  MoveRight(&prms);
  int result = CheckTetramino(prms, tetramino);
  int result2 = CheckNewVariant(prms);
  ck_assert_int_eq(result, 0);  
  ck_assert_int_eq(result2, 0);  

  prms.hold = 1;
  pos.y = 7;
  MoveRight(&prms);
  MoveRight(&prms);
  MoveDown(&prms);
  int result3 = CheckTetramino(prms, *prms.tetramino);
  ck_assert_int_eq(result3, 1);

  MoveDown(&prms);

TetraminoPosInit(tetramino.point);
  TurnRight(&prms);
  ck_assert_int_eq(tetramino.point->x, -1);  
  ck_assert_int_eq(tetramino.point->y, 3); 

}
END_TEST


// Инициализация доски
START_TEST(test_game_over) {
  Board_t map;
  Tetramino_t tetramino;
  Position pos = {15, 0};
  InitBoard(&map);
  GetArrayFigures(tetramino.array_figures);
  tetramino.variant = 1;
  tetramino.type = 6;
  GetTetramino(&tetramino);
  tetramino.point = &pos;
  GameInfo_t stats = {0};
    State_t state = MOVING;
  Params_t prms = {.map = &map, .tetramino = &tetramino, .hold = 0, .state = &state, .stats = &stats};
  prms.hold = 1;
  int y = 5;
  for (int x = 19; x > 1; x--) {
    map.field[x][y] = 1;
  }
  Spawn(&prms);
  MoveDown(&prms);
  MoveDown(&prms);
  Spawn(&prms);
  ck_assert_int_eq(*prms.state, GAMEOVER);

// StartGame(&prms);
//   ck_assert_int_eq(*prms.state, SPAWN);
//   ck_assert_int_eq(tetramino.point->x, -1);  
//   ck_assert_int_eq(tetramino.point->y, 3); 

//getsignal

//updatecurrentstate

//shfting

//startgame


//gamepause

//statsinit

//userinput
}
END_TEST

// Добавление тетрамино на доску
START_TEST(test_add_tetramino_on_board) {
  Board_t map;
  Tetramino_t tetramino;
  Position pos = {0, 0};

  InitBoard(&map);
  tetramino.point = &pos;
  tetramino.figure[0][0] = 1;
  tetramino.figure[0][1] = 0;
  tetramino.figure[1][0] = 1;
  tetramino.figure[1][1] = 1;

  Params_t prms = {.tetramino = &tetramino, .map = &map};

    AddTetraminoOnBoard(&prms);

  ck_assert_int_eq(map.field[0][0], 1);
  ck_assert_int_eq(map.field[1][0], 1);
  ck_assert_int_eq(map.field[1][1], 1);
}
END_TEST

// Тест проверки тетрамино на столкновения
START_TEST(test_check_tetramino_collision) {
  Board_t map;
  Tetramino_t tetramino;
  Position pos = {17, 0};

  InitBoard(&map);
  GetArrayFigures(tetramino.array_figures);
  tetramino.type = 1;
  tetramino.variant = 1;
  GetTetramino(&tetramino);
  tetramino.point = &pos;

  Params_t prms = {.tetramino = &tetramino, .map = &map};

  int result = CheckTetramino(prms, tetramino);
  ck_assert_int_eq(result, 1);  
}
END_TEST

// Тест проверки и удаления полной линии
START_TEST(test_check_and_remove_full_line) {
  Board_t map;
  InitBoard(&map);

  // Заполняем третью линию
  for (int y = 0; y < 10; y++) {
    map.field[2][y] = 1;
  }

  Params_t prms = {.map = &map};
  State_t state = MOVING;
  prms.state = &state;
  GameInfo_t stats = {0};
  prms.stats = &stats;

  ck_assert_int_eq(stats.score, 0);
  Check(&prms);

  ck_assert_int_eq(stats.score, 100);
  ck_assert_int_eq(*prms.state, SHIFTING);
  ck_assert_int_eq(map.field[2][0], 0);
  ck_assert_int_eq(map.field[2][1], 0);
  ck_assert_int_eq(map.field[2][2], 0);
  ck_assert_int_eq(map.field[2][3], 0);
  ck_assert_int_eq(map.field[2][4], 0);
  ck_assert_int_eq(map.field[2][5], 0);
  ck_assert_int_eq(map.field[2][6], 0);
  ck_assert_int_eq(map.field[2][7], 0);
  ck_assert_int_eq(map.field[2][8], 0);
  ck_assert_int_eq(map.field[2][9], 0);
}
END_TEST

Suite *tetris_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Tetris");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_init_board);
  tcase_add_test(tc_core, test_add_tetramino_on_board);
  tcase_add_test(tc_core, test_check_tetramino_collision);
  tcase_add_test(tc_core, test_check_and_remove_full_line);
  tcase_add_test(tc_core, test_variation_tetramino);
  tcase_add_test(tc_core, test_states_and_moves);
  tcase_add_test(tc_core, test_game_over);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = tetris_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
