#include "brick_game/tetris/tetris.h"
// #include "brick_game/tetris/defines.h"
// #include "brick_game/tetris/objects.h"

#include <check.h>

#define	EXIT_FAILURE	1
#define	EXIT_SUCCESS	0

START_TEST(exit_test) {
  // board_t *field;
  tetramino_t tetramino;
  tetramino.type = 0;
    tetramino.variant = 0;
    get_tetramino(&tetramino);
  params_t *prms = getPrmsInstance();
  prms->tetramino = &tetramino;
  prms->map->field[1][1] = 1;
  // ck_assert_int_eq(, OK);
  // s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_move_down)
{
    tetramino_t tetramino;
    tetramino.type = 1;
    board_t board;
    init_board(&board);
    get_tetramino(&tetramino);
    params_t prms;
    prms.tetramino = &tetramino;
    movedown(&prms);

    ck_assert_int_eq(tetramino.point->x, 1);  // Пример
    ck_assert_int_eq(tetramino.point->x, 0);  // Пример
}
END_TEST



START_TEST(test_move_down2) {
    tetramino_t tetramino;
    tetramino.type = 1;
    board_t board;
    init_board(&board);
    get_tetramino(&tetramino);
    params_t prms;
    prms.tetramino = &tetramino;
    movedown(&prms);

    ck_assert_int_eq(tetramino.point->x, 1);  // Пример
    ck_assert_int_eq(tetramino.point->x, 0);  // Пример
    }
END_TEST

Suite *s21_create_matrix_suite(void) {
  Suite *suite = suite_create("s21_create_matrix");
  TCase *tc_core = tcase_create("core_of_create_matrix");
  tcase_add_test(tc_core, exit_test);
  tcase_add_test(tc_core, test_move_down);
  tcase_add_test(tc_core, test_move_down2);
  suite_add_tcase(suite, tc_core);

  return suite;
}

// Suite *s21_remove_matrix_suite(void) {
//   Suite *suite = suite_create("s21_remove_matrix");
//   TCase *tc_core = tcase_create("core_of_remove_matrix");
//   tcase_add_test(tc_core, remove_matrix_1);
//   tcase_add_test(tc_core, remove_matrix_2);
//   tcase_add_test(tc_core, remove_matrix_3);
//   suite_add_tcase(suite, tc_core);

//   return suite;
// }


void s21_suit_execution(Suite *suite, int *failed_count) {
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  *failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
}

int main(void) {
  int failed_count = 0;
  s21_suit_execution(s21_create_matrix_suite(), &failed_count);
  // s21_suit_execution(s21_remove_matrix_suite(), &failed_count);
  // s21_suit_execution(s21_eq_matrix_suite(), &failed_count);
  // s21_suit_execution(s21_sum_matrix_suite(), &failed_count);
  // s21_suit_execution(s21_sub_matrix_suite(), &failed_count);
  // s21_suit_execution(s21_mult_number_suite(), &failed_count);
  // s21_suit_execution(s21_mult_matrix_suite(), &failed_count);
  // s21_suit_execution(s21_transpose_suite(), &failed_count);
  // s21_suit_execution(s21_calc_complements_suite(), &failed_count);
  // s21_suit_execution(s21_determinant_suite(), &failed_count);
  // s21_suit_execution(s21_inverse_matrix_suite(), &failed_count);

  return failed_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}