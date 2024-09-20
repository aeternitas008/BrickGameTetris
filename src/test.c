#include <check.h>

#include "brick_game/tetris/backend.h"
#include "brick_game/tetris/main.h"

// Тест инициализации доски
START_TEST(test_init_board) {
  board_t map;
  init_board(&map);

  for (int x = 0; x < 20; x++) {
    for (int y = 0; y < 10; y++) {
      ck_assert_int_eq(map.field[x][y], 0);
    }
  }
}
END_TEST

// Тест добавления тетрамино на доску
START_TEST(test_add_tetramino_on_board) {
  board_t map;
  tetramino_t tetramino;
  position pos = {0, 0};

  init_board(&map);
  tetramino.point = &pos;
  tetramino.figure[0][0] = 1;
  tetramino.figure[0][1] = 0;
  tetramino.figure[1][0] = 1;
  tetramino.figure[1][1] = 1;

  params_t prms = {.tetramino = &tetramino, .map = &map};

  add_tetramino_on_board(&prms);

  ck_assert_int_eq(map.field[0][0], 1);
  ck_assert_int_eq(map.field[1][0], 1);
  ck_assert_int_eq(map.field[1][1], 1);
}
END_TEST

// Тест проверки тетрамино на столкновения
START_TEST(test_check_tetramino_collision) {
  board_t map;
  tetramino_t tetramino;
  position pos = {17, 0};

  init_board(&map);
  get_array_figures(tetramino.array_figures);
  tetramino.type = 1;
  tetramino.variant = 1;
  get_tetramino(&tetramino);
  tetramino.point = &pos;
  // tetramino.figure[0][1] = 1;
  // tetramino.figure[1][1] = 1;
  // tetramino.figure[2][1] = 1;
  // tetramino.figure[3][1] = 1;

  params_t prms = {.tetramino = &tetramino, .map = &map};

  int result = check_tetramino(prms, tetramino);
  ck_assert_int_eq(result, 1);  // Ожидаем, что столкновение произойдет
}
END_TEST

// Тест проверки и удаления полной линии
START_TEST(test_check_and_remove_full_line) {
  board_t map;
  init_board(&map);

  // Заполняем третью линию
  for (int y = 0; y < 10; y++) {
    map.field[2][y] = 1;
  }

  params_t prms = {.map = &map};
  state_t state = MOVING;
  prms.state = &state;
  GameInfo_t stats = {0};
  prms.stats = &stats;

  ck_assert_int_eq(stats.score, 0);
  check(&prms);

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

// Главная функция для запуска тестов
Suite *tetris_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Tetris");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_init_board);
  tcase_add_test(tc_core, test_add_tetramino_on_board);
  tcase_add_test(tc_core, test_check_tetramino_collision);
  tcase_add_test(tc_core, test_check_and_remove_full_line);
  // tcase_add_test(tc_core, test_has_full_line);

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
