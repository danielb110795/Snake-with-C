#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>

#include "game.h"

/** \brief Inicjalizacja bibliotki i potrzebnych modułów.
 *
 * \return bool Informacja czy inicjalizacja przebiegła pomyślnie.
 *
 */
bool initAllegro()
{
    if(!al_init())                          //inicjalizacja Allegro
        return false;
    if(!al_install_keyboard())              // instalacja klawiatury
        return false;
    if(!al_init_ttf_addon())                //inicjalizacja obsługi formatu ttf
        return false;
    if(!al_init_image_addon())              //inicjalizacja obsługi grafiki
        return false;
    if(!al_init_primitives_addon())         // inicjalizacja modułu rysowania kształtów
        return false;
    if(!al_install_audio())                 //instalacja obsługi dźwięku
        return false;
    if(!al_init_acodec_addon())             //inicjalizacja dźwięku
        return false;
    if(!al_reserve_samples(3))              //zarezerwowanie możliwości załadowania 3 sampli
        return false;

    return true;                            //jeśli funkcja dotała do tego miejsca zwraca prawdę
}

/** \brief Główna funkcja programu.
 *
 * \return int Wynik działania zwracany do systemu.
 *
 */
int main()
{
    if(!initAllegro())                                          //sprawdzenie czy inicjalizacja się powiodła
        return -1;
    ALLEGRO_DISPLAY *mainWindow = al_create_display(800, 580);  //stworzenie okna programu
    al_set_window_title(mainWindow, "Snake");                   //ustawienie tytułu okna

    game(mainWindow);                                           //rozpoczęcie gry

    al_destroy_display(mainWindow);                             //zwolnienie pamięci wykorzystywanej przez okno programu
    return 0;                                                   //Zwrócenie do sywtemu informacji o poprawnym zakończeniu działania.
}

/*! \mainpage Gra Snake
 *
 * \section goal Cel gry
 *
 * Zadaniem gracza jest sterowanie poruszającym się po ekranie wężem, tak by unikać zderzenia z przeszkodami,
 * bądź samym sobą oraz zbierać pojawiające się na ekranie jabłka.
 *
 * \section run Uruchomienie gry
 *
 * Rozpoczęcie gry możliwe jest poprzez uruchomienie pliku wykonywalnego „Snake.exe”.
 *
 */
