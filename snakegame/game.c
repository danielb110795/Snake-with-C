/** \file game.c
 * \brief Zawiera funkcje kontrolujące grę.
 */

#include "game.h"

void newApple(struct Field *position)
{
    int rnd = rand() % 10;                                                                  //losowanie liczby z zakresu 0-9
    position->x = rnd;                                                                      //nadanie losowej wartośc X
    rnd = rand() % 10;                                                                      //losowanie liczby z zakresu 0-9
    position->y = rnd;                                                                      //nadanie losowej wartości Y
}

void updateDirection(ALLEGRO_KEYBOARD_STATE keyboard, struct Direction *direction, struct Direction prevDirection)
{
    if(al_key_down(&keyboard, ALLEGRO_KEY_UP) && prevDirection.y != 1)                      //sprawdzenie czy wciśnięto strzałkę w górę i czy w poprzednim ruchu wąż nie poruszał się do góry
    {
        direction->y = -1;                                                                  //zapisanie nowego kierunku ruchu
        direction->x = 0;
    }
    else if(al_key_down(&keyboard, ALLEGRO_KEY_DOWN) && prevDirection.y != -1)              //sprawdzenie czy wciśnięto strzałkę w dół i czy w poprzednim ruchu wąż nie poruszał się w dół ekranu
    {
        direction->y = 1;                                                                   //zapisanie nowego kierunku ruchu
        direction->x = 0;
    }
    else if(al_key_down(&keyboard, ALLEGRO_KEY_LEFT) && prevDirection.x != 1)               //sprawdzenie czy wciśnięto strzałkę w lewo i czy w poprzednim ruchu wąż nie poruszał się w lewą stronę ekranu
    {
        direction->y = 0;                                                                   //zapisanie nowego kierunku ruchu
        direction->x = -1;
    }
    else if(al_key_down(&keyboard, ALLEGRO_KEY_RIGHT) && prevDirection.x != -1)             //sprawdzenie czy wciśnięto strzałkę w prawo i czy w poprzednim ruchu wąż nie poruszał się w prawą stronę ekranu
    {
        direction->y = 0;                                                                   //zapisanie nowego kierunku ruchu
        direction->x = 1;
    }
}

void game(ALLEGRO_DISPLAY *mainWindow)
{
    ALLEGRO_SAMPLE *soundPoint, *soundNextLevel, *soundGameOver;                                        //dźwięki
    ALLEGRO_FONT *fontPoints, *fontText;                                                                //czcionki
    ALLEGRO_BITMAP *imageApple, *imageBackground, *imageSHead, *imageSBody, *imageSCorner, *imageSTail; //grafiki używane w grze

    //---wczytywanie potrzebnych zasobów i zakończenie funkcji w przypadku niepowodzenia
    soundPoint = al_load_sample("resources/s.ogg");
    if(!soundPoint)
        return;
    soundNextLevel = al_load_sample("resources/next level.ogg");
    if(!soundNextLevel)
        return;
    soundGameOver = al_load_sample("resources/game over.ogg");
    if(!soundGameOver)
        return;
    fontPoints = al_load_ttf_font("resources/DJB.ttf", 24, 0);
    if(!fontPoints)
        return;
    fontText = al_load_ttf_font("resources/cm.ttf", 32, 0);
    if(!fontText)
        return;
    imageApple = al_load_bitmap("resources/a.png");
    if(!imageApple)
        return;
    imageBackground = al_load_bitmap("resources/background.png");
    if(!imageBackground)
        return;
    imageSHead = al_load_bitmap("resources/1.png");
    if(!imageSHead)
        return;
    imageSBody = al_load_bitmap("resources/2.png");
    if(!imageSBody)
        return;
    imageSCorner = al_load_bitmap("resources/3.png");
    if(!imageSCorner)
        return;
    imageSTail = al_load_bitmap("resources/4.png");
    if(!imageSTail)
        return;
    //---

    ALLEGRO_KEYBOARD_STATE keyboard;                                                                    //stan klawiatury

    srand(time(NULL));

    const int fieldSize = 50;                                                                           //rozmiar pola na planszy (w px)
    const int applesPerLevel = 10;                                                                      // ilość jabłek jakie należy zebrać, by przejść do kolejnego poziomu
    const float defaultMoveDelay = 0.5;                                                                 //domyślna prędkość gry

    bool endGame = false;                                                                               //informacja, czy należy zakończyć program
    bool gameOver = false;                                                                              //informacja, czy należy zakończyć aktualną rozgrywkę
    bool restart = false;                                                                               //informacja, czy należy rozpocząć grę od początku
    bool grow = false;                                                                                  //informacja, czy należy zwiększyć rozmiar węża
    int level;                                                                                          //aktualny poziom
    int score;                                                                                          //aktualna ilość punktów
    int applesColected;                                                                                 //ilość zebranych jabłek
    float moveDelay;                                                                                    //aktualna prędkość gry

    struct Direction snakeDirection;                                                                    //aktualny kierunek ruchu
    struct Direction snakePrevDirection;                                                                //kierunke poprzednio wykonanego ruchu
    struct SnakePart *head;                                                                             //wskaźnik na początek węża

    struct Field applePosition;                                                                         //pozycja jabłka na planszy

    while(!endGame)                                                                                     //powtarzane do momentu zakończenia programu
    {
        head = newSnake();                                                                              //stworzenie nowego węża
        snakeDirection.x = 0;                                                                           //początkowo brak wybranego kierunku
        snakeDirection.y = 0;
        snakePrevDirection.x = 0;                                                                       //początkowo brak poprzedniego kierunku
        snakePrevDirection.y = 0;
        newApple(&applePosition);                                                                       //wylosowanie nowej pozycji jabłka
        level = 1;                                                                                      //gracz zaczyna od poziomu 1
        score = 0;                                                                                      //gracz zaczyna z zerowym wynikiem
        applesColected = 0;                                                                             //wyzerowanie ilości zebranych jabłek
        grow = false;                                                                                   //wąż nie powinien roznąć do moemntu zebrania jabłka
        moveDelay = defaultMoveDelay;                                                                   //prędkośc gry ustawiona na domyślną
        double time = al_get_time();                                                                    //pobranie aktualnego czasu
        while(!gameOver)                                                                                //powtarzane do czasu zakończenie aktualnej rozgrywki (błędu gracza_
        {
            al_get_keyboard_state(&keyboard);                                                           //pobranie aktualnego stanu klawiatury
            updateDirection(keyboard, &snakeDirection, snakePrevDirection);                             //aktualizacja kierunku ruchu
            al_draw_bitmap(imageBackground, 0, 0, 0);                                                   //wyrysowanie tła
            drawScoreBoard(score, level, (applesColected * 100) / applesPerLevel, fontText, fontPoints);//rysowanie tablicy wyników
            al_draw_bitmap(imageApple, (applePosition.x * fieldSize) + 40, (applePosition.y * fieldSize) + 40, 0);  //rysowanie jabłka
            drawSnake(head, imageSHead, imageSBody, imageSCorner, imageSTail);                          //rysowanie węża
            al_flip_display();                                                                          //odświeżenie ekranu
            if(al_get_time() > time + moveDelay)                                                        //jeśli należy wykonać ruch (upłynęła odpowiednia ilość czasu od ostatniego ruchu)
            {
                if(moveSnake(head, snakeDirection, grow))                                               //przesunięcie węża
                {
                    grow = false;                                                                       //jeśli należało powiększyć węża, wykonano to podczas ruchu
                    snakePrevDirection.x = snakeDirection.x;                                            //zapisanie aktualnego kierunku ruchu
                    snakePrevDirection.y = snakeDirection.y;
                    if(head->position.x == applePosition.x && head->position.y == applePosition.y)      //jeśli wąż znajduje się na polu z jabłkiem
                    {
                        newApple(&applePosition);                                                       //wylosowanie nowej pozycji jabłka
                        score += 10 * level;                                                            //powększenie wyniku
                        if(++applesColected == applesPerLevel)                                          //jeśli zebrano odpowiednią ilośc jabłek by awansować
                        {
                            al_play_sample(soundNextLevel, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); //dźwięku awansu
                            level++;                                                                    //zwiększenie poziomu
                            applesColected = 0;                                                         //wyzerowanie ilości zebranych jabłek
                            shrinkSnake(head);                                                          //zmniejszenie węża do rozmiarów początkowych
                            moveDelay -= moveDelay / 10;                                                //przyspieszenie ruchu węża
                        }
                        else                                                                            //jeśli jeszcze nie należy awansować
                        {
                            al_play_sample(soundPoint, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);     //dźwięk zebrania jabłka
                            grow = true;                                                                //zapisanie informacji o konieczności zwiększenia rozmiaru
                        }
                    }
                    time = al_get_time();                                                               //pobranie aktualnego czasu
                }
                else                                                                                    //jeśli funkcja ruchu zwróciała false
                {
                    gameOver = true;                                                                    //zakończenie gry
                    al_play_sample(soundGameOver, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);          //dźwięk końca gry
                }
            }
            if(al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE))                                              //jeśli wciśnięto esc
            {
                int decision = showPauseMenu(mainWindow, fontText, fontPoints, level, score);           //wyświetlenie menu pauzy i pobranie decyzji gracza
                if(decision == 1)                                                                       //jeśli wybrano restart
                {
                    gameOver = true;
                    restart = true;
                }
                else if(decision == 2)                                                                  //jeśli wybrano zakończenie gry
                {
                    gameOver = true;
                    endGame = true;
                }
            }
        }
        if(!endGame && !restart)                                                                        //jeśli gracz nie wybrał opcji zakończenia gry, ani restartu
            if(showNewGameMenu(mainWindow, fontText, fontPoints, level, score) == 1)                    //wyświetlenie menu nowej gry i sprawdzenie czy gracz wybrał opcję zakończenia gry
                endGame = true;
        gameOver = restart = false;
        clearSnake(head);                                                                               //usunięcie węża
    }

    //---zwolnienie zasobów:
    al_destroy_sample(soundPoint);
    al_destroy_sample(soundNextLevel);
    al_destroy_sample(soundGameOver);
    al_destroy_font(fontPoints);
    al_destroy_font(fontText);
    al_destroy_bitmap(imageApple);
    al_destroy_bitmap(imageBackground);
    al_destroy_bitmap(imageSHead);
    al_destroy_bitmap(imageSBody);
    al_destroy_bitmap(imageSCorner);
    al_destroy_bitmap(imageSTail);
}

void drawScoreBoard(int score, int level, int progres, ALLEGRO_FONT *fontText, ALLEGRO_FONT *fontScore)
{
    char textScore[10];                                                                                 //wynik gracza
    char textLevel[10];                                                                                 //aktualny poziom
    char textProgres[10];                                                                               //procent do awansu
    sprintf(textScore, "%d", score);
    sprintf(textLevel, "%d", level);
    sprintf(textProgres, "%d%%", progres);

    int textHeight = al_get_font_line_height(fontText);
    al_draw_filled_rounded_rectangle(562, 42, 782, 207, 20, 20, al_map_rgba(145, 145, 119, 255));
    al_draw_filled_rounded_rectangle(560, 40, 780, 205, 20, 20, al_map_rgba(189, 199, 126, 255));

    al_draw_text(fontText, al_map_rgb(34, 77, 93), 570, 60, ALLEGRO_ALIGN_LEFT, "Wynik:");
    al_draw_text(fontScore, al_map_rgb(34, 77, 93), 770, 60, ALLEGRO_ALIGN_RIGHT, textScore);
    al_draw_text(fontText, al_map_rgb(34, 77, 93), 570, 60 + textHeight, ALLEGRO_ALIGN_LEFT, "Poziom:");
    al_draw_text(fontScore, al_map_rgb(34, 77, 93), 770, 60 + textHeight, ALLEGRO_ALIGN_RIGHT, textLevel);
    al_draw_text(fontText, al_map_rgb(34, 77, 93), 570, 60 + textHeight * 2, ALLEGRO_ALIGN_LEFT, "Kolejny poziom:");
    al_draw_text(fontScore, al_map_rgb(34, 77, 93), 770, 60 + textHeight * 2, ALLEGRO_ALIGN_RIGHT, textProgres);
}
