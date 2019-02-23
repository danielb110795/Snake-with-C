#ifndef GAME
#define GAME

/** \file game.h
 * \brief Zawiera funkcje kontrolujące grę.
 */

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "snake.h"
#include "menu.h"
#include "types.h"

/** \brief Funkcja losująca pozycję jabłka na planszy.
 *
 * \param position struct Field* wskaźnik na strukturę przechowującą pozycję jabłka
 * \return void
 *
 */
void newApple(struct Field *position);

/** \brief Funkcja pobierająca nowy kierunek ruchu.
 * \details Funkcja definiuje nowy kierunek ruchu na podstawie wciśniętego klawisza. Funkcja uwzględnia wcześniejszy
 * kierunek poruszania, by uniemożliwić zawrócenie.
 * Możliwe jest kilkukrotne pobranie kierunku pomiędzy poszczególnymi ruchami węża - wykonany zostanie ruch w najpóźniej podanym kierunku.
 * W prevDirection zapisany jest kierunek ruchu w poprzednim ruchu węża, a nie ostatnio pobrany kierunek.
 *
 * \param keyboard ALLEGRO_KEYBOARD_STATE stan klawitury
 * \param direction struct Direction* wskaźnik, w którym zapisany zostanie nowy kierunek
 * \param prevDirection struct Direction kierunek, w jakim poruszał się wąż podczas poprzedniego ruchu.
 * \return void
 *
 */
void updateDirection(ALLEGRO_KEYBOARD_STATE keyboard, struct Direction *direction, struct Direction prevDirection);

/** \brief Funkcja kontrolująca przebieg gry.
 *
 * \param mainWindow ALLEGRO_DISPLAY* okno programu
 * \return void
 *
 */
void game(ALLEGRO_DISPLAY *mainWindow);

/** \brief Funkcja rysująca na ekranie informacje o aktualnym pstępie gry
 *
 * \param score int aktualny wynik
 * \param level int aktualny poziom
 * \param progres int postęp aktualnego poziomu (w procentach)
 * \param fontText ALLEGRO_FONT* czcionka do tekstu
 * \param fontScore ALLEGRO_FONT* czcionka służąca do wypisywania wyniku
 * \return void
 *
 */
void drawScoreBoard(int score, int level, int progres, ALLEGRO_FONT *fontText, ALLEGRO_FONT *fontScore);

#endif
