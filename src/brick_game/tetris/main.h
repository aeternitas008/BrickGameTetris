#ifndef MAIN_H
#define MAIN_H

#include <ncurses.h>

#include "defines.h"

/**
 * @file main.h хэдер хранит основные объекты и вспомогательные структуры игры и
 * объединяет бэк с фронтом
 *
 */

/**
 * @brief Структура, представляющая координаты на игровом поле.
 */
typedef struct {
  int x; /**< Координата X */
  int y; /**< Координата Y */
} Position;

/**
 * @brief Структура, представляющая тетромино, включая его позицию, тип и
 * варианты вращения.
 */
typedef struct {
  Position *point; /**< Указатель на позицию тетромино на игровом поле */
  int type; /**< Тип тетромино (например, I, O, T и т.д.) */
  int variant; /**< Вариант вращения тетромино (0-3) */
  unsigned int figure[4][4]; /**< Текущая форма тетромино */
  unsigned int array_figures[19][4]
                            [4]; /**< Массив всех возможных фигур тетромино */
} Tetramino_t;

/**
 * @brief Структура, представляющая игровое поле.
 */
typedef struct {
  int field[ROWS_MAP][COLS_MAP]; /**< Поле, хранящее состояние клеток (занято
                                    или пусто) */
} Board_t;

/**
 * @brief Перечисление действий пользователя.
 */
typedef enum {
  Start,     /**< Начать игру */
  Pause,     /**< Поставить игру на паузу */
  Terminate, /**< Завершить игру */
  Left,      /**< Движение влево */
  Right,     /**< Движение вправо */
  Up,        /**< Движение вверх или поворот */
  Down,      /**< Движение вниз */
  Action     /**< Выполнение действия */
} UserAction_t;

/**
 * @brief Перечисление состояний игры.
 */
typedef enum {
  START = 0, /**< Начало игры */
  SPAWN,     /**< Появление новой фигуры */
  MOVING,    /**< Фигура движется */
  SHIFTING,  /**< Сдвиг или поворот фигуры */
  GAMEOVER,  /**< Конец игры */
  EXIT_STATE /**< Выход из игры */
} State_t;

/**
 * @brief Структура, содержащая информацию об игре.
 */
typedef struct {
  int **field; /**< Двумерный массив игрового поля */
  int **next; /**< Двумерный массив для отображения следующего тетромино */
  int score;  /**< Текущий счет игрока */
  int high_score; /**< Максимальный достигнутый счет */
  int level;      /**< Текущий уровень */
  int speed;      /**< Скорость падения фигур */
  int pause;      /**< Состояние паузы */
} GameInfo_t;

/**
 * @brief Структура, содержащая параметры игры.
 */
typedef struct GameParams {
  GameInfo_t *stats; /**< Указатель на структуру с информацией об игре */
  State_t *state; /**< Указатель на текущее состояние игры */
  Board_t *map; /**< Указатель на структуру игрового поля */
  struct timespec *time; /**< Указатель на структуру времени */
  Tetramino_t *tetramino; /**< Указатель на текущее тетромино */
  int sig; /**< Сигнальное значение (для обработки сигналов) */
  int hold; /**< Флаг удержания текущего тетромино */
} Params_t;

// For ubuntu if need to realise clock_gettime
// #define _POSIX_C_SOURCE 199309L
//  #define CLOCK_REALTIME 0
// int clock_gettime(int clk_id, struct timespec *tp) {
//   struct timeval now;
//   int rv = gettimeofday(&now, NULL);
//   if (rv == 0) {
//     tp->tv_sec = now.tv_sec;
//     tp->tv_nsec =
//         now.tv_usec * 1000;  // Конвертируем микросекунды в наносекунды
//   }
//   return rv;
// }

#endif