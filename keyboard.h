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
/* Modes du clavier / Gammes */
#define MODE_NUMBER              4
#define NOTE                     0
#define GAMME_3                  1
#define GAMME_4                  2
#define GAMME_5                  3

/* Nombre de touches */
#define KEY_NUMBER                      15

/* Taille d'une touche en pixels */
#define KEY_SMALL_LENGTH                70 //Longueur
#define KEY_SMALL_HEIGHT                70 //Hauteur
#define KEY_DISTANCE                    25 //Distance entre les touches

/* État d'une touche */
#define KEY_RELEASED                    0 //Touche relachée
#define KEY_PRESSED                     1 //Touche appuyée

/* Structure d'une touche */
typedef struct
{
    uint8_t         id;     //valeur unique d'identifiaction de chaque touche 
    uint8_t         status; //le status de la touche qui indique si elle est relachée ou enfoncée
    uint16_t        posX;   //coordonnée x de la touche
    uint16_t        posY;   //coordonnée y de la touche
    uint8_t         dimX;   // largeur de la touche
    uint8_t         dimY;   // hauteur de la touche
    uint8_t         value[MODE_NUMBER]; //contient le caractère associée à l'appelation de la note (C,D,E,etc)
    uint8_t         content[MODE_NUMBER]; //contient le caractère à afficher à côté de la lettre précédente 
                                        //pour distinguer la gamme dans laquelle on se situe (3,4,5,etc)
}   Key_TypeDef;


/* Structure du clavier */
typedef struct
{
    uint16_t        posX;   //coordonnée x de l'origine du bloc des touches
    uint16_t        posY;   //coordonnée y de l'origine du bloc des touches
    Key_TypeDef key[KEY_NUMBER]; //structure précédente
    uint8_t         mode;   //contient la gamme actuelle/ sélectionnée
}   Keyboard_TypeDef;

/* Fonctions du clavier sur l'écran */
uint8_t Keyboard_init(uint16_t x_value, uint16_t y_value); /* Initialisation et affichage du clavier */
uint8_t Keyboard_display_all(void);         /* Dessiner le clavier à l’écran */
uint8_t Key_display_normal(uint8_t id);     /* Dessin d’une seule touche de clavier à l’écran */
uint8_t Key_display_inverted(uint8_t id);   /* Dessin d’une seule touche de clavier à l’écran (couleur inversée) */
uint8_t Keyboard_check(void);               /* Vérifier l’entrée sur le clavier à l’écran */
void Keyboard_handler();                    /* Vérifier l’entrée sur le clavier à l’écran */

#ifdef __cplusplus
}
#endif

/* Fin du fichier "keyboard.h" */
#endif
