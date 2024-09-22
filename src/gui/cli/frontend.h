#ifndef FRONTEND_H
#define FRONTEND_H

#include "../../brick_game/tetris/main.h"

/**
 * @file frontend.h Файл имеет основные функции для отрисовки поля игры,
 * тетрамино и статистики
 *
 */

/**
 * @brief Отображает основной интерфейс игры, включая игровое поле и HUD.
 *
 * Включает отображение максимального счета, текущего счета, уровня, времени
 * и тетромино, которое будет следовать.
 */
void PrintOverlay(void);

/**
 * @brief Рисует прямоугольник на экране с заданными координатами.
 *
 * @param top_y Координата Y верхней границы.
 * @param bottom_y Координата Y нижней границы.
 * @param left_x Координата X левой границы.
 * @param right_x Координата X правой границы.
 */
void PrintRectangle(int top_y, int bottom_y, int left_x, int right_x);

/**
 * @brief Выводит текущие игровые статистики на экран.
 *
 * @param stats Указатель на структуру с информацией об игре (GameInfo_t),
 * включающей максимальный счет, текущий счет и уровень.
 */
void PrintStats(GameInfo_t *stats);

/**
 * @brief Печатает игровое поле на экране.
 *
 * Анимация постепенного заполнения поля используется для эффекта.
 */
void PrintField();

/**
 * @brief Печатает игровое поле (Board_t) на экране, отображая блоки и пустые
 * клетки.
 *
 * @param map Структура игрового поля (Board_t), которая хранит состояние
 * клеток.
 */
void PrintBoard(Board_t map);

/**
 * @brief Отображает сообщение об окончании игры с итоговым счетом.
 *
 * @param stats Указатель на структуру с информацией об игре (GameInfo_t),
 * включающей текущий счет.
 */
void PrintGameOver(GameInfo_t *stats);

/**
 * @brief Отображает текущее тетромино на игровом поле.
 *
 * @param tetramino Текущая фигура тетромино (Tetramino_t), которая будет
 * отображена на экране.
 */
void PrintTetramino(Tetramino_t tetramino);

/**
 * @brief Очищает текущее тетромино с экрана.
 *
 * @param tetramino Текущая фигура тетромино (Tetramino_t), которая будет
 * очищена.
 */
void ClearTetramino(Tetramino_t tetramino);

/**
 * @brief Отображает следующее тетромино в дополнительном блоке.
 *
 * @param tetramino Текущая фигура тетромино (Tetramino_t) для получения
 * следующего.
 */
void PrintFrontNextTetr(Tetramino_t tetramino);

/**
 * @brief Отображает сообщение о паузе.
 */
void PrintPause();

/**
 * @brief Очищает сообщение о паузе.
 */
void ClearPause();
void UpdateTime(int hours, int minutes);
#endif