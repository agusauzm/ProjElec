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
#define MODE_NUMBER                     3
#define MODE_UPPER_CASE                 0
#define MODE_LOWER_CASE                 1
#define MODE_SYMBOLS                    2

/* Nombre de touches */
#define KEY_NUMBER                      39
#define KEY_BUFFER_LEN                  39

/* Taille d'une touche en pixels */
#define KEY_SMALL_LENGTH                55    /* longueur */
#define KEY_SMALL_HEIGHT                50    /* largeur */
#define KEY_DISTANCE                    10    /* distance entre les touches */
#define KEY_SMALLER_HEIGHT              30    /* largeur plus petite pour les dièses */

/* État d'une touche */
#define KEY_RELEASED                    0     /* la touche n'est pas appuyée */
#define KEY_PRESSED                     1     /* la touche est appuyée */

/* Structure d'une touche */
typedef struct
{
    uint8_t         id;
    uint8_t         status;
    uint16_t        posX;
    uint16_t        posY;
    uint8_t         dimX;
    uint8_t         dimY;
    int         value[MODE_NUMBER];
    uint32_t        color;
}   Key_TypeDef;

/* Structure du clavier */
typedef struct
{
    uint16_t        posX;
    uint16_t        posY;
    Key_TypeDef key[KEY_NUMBER];
    uint8_t         mode;    
    char            buffer[KEY_BUFFER_LEN];
}   Keyboard_TypeDef;

/* Fonctions du clavier sur l'écran */
uint8_t Keyboard_init(uint16_t x_value, uint16_t y_value);
uint8_t Keyboard_display_all(void);
uint8_t Key_display_normal(uint8_t id);
uint8_t Key_display_inverted(uint8_t id);
uint8_t Key_display_specials(uint8_t id);
uint8_t Keyboard_check(void);
uint8_t Keyboard_handler(char *prompt, char buffer[]);

#ifdef __cplusplus
}
#endif

/* Fin du fichier "keyboard.h" */
#endif
