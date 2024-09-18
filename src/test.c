#include <check.h>
#include "brick_game/tetris/tetr_backend.h"  // Замените на правильный заголовочный файл

#define EXIT_SUCCESS 1
#define EXIT_FAILURE 0

// Тест инициализации доски
START_TEST(test_init_board)
{
    board_t map;
    init_board(&map);

    // Проверка, что все поля доски инициализированы в 0
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 10; y++) {
            ck_assert_int_eq(map.field[x][y], 0);
        }
    }
}
END_TEST

// Тест добавления тетрамино на доску
START_TEST(test_add_tetramino_on_board)
{
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

// Тест проверки полной линии
START_TEST(test_has_full_line)
{
    board_t map;
    init_board(&map);

    // Заполняем строку для проверки
    for (int y = 0; y < 10; y++) {
        map.field[5][y] = 1;
    }

    int result = has_full_line(&map, 5); // Предполагается, что эта функция проверяет линию 5
    ck_assert_int_eq(result, 1);  // Ожидаем, что функция вернет 1 (линия заполнена)
}
END_TEST

// Главная функция для запуска тестов
Suite* tetris_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Tetris");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_init_board);
    tcase_add_test(tc_core, test_add_tetramino_on_board);
    tcase_add_test(tc_core, test_has_full_line);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
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
