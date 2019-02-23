#ifndef SNAKE
#define SNAKE

/** \file snake.h
 * \brief Zawiera funkcje związane z wężem.
 */

#include <allegro5/allegro_primitives.h>

#include "types.h"

/** \brief Fragment węża
 *  \details Fragment kolejki reprezentującej węża.
 *   Zawiera informację o pozycji fragmentu na planszy oraz wskaźnik do następnego i poprzedniego elementu.
 */
struct SnakePart
{
    struct SnakePart *prev;/**< Wskaźnik na poprzedni element. */
    struct SnakePart *next;/**< Wskaźnik na następny element. */
    struct Field position;/**< Pozycja na planszy. */
};

/** \brief Funkcja rysująca węża na planszy.
 *
 * \param head SnakePart* początek węża (kolejki)
 * \param imageHead ALLEGRO_BITMAP* grafiki przedstawiajęce kolejne części węża
 * \return void
 *
 */
void drawSnake(struct SnakePart *head, ALLEGRO_BITMAP *imageHead, ALLEGRO_BITMAP *imageBody, ALLEGRO_BITMAP *imageCorner, ALLEGRO_BITMAP *imageTail);

/** \brief Funkcja przesuwająca węża w podanym kierunku.
 *
 * \param head SnakePart* głowa węża
 * \param direction Direction kierunk ruchu węża
 * \param grow bool informacja czy wąż powinien zostać powiększony
 * \return bool informacja czy przesunięcie było możliwe (czy wąż napotkał ścianę lub siebie samego)
 *
 */
bool moveSnake(struct SnakePart *head, struct Direction direction, bool grow);

/** \brief Zmniejszenie węża do początkowego rozmiaru.
 *  \details Wykorzystywane podczas przejścia do następnego poziomu.
 *
 * \param head SnakePart* początek węża
 * \return void
 *
 */
void shrinkSnake(struct SnakePart *head);

/** \brief Usunięcie węża (wyczyszczenie kolejki)
 * \details Funkcja zwraca pamięć zajmowaną przez elementy kolejki.
 *
 * \param head SnakePart* początek węża
 * \return void
 *
 */
void clearSnake(struct SnakePart *head);

/** \brief Stowrzenie węża.
 * \details Stworzenie głowy oraz ogona.
 *
 * \return wskaźnik na głowę stworzonego węża
 *
 */
struct SnakePart* newSnake();

#endif
