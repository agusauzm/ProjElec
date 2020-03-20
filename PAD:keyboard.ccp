/*
 *******************************************************************************
 * Keyboard Library virtual keyboard for touch screen display on demo
 * Découverte STM32F746NG
 *
 * Fichier "keyboard.ccp"
 *******************************************************************************
 */
/*Ajouter le fichier header*/
#include "keyboard.h"
#include "USBMIDI.h"
#include "MIDIMessage.h"
/* Les structures de la clavature et de l’écran tactile */
Keyboard_TypeDef keyboard;
TS_StateTypeDef tScreen;
USBMIDI midi(Highspeed_Interface,0x0700,0x0101,0x0001);
/*Fonction pour travailler avec le clavier à l’écran */
/* Initialisation et affichage du clavier */
uint8_t Keyboard_init(uint16_t  x_value, uint16_t   y_value)
{
    uint8_t i;
    /* Les coordonnées du coin supérieur gauche du clavier sur l’écran servent de "point
       de référence" pour déterminer l’emplacement de tous les autres éléments */
    keyboard.posX = x_value;
    keyboard.posY = y_value;
    /* La valeur par défaut sur le clavier est une disposition anglaise en MAJ. */
    keyboard.mode = MODE_UPPER_CASE;
    /* Bloc d’initialisation pour les clés standard */
    /* Initialisation des coordonnées des touches du clavier pour la première rangée */
    for (i = 0; i < 5; i++) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 5 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * i;
        keyboard.key[i].posY = keyboard.posY + 3;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    /* Valeurs ASCII de chaque touche de la première rangée pour différentes
       dispositions du clavier
    */
    keyboard.key[0].value[0] = '4C';
    keyboard.key[0].value[1] = 'C4';
    keyboard.key[0].value[2] = '1';

    keyboard.key[1].value[0] = '4D';
    keyboard.key[1].value[1] = 'D4';
    keyboard.key[1].value[2] = '2';

    keyboard.key[2].value[0] = '4E';
    keyboard.key[2].value[1] = 'E4';
    keyboard.key[2].value[2] = '3';

    keyboard.key[3].value[0] = '4F';
    keyboard.key[3].value[1] = 'F4';
    keyboard.key[3].value[2] = '4';

    keyboard.key[4].value[0] = '4G';
    keyboard.key[4].value[1] = 'G4';
    keyboard.key[4].value[2] = '5';
    /* Initialisation des coordonnées des touches du clavier pour la rangée du milieu */
    for (i = 5; i < 8; i++) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 5 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * (i - 3) - 95;
        keyboard.key[i].posY = keyboard.posY + 3 + KEY_SMALL_HEIGHT + KEY_DISTANCE;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    /* Valeurs ASCII de chaque touche de la rangée du milieu pour différentes
       dispositions du clavier
    */
    keyboard.key[5].value[0] = '4A';
    keyboard.key[5].value[1] = 'A4';
    keyboard.key[5].value[2] = '6';

    keyboard.key[6].value[0] = '4B';
    keyboard.key[6].value[1] = 'B4';
    keyboard.key[6].value[2] = '7';

    keyboard.key[7].value[0] = '5C';
    keyboard.key[7].value[1] = 'C5';
    keyboard.key[7].value[2] = '8';
    /* Nous dessinons le clavier à l’écran */
    Keyboard_display_all();
    return 0;
}
/* Dessiner le clavier à l’écran */
uint8_t Keyboard_display_all(void)
{
    uint8_t i;
    /* Nous obtenons la valeur associée à la couleur de l’arrière-plan de l’écran */
    uint32_t back_color = BSP_LCD_GetBackColor();
    /* Peindre l’écran entier avec la couleur de l’arrière-plan */
    BSP_LCD_Clear(back_color);
    /* Nous dessinons toutes les touches sur le clavier */
    for (i = 0; i < KEY_NUMBER; i++) {
        Key_display_normal(i);
    }
    return 0;
}
/* Dessin d’une seule touche de clavier à l’écran */
uint8_t Key_display_normal(uint8_t id)
{
    /* Nous obtenons la couleur de l’arrière-plan de l’écran et la couleur de la police */
    uint32_t back_color = BSP_LCD_GetBackColor();
    uint32_t text_color = BSP_LCD_GetTextColor();
    /* Changer les couleurs et peindre l’endroit pour la touche sur l’écran avec la couleur de l’arrière-plan */
    BSP_LCD_SetTextColor(back_color);
    BSP_LCD_SetBackColor(text_color);
    BSP_LCD_FillRect(keyboard.key[id].posX, keyboard.key[id].posY, keyboard.key[id].dimX, keyboard.key[id].dimY);
    /* Retournez les mêmes valeurs de couleur de l’arrière-plan de l’écran et de la couleur de police */
    BSP_LCD_SetTextColor(text_color);
    BSP_LCD_SetBackColor(back_color);
    /* Dessiner un cadre autour de la touche et fermer le pixel dans le coin inférieur droit */
    BSP_LCD_DrawRect(keyboard.key[id].posX, keyboard.key[id].posY, keyboard.key[id].dimX, keyboard.key[id].dimY);
    BSP_LCD_DrawPixel(keyboard.key[id].posX + keyboard.key[id].dimX, keyboard.key[id].posY + keyboard.key[id].dimY, text_color);
    /* Afficher la valeur de la touche dans la disposition actuelle du clavier. */
    BSP_LCD_DisplayChar(keyboard.key[id].posX + 8, keyboard.key[id].posY + 8, keyboard.key[id].value[keyboard.mode]);
    BSP_LCD_DisplayChar(keyboard.key[id].posX + 20, keyboard.key[id].posY + 8, keyboard.key[id].value[keyboard.mode+1]);
    return 0;
}
/* Dessin d’une seule touche de clavier à l’écran (couleur inversée) */
uint8_t Key_display_inverted(uint8_t id)
{
    uint32_t back_color = BSP_LCD_GetBackColor();
    uint32_t text_color = BSP_LCD_GetTextColor();
    /* Remplir la place pour la touche à l’écran avec la couleur de la police */
    BSP_LCD_FillRect(keyboard.key[id].posX, keyboard.key[id].posY, keyboard.key[id].dimX, keyboard.key[id].dimY);
    /* Changer de couleur et afficher la valeur de la touche dans la disposition actuelle du clavier */
    BSP_LCD_SetTextColor(back_color);
    BSP_LCD_SetBackColor(text_color);
    BSP_LCD_DisplayChar(keyboard.key[id].posX + 8, keyboard.key[id].posY + 8, keyboard.key[id].value[keyboard.mode]);
    BSP_LCD_DisplayChar(keyboard.key[id].posX + 20, keyboard.key[id].posY + 8, keyboard.key[id].value[keyboard.mode+1]);
    /* Retour de la couleur de fond d’écran précédente et la couleur de police */
    BSP_LCD_SetTextColor(text_color);
    BSP_LCD_SetBackColor(back_color);
    return 0;
}
/* Vérifier l’entrée sur le clavier à l’écran */
uint8_t Keyboard_check(void)
{
    uint8_t i;
    uint8_t j;
    /* Vérification de l’état du "conducteur" de l’écran tactile */
    BSP_TS_GetState(&tScreen);
    /* Si on appuie sur l'ecran */
    if (tScreen.touchDetected) {
        for (i = 0; i < KEY_NUMBER; i++) {
            /* Si les coordonnées tactiles se trouvent dans les limites de l’une des touches non pressés, +/- 4 pixels */
            if (((tScreen.touchX[0] >= keyboard.key[i].posX - 4) && (tScreen.touchX[0] < keyboard.key[i].posX + keyboard.key[i].dimX + 4)) &&
                    ((tScreen.touchY[0] >= keyboard.key[i].posY - 4) && (tScreen.touchY[0] < keyboard.key[i].posY + keyboard.key[i].dimY + 4)) &&
                    (keyboard.key[i].status == KEY_RELEASED)) {
                /* Dessinez la bonne clé dans la couleur inversée */
                Key_display_inverted(i);
                /* Si l'appui a déjà été fixée sur une autre clé, "appuyez-la" et redessiner */
                for (j = 0; j < KEY_NUMBER; j++) {
                    if (keyboard.key[j].status == KEY_PRESSED) {
                        Key_display_normal(j);
                        keyboard.key[j].status = KEY_RELEASED;
                    }
                }
                /* Changer l’état de la touche pour laquelle l'appui a été enregistré */
                keyboard.key[i].status = KEY_PRESSED;
                /* Réinitialisez l’état du conducteur de l’écran tactile */
                BSP_TS_ResetTouchData(&tScreen);
            }
        }
    }
/* S’il n’y a pas de contact, vérifiez l’état de chaque touche, peut-être qu'un appui
   est déja en cours et devrait être traité comme une entrée */
    for (i = 0; i < KEY_NUMBER; i++) {
        /* Si la clé touche est pressée, "appuyez-la" et redessiner */
        if (keyboard.key[i].status == KEY_PRESSED) {
            Key_display_normal(i);
            keyboard.key[i].status = KEY_RELEASED;
            BSP_TS_ResetTouchData(&tScreen);
            /* On retourne la valeur de l'entrée */
            return keyboard.key[i].value[2];
        }
    }
    return 0;
}
/* Gestionnaire d’entrée de clavier à l’écran */
uint8_t Keyboard_handler(char *prompt, char buffer[])
{
    uint8_t key;
    /* Vérifiez s’il y a un nouveau clic */
    key = Keyboard_check();
        if(key == '1')
    {
        midi.write(MIDIMessage::NoteOn(60));
    }
    else if(key == '2')
    {
        midi.write(MIDIMessage::NoteOn(62));
    }
    else if(key == '3')
    {
        midi.write(MIDIMessage::NoteOn(64));
    }
    else if(key == '4')
    {
        midi.write(MIDIMessage::NoteOn(65));
    }
    else if(key == '5')
    {
        midi.write(MIDIMessage::NoteOn(67));
    }
    else if(key == '6')
    {
        midi.write(MIDIMessage::NoteOn(69));
    }
    else if(key == '7')
    {
        midi.write(MIDIMessage::NoteOn(71));
    }
    else if(key == '8')
    {
        midi.write(MIDIMessage::NoteOn(72));
    }
    else
    {
        midi.write(MIDIMessage::NoteOff(60));
        midi.write(MIDIMessage::NoteOff(62));
        midi.write(MIDIMessage::NoteOff(64));
        midi.write(MIDIMessage::NoteOff(65));
        midi.write(MIDIMessage::NoteOff(67));
        midi.write(MIDIMessage::NoteOff(69));
        midi.write(MIDIMessage::NoteOff(71));
        midi.write(MIDIMessage::NoteOff(72));
    }
    /* Retourner la valeur de la dernière touche pressée */
    return key;
}
