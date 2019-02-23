/** \file snake.c
 * \brief Zawiera funkcje związane z wężem.
 *
 */

#include "snake.h"

void drawSnake(struct SnakePart *head, ALLEGRO_BITMAP *imageHead, ALLEGRO_BITMAP *imageBody, ALLEGRO_BITMAP *imageCorner, ALLEGRO_BITMAP *imageTail)
{
    ALLEGRO_BITMAP *image;                                                          //pomocniczy wskaźnik na bitmapę
    float rotateRadian;                                                             //rotacja jaką należy nałożyć na obraz przed wyświetleniem

    rotateRadian = 0;                                                               //domyślnie brak rotacji
    if(head->next->position.y < head->position.y)                                   //nadanie odpowiedniej rotacji, zależnej od pozycji następnego elementu węża
        rotateRadian = 1.5707963268;
    else if(head->next->position.y > head->position.y)
        rotateRadian = -1.5707963268;
    else if(head->next->position.x > head->position.x)
        rotateRadian = 3.1415926536;

    al_draw_rotated_bitmap(imageHead, 25, 25, 65 + (head->position.x * 50), 65 + (head->position.y * 50), rotateRadian, 0);
                                                                                    //wyświtlenie głowy
    struct SnakePart *currentPart;                                                  //wskaźnik na aktualnie wyświetlany element
    currentPart = head;                                                             //rozpoczęcie od głowy
    while(currentPart->next != NULL)                                                //pętla powtarzana do momentu gdy nie będzie elementu znajdującego się za aktualnym (momentu dotarcia do ostatniego elementu)
    {
        currentPart = currentPart->next;                                            //przejście do następnego elementu
        rotateRadian = 0;                                                           //domyślnie brak rotacji
        if(currentPart->next == NULL)                                               //jeśli aktualny element jest ostatnim
        {
            if(currentPart->prev->position.y > currentPart->position.y)             //nadanie odpowiednej rotacji zależnaej od pozycji względem poprzedniego elementu
                rotateRadian = 1.5707963268;
            else if(currentPart->prev->position.y < currentPart->position.y)
                rotateRadian = -1.5707963268;
            else if(currentPart->prev->position.x < currentPart->position.x)
                rotateRadian = 3.1415926536;
            al_draw_rotated_bitmap(imageTail, 25, 25, 65 + (currentPart->position.x * 50), 65 + (currentPart->position.y * 50), rotateRadian, 0);
                                                                                    //rysowanie bitmapy
        }
        else                                                                        //jeśli aktualny element nie jest ostatnim
        {
            if(currentPart->next->position.y == currentPart->prev->position.y)      //jeśli poprzedni i następny element są w linii poziomej
                image = imageBody;                                                  //wybranie odpowiedniego obrazu do wyświetlenia
            else if(currentPart->next->position.x == currentPart->prev->position.x) //jeśli poprzedni i następny element są w linii pionowej
            {
                image = imageBody;                                                  //wybranie odpowiedniego obrazu
                rotateRadian = 1.5707963268;                                        //nadanie odpowiedniej rotacji
            }
            else                                                                    //jeśli aktualny element jest punktem zgięcia węża
            {
                image = imageCorner;                                                //wybranie obrazu do wyświetlenia
                if((currentPart->next->position.x < currentPart->position.x && currentPart->prev->position.y > currentPart->position.y) || (currentPart->next->position.y > currentPart->position.y && currentPart->prev->position.x < currentPart->position.x))
                    rotateRadian = 1.5707963268;                                    //nadanie odpowiedniej rotazji zależnie od położenia sąsiednich elementów
                if((currentPart->next->position.y < currentPart->position.y && currentPart->prev->position.x < currentPart->position.x) || (currentPart->next->position.x < currentPart->position.x && currentPart->prev->position.y < currentPart->position.y))
                    rotateRadian = 3.1415926536;
                if((currentPart->next->position.x > currentPart->position.x && currentPart->prev->position.y < currentPart->position.y) || (currentPart->next->position.y < currentPart->position.y && currentPart->prev->position.x > currentPart->position.x))
                    rotateRadian = -1.5707963268;
            }
            al_draw_rotated_bitmap(image, 25, 25, 65 + (currentPart->position.x * 50), 65 + (currentPart->position.y * 50), rotateRadian, 0);
                                                                                    //wyświetlenie obrazu
        }
    }
    return;
}

bool moveSnake(struct SnakePart *head, struct Direction direction, bool grow)
{
    int newPositionX;                                                                           //pozycja głowy na osi X po przesunięciu
    int newPositionY;                                                                           //pozycja głowy na osi X po przesunięciu
    newPositionX = head->position.x + direction.x;                                              //zapisanie nowje pozycji pierwszego elementu
    newPositionY = head->position.y + direction.y;
    if(newPositionX < 0 || newPositionX > 9)                                                    //jeśli nowa pozycja znajduje się poza planszą
        return false;                                                                           //zwrócenie informacji o niepowodzeniu
    if(newPositionY < 0 || newPositionY > 9)                                                    //jeśli nowa pozycja znajduje się poza planszą
        return false;                                                                           //zwrócenie informacji o niepowodzeniu

    if(direction.x == 0 && direction.y == 0)                                                    //jeśli nie nadano jeszcze kierunku ruchu
        return true;

    struct SnakePart *currentPart = head;                                                       //wskaźnik na kolejne elementy węza
    while(currentPart->next != NULL)                                                            //przejście przez kolejne elementy
    {
        if(currentPart->position.x == newPositionX && currentPart->position.y == newPositionY)  //jeśli element znajduje się na pozycji, na którą planowano przesunąć węża
            return false;                                                                       //zwrócnie informacji o niepowodzeniu
        currentPart = currentPart->next;                                                        //przejście do następnego elementu
    }

    if(grow)                                                                                    //jeśli podczas ruchu wąż ma zostać powiększony
    {
        struct SnakePart *newPart = malloc(sizeof *newPart);                                    //alokacja pamięci
        newPart->position.x = currentPart->prev->position.x;                                    //nadanie  nowemu elemntowi odpowiedniej pozycji na planszy
        newPart->position.y = currentPart->prev->position.y;
        newPart->prev = currentPart->prev;                                                      //włączenie nowego elementu do kolejki
        newPart->next = currentPart;
        currentPart->prev->next = newPart;
        currentPart->prev = newPart;
        currentPart = newPart->prev;
    }

    while(currentPart->prev != NULL)                                                            //do czasu dotarcia do początkowego elementu
    {
        currentPart->position.x = currentPart->prev->position.x;                                //przeniesienie aktualnego elementu na miejsce elementu poprzedzającego
        currentPart->position.y = currentPart->prev->position.y;
        currentPart = currentPart->prev;                                                        //przejście do poprzedniego elementu
    }
    head->position.x += direction.x;                                                            //przesunięcie głowy węża w odpowiednim kierunku
    head->position.y += direction.y;
    return true;                                                                                //informacja o poprawnym przesunięciu węża
}

void shrinkSnake(struct SnakePart *head)
{
    struct SnakePart *currentPart = head->next;                                                 //przejście do drugiego elementu węża
    struct Field tailPosition;                                                                  //pozycja na jakiej powinien się znaleźć ogon
    tailPosition = currentPart->position;                                                       //zapisanie pozycji drugiego elementu (na której powinien zostać umieszczony ogon
    while(currentPart->next != NULL)                                                            //do momentu dotarcia do ostatniego elementu
    {
        currentPart = currentPart->next;                                                        //przejście do kolejnego elementu
        free(currentPart->prev);                                                                //zwolnienie pamięci zajmowanej przez poprzedni element
    }
    head->next = currentPart;
    currentPart->prev = head;
    currentPart->position = tailPosition;                                                       //nadanie ogonowi właściwej pozycji
}

void clearSnake(struct SnakePart *head)
{
    struct SnakePart *currentPart = head;
    while(currentPart->next != NULL)                                                            //przejście przez wszystkie elementy
    {
        currentPart = currentPart->next;                                                        //przejście do następnego elementu
        free(currentPart->prev);                                                                //zwolnienie pamięci zajmowanej przez poprzedni elemet
    }
    free(currentPart);                                                                          //zwolnienie pamięci zajmowanej przez ostatni element
}

struct SnakePart* newSnake()
{
    struct SnakePart *head = malloc(sizeof *head);                                              //alokacja pamęci na głowę
    head->position.x = 1;                                                                       //nadanie głowie domyślnej pozycji
    head->position.y = 0;
    head->prev = NULL;
    head->next = malloc(sizeof head->next);                                                     //alokacja pamięci na ogon
    head->next->position.x = 0;                                                                 //nadanie ogonowi domyślnej pozycji
    head->next->position.y = 0;
    head->next->prev = head;
    head->next->next = NULL;
    return head;                                                                                //zwrócenie wskaźnika na głowę stworzonego węża
}
