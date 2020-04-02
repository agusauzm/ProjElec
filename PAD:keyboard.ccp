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

/* Liste couleurs possibles */
uint32_t keycolorlist[40] = {LCD_COLOR_BLUE,LCD_COLOR_GREEN,LCD_COLOR_RED,LCD_COLOR_CYAN,LCD_COLOR_MAGENTA,LCD_COLOR_YELLOW,LCD_COLOR_LIGHTBLUE,LCD_COLOR_LIGHTGREEN,LCD_COLOR_LIGHTRED,LCD_COLOR_LIGHTCYAN,LCD_COLOR_LIGHTMAGENTA,LCD_COLOR_LIGHTYELLOW,LCD_COLOR_DARKBLUE,LCD_COLOR_DARKGREEN,LCD_COLOR_DARKRED,LCD_COLOR_DARKCYAN,LCD_COLOR_DARKMAGENTA,LCD_COLOR_DARKYELLOW,LCD_COLOR_BROWN,LCD_COLOR_ORANGE,LCD_COLOR_BLUE,LCD_COLOR_GREEN,LCD_COLOR_RED,LCD_COLOR_CYAN,LCD_COLOR_MAGENTA,LCD_COLOR_YELLOW,LCD_COLOR_LIGHTBLUE,LCD_COLOR_LIGHTGREEN,LCD_COLOR_LIGHTRED,LCD_COLOR_LIGHTCYAN,LCD_COLOR_LIGHTMAGENTA,LCD_COLOR_LIGHTYELLOW,LCD_COLOR_DARKBLUE,LCD_COLOR_DARKGREEN,LCD_COLOR_DARKRED,LCD_COLOR_DARKCYAN,LCD_COLOR_DARKMAGENTA,LCD_COLOR_DARKYELLOW,LCD_COLOR_BROWN,LCD_COLOR_ORANGE};

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
    for (i = 0; i < 7; i++) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 5 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * i;
        keyboard.key[i].posY = keyboard.posY + 42;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    for (i = 7; i < 14; i++) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 5 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * (i-7);
        keyboard.key[i].posY = keyboard.posY + 132;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    for (i = 14; i < 21; i++) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 5 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * (i-14);
        keyboard.key[i].posY = keyboard.posY + 222;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    for (i = 21; i < 27; i++) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 30 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * (i-21);
        keyboard.key[i].posY = keyboard.posY + 5;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALLER_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    for (i = 27; i < 33; i++) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 30 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * (i-27);
        keyboard.key[i].posY = keyboard.posY + 97;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALLER_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    for (i = 33; i < 39; i++) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 30 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * (i-33);
        keyboard.key[i].posY = keyboard.posY + 187;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALLER_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    /* Valeurs ASCII de chaque touche de la première rangée pour différentes
       dispositions du clavier
    */
    keyboard.key[0].value[0] = 'C';
    keyboard.key[0].value[1] = '3';
    keyboard.key[0].value[2] = 1;

    keyboard.key[1].value[0] = 'D';
    keyboard.key[1].value[1] = '3';
    keyboard.key[1].value[2] = 2;

    keyboard.key[2].value[0] = 'E';
    keyboard.key[2].value[1] = '3';
    keyboard.key[2].value[2] = 3;

    keyboard.key[3].value[0] = 'F';
    keyboard.key[3].value[1] = '3';
    keyboard.key[3].value[2] = 4;

    keyboard.key[4].value[0] = 'G';
    keyboard.key[4].value[1] = '3';
    keyboard.key[4].value[2] = 5;

    keyboard.key[5].value[0] = 'A';
    keyboard.key[5].value[1] = '3';
    keyboard.key[5].value[2] = 6;

    keyboard.key[6].value[0] = 'B';
    keyboard.key[6].value[1] = '3';
    keyboard.key[6].value[2] = 7;
    
    keyboard.key[7].value[0] = 'C';
    keyboard.key[7].value[1] = '4';
    keyboard.key[7].value[2] = 8;

    keyboard.key[8].value[0] = 'D';
    keyboard.key[8].value[1] = '4';
    keyboard.key[8].value[2] = 9;

    keyboard.key[9].value[0] = 'E';
    keyboard.key[9].value[1] = '4';
    keyboard.key[9].value[2] = 10;

    keyboard.key[10].value[0] = 'F';
    keyboard.key[10].value[1] = '4';
    keyboard.key[10].value[2] = 11;

    keyboard.key[11].value[0] = 'G';
    keyboard.key[11].value[1] = '4';
    keyboard.key[11].value[2] = 12;

    keyboard.key[12].value[0] = 'A';
    keyboard.key[12].value[1] = '4';
    keyboard.key[12].value[2] = 13;

    keyboard.key[13].value[0] = 'B';
    keyboard.key[13].value[1] = '4';
    keyboard.key[13].value[2] = 14;
    
    keyboard.key[14].value[0] = 'C';
    keyboard.key[14].value[1] = '5';
    keyboard.key[14].value[2] = 15;

    keyboard.key[15].value[0] = 'D';
    keyboard.key[15].value[1] = '5';
    keyboard.key[15].value[2] = 16;

    keyboard.key[16].value[0] = 'E';
    keyboard.key[16].value[1] = '5';
    keyboard.key[16].value[2] = 17;

    keyboard.key[17].value[0] = 'F';
    keyboard.key[17].value[1] = '5';
    keyboard.key[17].value[2] = 18;

    keyboard.key[18].value[0] = 'G';
    keyboard.key[18].value[1] = '5';
    keyboard.key[18].value[2] = 19;

    keyboard.key[19].value[0] = 'A';
    keyboard.key[19].value[1] = '5';
    keyboard.key[19].value[2] = 20;

    keyboard.key[20].value[0] = 'B';
    keyboard.key[20].value[1] = '5';
    keyboard.key[20].value[2] = 21;
    
    keyboard.key[21].value[0] = 'C';
    keyboard.key[21].value[1] = '#';
    keyboard.key[21].value[2] = 22;
    
    keyboard.key[22].value[0] = 'D';
    keyboard.key[22].value[1] = '#';
    keyboard.key[22].value[2] = 23;
    
    keyboard.key[23].value[0] = ' ';
    keyboard.key[23].value[1] = ' ';
    keyboard.key[23].value[2] = 24;
    
    keyboard.key[24].value[0] = 'F';
    keyboard.key[24].value[1] = '#';
    keyboard.key[24].value[2] = 25;
    
    keyboard.key[25].value[0] = 'G';
    keyboard.key[25].value[1] = '#';
    keyboard.key[25].value[2] = 26;
    
    keyboard.key[26].value[0] = 'A';
    keyboard.key[26].value[1] = '#';
    keyboard.key[26].value[2] = 27;
    
    keyboard.key[27].value[0] = 'C';
    keyboard.key[27].value[1] = '#';
    keyboard.key[27].value[2] = 28;
    
    keyboard.key[28].value[0] = 'D';
    keyboard.key[28].value[1] = '#';
    keyboard.key[28].value[2] = 29;
    
    keyboard.key[29].value[0] = ' ';
    keyboard.key[29].value[1] = ' ';
    keyboard.key[29].value[2] = 30;
    
    keyboard.key[30].value[0] = 'F';
    keyboard.key[30].value[1] = '#';
    keyboard.key[30].value[2] = 31;
    
    keyboard.key[31].value[0] = 'G';
    keyboard.key[31].value[1] = '#';
    keyboard.key[31].value[2] = 32;
    
    keyboard.key[32].value[0] = 'A';
    keyboard.key[32].value[1] = '#';
    keyboard.key[32].value[2] = 33;
    
    keyboard.key[33].value[0] = 'C';
    keyboard.key[33].value[1] = '#';
    keyboard.key[33].value[2] = 34;
    
    keyboard.key[34].value[0] = 'D';
    keyboard.key[34].value[1] = '#';
    keyboard.key[34].value[2] = 35;
    
    keyboard.key[35].value[0] = ' ';
    keyboard.key[35].value[1] = ' ';
    keyboard.key[35].value[2] = 36;
    
    keyboard.key[36].value[0] = 'F';
    keyboard.key[36].value[1] = '#';
    keyboard.key[36].value[2] = 37;
    
    keyboard.key[37].value[0] = 'G';
    keyboard.key[37].value[1] = '#';
    keyboard.key[37].value[2] = 38;
    
    keyboard.key[38].value[0] = 'A';
    keyboard.key[38].value[1] = '#';
    keyboard.key[38].value[2] = 39;
    
    

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
    uint32_t text_color = keycolorlist[id];
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
    uint32_t text_color = keycolorlist[id];
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
                /* Si l'appui a déjà été fixée sur une autre clé, "appuyez-la" et redessiner */
                for (j = 0; j < KEY_NUMBER; j++) {
                    if (keyboard.key[j].status == KEY_PRESSED and j!=i) {
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
    for (i = 0; i < KEY_NUMBER; i++) {
        if (keyboard.key[i].status == KEY_PRESSED) {
            Key_display_inverted(i);
        }
        else {
            Key_display_normal(i);
        }
    }
/* S’il n’y a pas de contact, vérifiez l’état de chaque touche, peut-être qu'un appui
   est déja en cours et devrait être traité comme une entrée */
    for (i = 0; i < KEY_NUMBER; i++) {
        /* Si la clé touche est pressée, "appuyez-la" et redessiner */
        if (keyboard.key[i].status == KEY_PRESSED) {
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
    if(key == 1)
    {
        midi.write(MIDIMessage::NoteOn(48));
    }
    else if(key == 2)
    {
        midi.write(MIDIMessage::NoteOn(50));
    }
    else if(key == 3)
    {
        midi.write(MIDIMessage::NoteOn(52));
    }
    else if(key == 4)
    {
        midi.write(MIDIMessage::NoteOn(53));
    }
    else if(key == 5)
    {
        midi.write(MIDIMessage::NoteOn(55));
    }
    else if(key == 6)
    {
        midi.write(MIDIMessage::NoteOn(57));
    }
    else if(key == 7)
    {
        midi.write(MIDIMessage::NoteOn(59));
    }
    else if(key == 8)
    {
        midi.write(MIDIMessage::NoteOn(60));
    }
    else if(key == 9)
    {
        midi.write(MIDIMessage::NoteOn(62));
    }
    else if(key == 10)
    {
        midi.write(MIDIMessage::NoteOn(64));
    }
    else if(key == 11)
    {
        midi.write(MIDIMessage::NoteOn(65));
    }
    else if(key == 12)
    {
        midi.write(MIDIMessage::NoteOn(67));
    }
    else if(key == 13)
    {
        midi.write(MIDIMessage::NoteOn(69));
    }
    else if(key == 14)
    {
        midi.write(MIDIMessage::NoteOn(71));
    }
    else if(key == 15)
    {
        midi.write(MIDIMessage::NoteOn(72));
    }
    else if(key == 16)
    {
        midi.write(MIDIMessage::NoteOn(74));
    }
    else if(key == 17)
    {
        midi.write(MIDIMessage::NoteOn(76));
    }
    else if(key == 18)
    {
        midi.write(MIDIMessage::NoteOn(77));
    }
    else if(key == 19)
    {
        midi.write(MIDIMessage::NoteOn(79));
    }
    else if(key == 20)
    {
        midi.write(MIDIMessage::NoteOn(81));
    }
    else if(key == 21)
    {
        midi.write(MIDIMessage::NoteOn(83));
    }
    else if(key == 22)
    {
        midi.write(MIDIMessage::NoteOn(49));
    }
    else if(key == 23)
    {
        midi.write(MIDIMessage::NoteOn(51));
    }
    else if(key == 25)
    {
        midi.write(MIDIMessage::NoteOn(54));
    }
    else if(key == 26)
    {
        midi.write(MIDIMessage::NoteOn(56));
    }
    else if(key == 27)
    {
        midi.write(MIDIMessage::NoteOn(58));
    }
    else if(key == 28)
    {
        midi.write(MIDIMessage::NoteOn(61));
    }
    else if(key == 29)
    {
        midi.write(MIDIMessage::NoteOn(63));
    }
    else if(key == 31)
    {
        midi.write(MIDIMessage::NoteOn(66));
    }
    else if(key == 32)
    {
        midi.write(MIDIMessage::NoteOn(68));
    }
    else if(key == 33)
    {
        midi.write(MIDIMessage::NoteOn(70));
    }
    else if(key == 34)
    {
        midi.write(MIDIMessage::NoteOn(73));
    }
    else if(key == 35)
    {
        midi.write(MIDIMessage::NoteOn(75));
    }
    else if(key == 37)
    {
        midi.write(MIDIMessage::NoteOn(78));
    }
    else if(key == 38)
    {
        midi.write(MIDIMessage::NoteOn(80));
    }
    else if(key == 39)
    {
        midi.write(MIDIMessage::NoteOn(82));
    }
    else
    {
        midi.write(MIDIMessage::AllNotesOff());
    }
    /* Retourner la valeur de la dernière touche pressée */
    return key;
}
