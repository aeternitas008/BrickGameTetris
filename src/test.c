#include <ncurses.h>
#include <locale.h>

#define MVPRINTW(y, x, ...) mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)

int main() {
    // Устанавливаем локаль для поддержки Юникода
    // setlocale(LC_CTYPE, "");

    // Инициализация ncurses
    initscr();
    // cbreak();
    // noecho();
    // keypad(stdscr, TRUE);

    // Определяем координаты вывода
    int BOARDS_BEGIN = 0;
    int BOARD_M = 10;

    // Выводим символ "▢" используя mvprintw
    MVPRINTW(15, BOARD_M + 4, "▢");

    // Обновляем экран
    // refresh();

    // Ждем ввода
    getch();

    // Завершаем работу ncurses
    endwin();

    return 0;
}