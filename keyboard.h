/*
 *******************************************************************************
 * Bibliothèque du clavier virtuel pour l'affichage avec l'écran tactile sur la
 * carte STM32F746NG Discovery
 * Fichier "keyboard.h"
 *******************************************************************************
 */

/* Définition pour éviter l'inclusion multiple */
#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

/* Dans le cas d'utilisation en C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* Inclusion de string.h pour avoir la fonction strlen() */
#include <string.h>

/* Inclusion des bibliothèques pour travailler avec l'écran tactile et son contrôleur */
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"

/* Définitions */
/* Modes du clavier */
#define MODE_NUMBER                     4
#define MODE_UPPER_CASE                 0
#define MODE_LOWER_CASE                 1
#define MODE_SYMBOLS                    2

/* Nombre de touches */
#define KEY_NUMBER                      112
#define KEY_BUFFER_LEN                  112

/* Taille d'une touche en pixels */
#define KEY_SMALL_LENGTH                70
#define KEY_SMALL_HEIGHT                70
#define KEY_DISTANCE                    25
#define KEY_SMALLER_HEIGHT              50

/* État d'une touche */
#define KEY_RELEASED                    0
#define KEY_PRESSED                     1

/* Structure d'une touche */
typedef struct
{
    int         id;
    int         status;
    uint16_t        posX;
    uint16_t        posY;
    int         dimX;
    int         dimY;
    int         value[MODE_NUMBER];
    int             content[MODE_NUMBER];
}   Key_TypeDef;

/* Structure du clavier */
typedef struct
{
    uint16_t        posX;
    uint16_t        posY;
    Key_TypeDef key[KEY_NUMBER+1];
    int         mode;    
    char            buffer[KEY_BUFFER_LEN+1];
}   Keyboard_TypeDef;

/* Fonctions du clavier sur l'écran */
void Keyboard_define(void);
int Keyboard_init(uint16_t x_value, uint16_t y_value);
int Keyboard_display_all(void);
int Key_display_normal(int id);
int Key_display_inverted(int id);
int Key_display_specials(int id);
int Keyboard_check(void);
void Keyboard_handler();

#ifdef __cplusplus
}
#endif

/* Fin du fichier "keyboard.h" */
#endif
