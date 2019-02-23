/** \file menu.c
 * \brief Zawiera funkcje związane z menu pauzy i nowej gry.
 */

#include "menu.h"

int showPauseMenu(ALLEGRO_DISPLAY *window, ALLEGRO_FONT *fontText, ALLEGRO_FONT *fontScore, int level, int score)
{
    int width = al_get_display_width(window);                                                       //szerokość okna
    int height = al_get_display_height(window);                                                     //wysokość okna

    int menuWidth = width / 2;                                                                      //szerokość menu
    int menuHeight = height / 2;                                                                    //wysokośc menu
    int menuPositionX = width / 4;                                                                  //pozycja X menu
    int menuPositionY = height / 4;                                                                 //pozycja Y menu

    ALLEGRO_BITMAP *background = al_clone_bitmap(al_get_backbuffer(window));                        //zapisanie obrazu przedstawiającego aktualny wygląd okna

    int i;
    for(i=0; i<=menuHeight; ++i)                                                                    //pętla rozwijająca menu
    {
        al_draw_bitmap(background, 0, 0, 0);                                                        //rysowanie tła
        al_draw_filled_rounded_rectangle(menuPositionX, menuPositionY, menuPositionX + menuWidth, menuPositionY + i, 20, 20, al_map_rgba(140, 255, 200, 100));
                                                                                                    //rysowanie tła menu
        al_flip_display();                                                                          //odświeżenie obrazu
    }

    char textScore[10];                                                                             //tekst zawierający informację o wyniku gracza
    char textLevel[10];                                                                             //tekst zawierający informację o aktualnym poziomie
    sprintf(textScore, "%d", score);
    sprintf(textLevel, "%d", level);

    int textHeight = al_get_font_line_height(fontText);                                             //pobranie wysokości tekstu
    //----Wypisanie tektu w menu:
    al_draw_text(fontText, al_map_rgb(34, 77, 93), width / 2, 10 + menuPositionY, ALLEGRO_ALIGN_CENTER, "PAUZA");
    al_draw_text(fontText, al_map_rgb(34, 77, 93), menuPositionX + 10, 10 + menuPositionY + textHeight, ALLEGRO_ALIGN_LEFT, "Aktualny wynik:");
    al_draw_text(fontScore, al_map_rgb(34, 77, 93), menuPositionX + menuWidth - 10, 10 + menuPositionY + textHeight, ALLEGRO_ALIGN_RIGHT, textScore);
    al_draw_text(fontText, al_map_rgb(34, 77, 93), menuPositionX + 10, 10 + menuPositionY + (textHeight * 2), ALLEGRO_ALIGN_LEFT, "Poziom:");
    al_draw_text(fontScore, al_map_rgb(34, 77, 93), menuPositionX + menuWidth - 10, 10 + menuPositionY + (textHeight * 2), ALLEGRO_ALIGN_RIGHT, textLevel);
    al_flip_display();                                                                              //odświeżenie obrazu

    int result;                                                                                     //zmienna przechowująca wybraną przez użytkownika opcję menu
    const char *options[3];                                                                         //tablica z opcjami do wyświetlenia
    options[0] = "Kontynuuj";                                                                       //zapisanie opcji do tablicy
    options[1] = "Restart";
    options[2] = "Zamknij";
    result = showOptionsList(window, options, 3, fontText, menuPositionX, (menuPositionY + menuHeight) - 10 - (3 * textHeight), menuWidth);
                                                                                                    //pobranie wyboru gracza

    for(i=menuHeight; i>30; --i)                                                                    //pętla zwijająca menu
    {
        al_draw_bitmap(background, 0, 0, 0);                                                        //wyświetlenie tła
        al_draw_filled_rounded_rectangle(menuPositionX, menuPositionY, menuPositionX + menuWidth, menuPositionY + i, 20, 20, al_map_rgba(140, 255, 200, 100));
                                                                                                    //wyświetlenie tła menu
        al_flip_display();                                                                          //odświeżenie obrazu
    }

    al_destroy_bitmap(background);                                                                  //zwolnienie pamięci bitmapy
    return result;                                                                                  //zwrócenie wyboru gracza
}

int showNewGameMenu(ALLEGRO_DISPLAY *window, ALLEGRO_FONT *fontText, ALLEGRO_FONT *fontScore, int level, int score)
{
    int width = al_get_display_width(window);                                                       //szerokośc ekranu
    int height = al_get_display_height(window);                                                     //wysokość ekranu

    int menuWidth = width / 2;                                                                      //szerokość menu
    int menuHeight = height / 2;                                                                    //wysokość menu
    int menuPositionX = width / 4;                                                                  //pozycja X menu
    int menuPositionY = height / 4;                                                                 //pozycja Y menu

    ALLEGRO_BITMAP *background = al_clone_bitmap(al_get_backbuffer(window));                        //aktualna zawartość okna

    int i;
    for(i=0; i<=menuHeight; ++i)                                                                    //pętla roziwjająca menu
    {
        al_draw_bitmap(background, 0, 0, 0);
        al_draw_filled_rounded_rectangle(menuPositionX, menuPositionY, menuPositionX + menuWidth, menuPositionY + i, 20, 20, al_map_rgba(140, 255, 200, 100));
        al_flip_display();
    }

    char textScore[10];                                                                             //aktualny wynik
    char textLevel[10];                                                                             //aktualny poziom
    sprintf(textScore, "%d", score);
    sprintf(textLevel, "%d", level);

    int textHeight = al_get_font_line_height(fontText);                                             //wysokość tekstu
    //---wypisanie tekstu manu:
    al_draw_text(fontText, al_map_rgb(34, 77, 93), width / 2, 10 + menuPositionY, ALLEGRO_ALIGN_CENTER, "KONIEC GRY");
    al_draw_text(fontText, al_map_rgb(34, 77, 93), menuPositionX + 10, 10 + menuPositionY + textHeight, ALLEGRO_ALIGN_LEFT, "Wynik:");
    al_draw_text(fontScore, al_map_rgb(34, 77, 93), menuPositionX + menuWidth - 10, 10 + menuPositionY + textHeight, ALLEGRO_ALIGN_RIGHT, textScore);
    al_draw_text(fontText, al_map_rgb(34, 77, 93), menuPositionX + 10, 10 + menuPositionY + (textHeight * 2), ALLEGRO_ALIGN_LEFT, "Poziom:");
    al_draw_text(fontScore, al_map_rgb(34, 77, 93), menuPositionX + menuWidth - 10, 10 + menuPositionY + (textHeight * 2), ALLEGRO_ALIGN_RIGHT, textLevel);
    al_flip_display();                                                                              //odświeżenie obrazu

    int result;
    const char *options[2];                                                                         //lista opcji
    options[0] = "Nowa gra";
    options[1] = "Zamknij";
    result = showOptionsList(window, options, 2, fontText, menuPositionX, (menuPositionY + menuHeight) - 10 - (2 * textHeight), menuWidth);
                                                                                                    //pobranie wyboru użytkownika

    for(i=menuHeight; i>30; --i)                                                                    //pętla zwijająca menu
    {
        al_draw_bitmap(background, 0, 0, 0);
        al_draw_filled_rounded_rectangle(menuPositionX, menuPositionY, menuPositionX + menuWidth, menuPositionY + i, 20, 20, al_map_rgba(140, 255, 200, 100));
        al_flip_display();
    }

    al_destroy_bitmap(background);                                                                  //zwolnienie pamięci
    return result;
}

int showOptionsList(ALLEGRO_DISPLAY *window, const char *options[], int nOptions, ALLEGRO_FONT *font, int x, int y, int width)
{
    int selected = 0;                                                                               //aktualnie wybrana pozycja z listy
    ALLEGRO_KEYBOARD_STATE keyboard;                                                                //stan klawiatury
    ALLEGRO_BITMAP *background = al_clone_bitmap(al_get_backbuffer(window));                        //skopiowanie tłą

    int textHeight = al_get_font_line_height(font);                                                 //pobranie wysokości tekstu

    int i;
    double time = al_get_time();                                                                    //pobranie aktualnego czasu

    do{
        al_draw_bitmap(background, 0, 0, 0);                                                        //rysowanie tła
        for(i=0; i<nOptions; ++i)                                                                   //przeście przez wszystkie opcje
        {
            if(i == selected)                                                                       //jeśli aktualna opcja jest zaznaczona, rysowane jest pod nią tło
                al_draw_filled_rectangle(x + 40, y + (textHeight * i), x + width - 40, y +(textHeight * (i + 1)), al_map_rgb(189, 199, 126));
            al_draw_text(font, al_map_rgb(34, 77, 93), (width / 2) + x, y + (textHeight * i), ALLEGRO_ALIGN_CENTER, options[i]);
        }                                                                                           //wypisanie opcji
        al_flip_display();                                                                          //odświeżenie obrazu

        al_get_keyboard_state(&keyboard);                                                           //pobranie stanu klawiatury
        if(al_get_time() > time + 0.1)                                                              //jeśli upłynęła odpowiedni ilośc czasu od ostatniej zmiany zaznaczenia
        {
            if(al_key_down(&keyboard, ALLEGRO_KEY_DOWN))                                            //jeśli wciśnięto strzałkę w dół
            {
                selected++;                                                                         //zaznaczenie zmienia się na pozycję następną
                if(selected == nOptions)                                                            //jeśli zanaczona była ostatnia pozycja na liście
                    selected = 0;                                                                   //zaznacznie pierwszej pozycji na liście
            }
            else if(al_key_down(&keyboard, ALLEGRO_KEY_UP))                                         //jeśli wciśnięto strzałkę do góry
            {
                selected--;                                                                         //zaznaczenie poprzedniej opcji
                if(selected < 0)                                                                    //jeśli zaznaczona była pierwsza opcja
                    selected = nOptions - 1;                                                        //zaznaczenie ostatniej opcji menu
            }
            time = al_get_time();
        }
    }while(!al_key_down(&keyboard, ALLEGRO_KEY_ENTER));                                             //pętla powtarzana jest do czasu wciśnięcia ENTER (zatwierdzenia wyboru)
    al_destroy_bitmap(background);                                                                  //zwolnienie pamięci
    return selected;                                                                                //zwrócenie wybranej opcji
}
