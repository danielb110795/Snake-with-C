#ifndef MENU
#define MENU

/** \file menu.h
 * \brief Zawiera funkcje związane z menu pauzy i nowej gry.
 */

#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

/** \brief Wyświetlenie menu pauzy.
 *
 * \param window ALLEGRO_DISPLAY* okno programu
 * \param fontText ALLEGRO_FONT* czcionka do zapisu tekstu
 * \param fontScore ALLEGRO_FONT* czcionka do zapisu wyników
 * \param level int aktualny poziom
 * \param score int aktualny wynik
 * \return int wybrana opcja
 *
 */
int showPauseMenu(ALLEGRO_DISPLAY *window, ALLEGRO_FONT *fontText, ALLEGRO_FONT *fontScore, int level, int score);

/** \brief Menu rozpoczęcia nowej gry.
 *
 * \param window ALLEGRO_DISPLAY* okno programu
 * \param fontText ALLEGRO_FONT* czcionka do zapisu tekstu
 * \param fontScore ALLEGRO_FONT* czcionka do zapisu wyników
 * \param level int aktualny poziom
 * \param score int aktualny wynik
 * \return int wybrana opcja
 *
 */
int showNewGameMenu(ALLEGRO_DISPLAY *window, ALLEGRO_FONT *fontText, ALLEGRO_FONT *fontScore, int level, int score);

/** \brief Funkcja pozwalająca użytkownikowi na wybranie opcji z listy.
 * \details Funkcja jest wykorzystywana przez manu pauzy i nowej gry.
 *
 * \param window ALLEGRO_DISPLAY* okno programu
 * \param options[] const char* lista opcji do wyświetlenia
 * \param nOptions int liczba opcji do wyświetlenia
 * \param font ALLEGRO_FONT* czcionka, za pomocą której wypisane będa opcje
 * \param x int pozycja X wyświetlenia listy
 * \param y int pozycja Y wyświetlenia listy
 * \param width int szerokość listy
 * \return int wybrana opcja
 *
 */
int showOptionsList(ALLEGRO_DISPLAY *window, const char *options[], int nOptions, ALLEGRO_FONT *font, int x, int y, int width);

#endif
