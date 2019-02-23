#ifndef TYPES
#define TYPES

/** \file types.h
 * \brief Definicje dodatkowych typów.
 */

/** \brief Struktura reprezuntojąca pole na planszy.
 */
struct Field
{
    int x;/**< pozycja na osi X */
    int y;/**< pozycja na osi Y */
};

/** \brief Struktura reprezentujaca kierunek ruchu.
 */
struct Direction
{
    int x;/**< przesunięcie na osi X */
    int y;/**< przesunięcie na osi Y */
};

#endif
