/*
 *******************************************************************************
 * Keyboard Library virtual keyboard for touch screen display on demo
 * Découverte STM32F746NG
 *
 * Fichier "keyboard.ccp"
 *******************************************************************************
 */
/*Ajouter les fichiers header*/
#include "keyboard.h"
#include "USBMIDI.h"
#include "MIDIMessage.h"
/* Les structures de la clavature et de l’écran tactile */
Keyboard_TypeDef keyboard;
TS_StateTypeDef tScreen;
USBMIDI midi(Fastspeed_Interface,0x0700,0x0101,0x0001);

/* Liste couleurs possibles */
/*uint32_t keycolorlist[40] = {LCD_COLOR_BLUE,LCD_COLOR_GREEN,LCD_COLOR_RED,LCD_COLOR_CYAN,LCD_COLOR_MAGENTA,LCD_COLOR_YELLOW,LCD_COLOR_LIGHTBLUE,LCD_COLOR_LIGHTGREEN,LCD_COLOR_LIGHTRED,LCD_COLOR_LIGHTCYAN,LCD_COLOR_LIGHTMAGENTA,LCD_COLOR_LIGHTYELLOW,LCD_COLOR_DARKBLUE,LCD_COLOR_DARKGREEN,LCD_COLOR_DARKRED,LCD_COLOR_DARKCYAN,LCD_COLOR_DARKMAGENTA,LCD_COLOR_DARKYELLOW,LCD_COLOR_BROWN,LCD_COLOR_ORANGE,LCD_COLOR_BLUE,LCD_COLOR_GREEN,LCD_COLOR_RED,LCD_COLOR_CYAN,LCD_COLOR_MAGENTA,LCD_COLOR_YELLOW,LCD_COLOR_LIGHTBLUE,LCD_COLOR_LIGHTGREEN,LCD_COLOR_LIGHTRED,LCD_COLOR_LIGHTCYAN,LCD_COLOR_LIGHTMAGENTA,LCD_COLOR_LIGHTYELLOW,LCD_COLOR_DARKBLUE,LCD_COLOR_DARKGREEN,LCD_COLOR_DARKRED,LCD_COLOR_DARKCYAN,LCD_COLOR_DARKMAGENTA,LCD_COLOR_DARKYELLOW,LCD_COLOR_BROWN,LCD_COLOR_ORANGE};*/
uint32_t keycolorlist[15] = {LCD_COLOR_BLUE,LCD_COLOR_GREEN,LCD_COLOR_YELLOW,LCD_COLOR_ORANGE,LCD_COLOR_LIGHTMAGENTA,LCD_COLOR_DARKCYAN,LCD_COLOR_MAGENTA,LCD_COLOR_LIGHTRED,LCD_COLOR_RED,LCD_COLOR_DARKCYAN,LCD_COLOR_DARKBLUE,LCD_COLOR_DARKGREEN,LCD_COLOR_DARKYELLOW,LCD_COLOR_DARKRED,LCD_COLOR_DARKMAGENTA};

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
    keyboard.mode = GAMME_3;
    /* Bloc d’initialisation des touches */
    /* Initialisation des coordonnées des touches du clavier pour la première rangée */
    for (i = 0; i < 5; i++) {
        keyboard.key[i].id = i;                    //valeur unique d'identifiaction de chaque touche 
        keyboard.key[i].posX = keyboard.posX + 5 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * i; // coordonnée x de la touche
        keyboard.key[i].posY = keyboard.posY - 40; // coordonnée y de la touche
        keyboard.key[i].dimX = KEY_SMALL_LENGTH; // largeur de la touche
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT; // hauteur de la touche
        keyboard.key[i].status = KEY_RELEASED; // On initialise le status de la touche en indiquant qu'elle est bien relachée
    }
    /* Valeurs de chaque touche de la première rangée pour les différents modes */
    /* On stocke dans value le caractère à afficher selon le mode sélectionné et
       dans content la valeur unique associée */
       
    keyboard.key[0].value[NOTE] = 'C'; // Ce caractère sera toujours affiché car l'appelation de la note ne change pas quelque soit la gamme (C3,C4,C5,etc)
    keyboard.key[0].value[GAMME_3] = '3'; // Caractère à afficher au côté du C quand la gamme 3 (mode 1) est selectionnée
    keyboard.key[0].content[GAMME_3] = '1'; // valeur associée au C3 
    keyboard.key[0].value[GAMME_4] = '4'; // Caractère à afficher au côté du C quand la gamme 4 (mode 2) est selectionnée
    keyboard.key[0].content[GAMME_4] = '9'; // valeur associée au C4
    keyboard.key[0].value[GAMME_5] = '5'; // Caractère à afficher au côté du C quand la gamme 5 (mode 3) est selectionnée
    keyboard.key[0].content[GAMME_5] = 'h'; // valeur associée au C5
                                     //Il en va de même pour les touches suivantes
    keyboard.key[1].value[NOTE] = 'D';
    keyboard.key[1].value[GAMME_3] = '3';
    keyboard.key[1].content[GAMME_3] = '2';
    keyboard.key[1].value[GAMME_4] = '4';
    keyboard.key[1].content[GAMME_4] = 'a';
    keyboard.key[1].value[GAMME_5] = '5';
    keyboard.key[1].content[GAMME_5] = 'i';
    
    keyboard.key[2].value[NOTE] = 'E';
    keyboard.key[2].value[GAMME_3] = '3';
    keyboard.key[2].content[GAMME_3] = '3';
    keyboard.key[2].value[GAMME_4] = '4';
    keyboard.key[2].content[GAMME_4] = 'b';
    keyboard.key[2].value[GAMME_5] = '5';
    keyboard.key[2].content[GAMME_5] = 'j';
    
    keyboard.key[3].value[NOTE] = 'F';
    keyboard.key[3].value[GAMME_3] = '3';
    keyboard.key[3].content[GAMME_3] = '4';
    keyboard.key[3].value[GAMME_4] = '4';
    keyboard.key[3].content[GAMME_4] = 'c';
    keyboard.key[3].value[GAMME_5] = '5';
    keyboard.key[3].content[GAMME_5] = 'k';
    
    keyboard.key[4].value[NOTE] = 'G';
    keyboard.key[4].value[GAMME_3] = '3';
    keyboard.key[4].content[GAMME_3] = '5';
    keyboard.key[4].value[GAMME_4] = '4';
    keyboard.key[4].content[GAMME_4] = 'd';
    keyboard.key[4].value[GAMME_5] = '5';
    keyboard.key[4].content[GAMME_5] = 'l';
    /* Initialisation des coordonnées des touches du clavier pour la dernière (3e) rangée */
    for (i = 6; i < 9; i++) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 5 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * (i-5);
        keyboard.key[i].posY = keyboard.posY + 3 + KEY_SMALL_HEIGHT + KEY_DISTANCE + 10;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    
    keyboard.key[5].id = i;
    keyboard.key[5].posX = keyboard.posX + 5;
    keyboard.key[5].posY = keyboard.posY + 3 + KEY_SMALL_HEIGHT + KEY_DISTANCE +50;
    keyboard.key[5].dimX = KEY_SMALL_LENGTH;
    keyboard.key[5].dimY = KEY_SMALL_HEIGHT;
    keyboard.key[5].status = KEY_RELEASED;    
    
    keyboard.key[9].id = i;
    keyboard.key[9].posX = keyboard.posX + 5 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * (9-5);
    keyboard.key[9].posY = keyboard.posY + 3 + KEY_SMALL_HEIGHT + KEY_DISTANCE +50;
    keyboard.key[9].dimX = KEY_SMALL_LENGTH;
    keyboard.key[9].dimY = KEY_SMALL_HEIGHT;
    keyboard.key[9].status = KEY_RELEASED;   
    
    /* Valeurs de chaque touche de la dernière (3e) rangée pour les différents modes */
    /* On stocke dans value le caractère à afficher selon le mode sélectionné et
       dans content la valeur unique associée */
       
    keyboard.key[5].value[NOTE] = '<';
    keyboard.key[5].value[GAMME_3] = '-';
    keyboard.key[5].content[GAMME_3] = '-';
    keyboard.key[5].value[GAMME_4] = '-';
    keyboard.key[5].content[GAMME_4] = '-';
    keyboard.key[5].value[GAMME_5] = '-';
    keyboard.key[5].content[GAMME_5] = '-';
    
    keyboard.key[6].value[NOTE] = 'A';
    keyboard.key[6].value[GAMME_3] = '3';
    keyboard.key[6].content[GAMME_3] = '6';
    keyboard.key[6].value[GAMME_4] = '4';
    keyboard.key[6].content[GAMME_4] = 'e';
    keyboard.key[6].value[GAMME_5] = '5';
    keyboard.key[6].content[GAMME_5] = 'm';
    
    keyboard.key[7].value[NOTE] = 'B';
    keyboard.key[7].value[GAMME_3] = '3';
    keyboard.key[7].content[GAMME_3] = '7';
    keyboard.key[7].value[GAMME_4] = '4';
    keyboard.key[7].content[GAMME_4] = 'f';
    keyboard.key[7].value[GAMME_5] = '5';
    keyboard.key[7].content[GAMME_5] = 'n';
    
    keyboard.key[8].value[NOTE] = 'C';
    keyboard.key[8].value[GAMME_3] = '4';
    keyboard.key[8].content[GAMME_3] = '8';
    keyboard.key[8].value[GAMME_4] = '5';
    keyboard.key[8].content[GAMME_4] = 'g';
    keyboard.key[8].value[GAMME_5] = '6';
    keyboard.key[8].content[GAMME_5] = 'o';
    
    keyboard.key[9].value[NOTE] = '+';
    keyboard.key[9].value[GAMME_3] = '>';
    keyboard.key[9].content[GAMME_3] = '+';
    keyboard.key[9].value[GAMME_4] = '>';
    keyboard.key[9].content[GAMME_4] = '+';
    keyboard.key[9].value[GAMME_5] = '>';
    keyboard.key[9].content[GAMME_5] = '+';
    
    /* Initialisation des coordonnées des touches # (rangée du milieu)*/
    for (i = 10; i < 15; i++) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 5 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * (i-10) + 10;
        keyboard.key[i].posY = keyboard.posY + 3 + KEY_SMALL_HEIGHT + KEY_DISTANCE - 55;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH - 15;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT - 15;
        keyboard.key[i].status = KEY_RELEASED;
    }
    
    /* Valeurs de chaque touche de la rangée du mileu pour les différents modes */
    /* On stocke dans value le caractère à afficher selon le mode sélectionné et
       dans content la valeur unique associée */
       
    keyboard.key[10].value[NOTE] = 'C';
    keyboard.key[10].value[GAMME_3] = '#';
    keyboard.key[10].content[GAMME_3] = 'A';
    keyboard.key[10].value[GAMME_4] = '#';
    keyboard.key[10].content[GAMME_4] = 'F';
    keyboard.key[10].value[GAMME_5] = '#';
    keyboard.key[10].content[GAMME_5] = 'K';
    
    keyboard.key[11].value[NOTE] = 'D';
    keyboard.key[11].value[GAMME_3] = '#';
    keyboard.key[11].content[GAMME_3] = 'B';
    keyboard.key[11].value[GAMME_4] = '#';
    keyboard.key[11].content[GAMME_4] = 'G';
    keyboard.key[11].value[GAMME_5] = '#';
    keyboard.key[11].content[GAMME_5] = 'L';
    
    keyboard.key[12].value[NOTE] = 'F';
    keyboard.key[12].value[GAMME_3] = '#';
    keyboard.key[12].content[GAMME_3] = 'C';
    keyboard.key[12].value[GAMME_4] = '#';
    keyboard.key[12].content[GAMME_4] = 'H';
    keyboard.key[12].value[GAMME_5] = '#';
    keyboard.key[12].content[GAMME_5] = 'M';
    
    keyboard.key[13].value[NOTE] = 'G';
    keyboard.key[13].value[GAMME_3] = '#';
    keyboard.key[13].content[GAMME_3] = 'D';
    keyboard.key[13].value[GAMME_4] = '#';
    keyboard.key[13].content[GAMME_4] = 'I';
    keyboard.key[13].value[GAMME_5] = '#';
    keyboard.key[13].content[GAMME_5] = 'N';
    
    keyboard.key[14].value[NOTE] = 'A';
    keyboard.key[14].value[GAMME_3] = '#';
    keyboard.key[14].content[GAMME_3] = 'E';
    keyboard.key[14].value[GAMME_4] = '#';
    keyboard.key[14].content[GAMME_4] = 'J';
    keyboard.key[14].value[GAMME_5] = '#';
    keyboard.key[14].content[GAMME_5] = 'O';

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
    BSP_LCD_DisplayChar(keyboard.key[id].posX + 20, keyboard.key[id].posY + 8, keyboard.key[id].value[keyboard.mode]);
    BSP_LCD_DisplayChar(keyboard.key[id].posX + 8, keyboard.key[id].posY + 8, keyboard.key[id].value[NOTE]);

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
    BSP_LCD_DisplayChar(keyboard.key[id].posX + 20, keyboard.key[id].posY + 8, keyboard.key[id].value[keyboard.mode]);
    BSP_LCD_DisplayChar(keyboard.key[id].posX + 8, keyboard.key[id].posY + 8, keyboard.key[id].value[NOTE]);
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
    for(i=0;i < KEY_NUMBER; i++)
    {
        // Permet de colorier la touche lorsqu'on reste appuyé sur l'une d'elle
        if(keyboard.key[i].status == KEY_PRESSED)
        {
            Key_display_inverted(i);
        }
        else
        {
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
            return keyboard.key[i].content[keyboard.mode];
        }
    }
    return 0;
}
/* Gestionnaire d’entrée de clavier à l’écran */
void Keyboard_handler()
{
    uint8_t key;
    int i;
    /* Vérifiez s’il y a un nouveau clic */
    key = Keyboard_check();
    
        /* Si la touche "+>" est pressée, nous modifions la disposition du clavier */
        /* On passe à la gamme suivante : gamme 4 quand on était en gamme 3, gamme 5 quand on était en gamme 4,et gamme 3 quand on était en gamme 5*/
    if (key == '+')
    {
        
        if(keyboard.mode == 1) //Passage en gamme 4
        {
            keyboard.mode = 2;   
        }
        else if(keyboard.mode == 2)//Passage en gamme 5
        {
            keyboard.mode = 3;    
        }
        else if(keyboard.mode == 3)// Passage en gamme 3
        {
            keyboard.mode = 1;    
        }
        
        
        for (i = 0; i < KEY_NUMBER; i++)
        {
            /* Nous affichons la valeur clé de la nouvelle mise en page */
            BSP_LCD_DisplayChar(keyboard.key[i].posX + 8, keyboard.key[i].posY + 8, keyboard.key[i].value[keyboard.mode]);
            BSP_LCD_DisplayChar(keyboard.key[i].posX + 8, keyboard.key[i].posY + 8, keyboard.key[i].value[NOTE]);

        }
        
        wait(0.5); /*Permet d'éviter que le changement de gamme ne se fasse trop vite 
        ( sans cela si on est en gamme 3 par exemple et qu'on appuie sur +>, on peut 
        retourner en gamme 3 (en passant par la 4 et la 5 mais sans le voir) 
        tellement le changement se fait rapidement )*/
    }
    
    /* Si la touche "+>" est pressée, nous modifions la disposition du clavier */
    /* On passe à la gamme précédente : gamme 4 quand on était en gamme 5, gamme 3 quand on était en gamme 4,et 
    gamme 5 quand on était en gamme 3*/
    
    if (key == '-')
    {
        
        if(keyboard.mode == 1) //Passage en gamme 5
        {
            keyboard.mode = 3;   
        }
        else if(keyboard.mode == 2) //Passage en gamme 3
        {
            keyboard.mode = 1;    
        }
        else if(keyboard.mode == 3) // Passage en gamme 4
        {
            keyboard.mode = 2;    
        }
        
        
        for (i = 0; i < KEY_NUMBER; i++)
        {
            /* Nous affichons la valeur clé de la nouvelle mise en page */
            BSP_LCD_DisplayChar(keyboard.key[i].posX + 8, keyboard.key[i].posY + 8, keyboard.key[i].value[keyboard.mode]);
            BSP_LCD_DisplayChar(keyboard.key[i].posX + 8, keyboard.key[i].posY + 8, keyboard.key[i].value[NOTE]);

            /*Key_display_specials(i);*/
        }
        
        wait(0.5); //Idem que précédemment
    }
    /* GESTION DES SIGNAUX MIDI */
    
    /* On envoie un signal différent en fonction de la touche sur laquelle on appuie
        La note joué est donc différente */
    
    else if(key == '1')
    {
        midi.write(MIDIMessage::NoteOn(48));
    }
        else if(key == 'A')
    {
        midi.write(MIDIMessage::NoteOn(49));
    }
    else if(key == '2')
    {
        midi.write(MIDIMessage::NoteOn(50));
    }
        else if(key == 'B')
    {
        midi.write(MIDIMessage::NoteOn(51));
    }
    else if(key == '3')
    {
        midi.write(MIDIMessage::NoteOn(52));
    }
    else if(key == '4')
    {
        midi.write(MIDIMessage::NoteOn(53));
    }
    else if(key == 'C')
    {
        midi.write(MIDIMessage::NoteOn(54));
    }
    else if(key == '5')
    {
        midi.write(MIDIMessage::NoteOn(55));
    }
    else if(key == 'D')
    {
        midi.write(MIDIMessage::NoteOn(56));
    }
    else if(key == '6')
    {
        midi.write(MIDIMessage::NoteOn(57));
    }
    else if(key == 'E')
    {
        midi.write(MIDIMessage::NoteOn(58));
    }
    else if(key == '7')
    {
        midi.write(MIDIMessage::NoteOn(59));
    }
    else if(key == '8')
    {
        midi.write(MIDIMessage::NoteOn(60));
    }
    else if(key == '9')
    {
        midi.write(MIDIMessage::NoteOn(60));
    }
    else if(key == 'F')
    {
        midi.write(MIDIMessage::NoteOn(61));
    }
    else if(key == 'a')
    {
        midi.write(MIDIMessage::NoteOn(62));
    }
    else if(key == 'G')
    {
        midi.write(MIDIMessage::NoteOn(63));
    }
    else if(key == 'b')
    {
        midi.write(MIDIMessage::NoteOn(64));
    }
    else if(key == 'c')
    {
        midi.write(MIDIMessage::NoteOn(65));
    }
    else if(key == 'H')
    {
        midi.write(MIDIMessage::NoteOn(66));
    }
    else if(key == 'd')
    {
        midi.write(MIDIMessage::NoteOn(67));
    }
    else if(key == 'I')
    {
        midi.write(MIDIMessage::NoteOn(68));
    }
    else if(key == 'e')
    {
        midi.write(MIDIMessage::NoteOn(69));
    }
    else if(key == 'J')
    {
        midi.write(MIDIMessage::NoteOn(70));
    }
    else if(key == 'f')
    {
        midi.write(MIDIMessage::NoteOn(71));
    }
    else if(key == 'g')
    {
        midi.write(MIDIMessage::NoteOn(72));
    }
    else if(key == 'h')
    {
        midi.write(MIDIMessage::NoteOn(72));
    }
    else if(key == 'K')
    {
        midi.write(MIDIMessage::NoteOn(73));
    }
    else if(key == 'i')
    {
        midi.write(MIDIMessage::NoteOn(74));
    }
    else if(key == 'L')
    {
        midi.write(MIDIMessage::NoteOn(75));
    }
    else if(key == 'j')
    {
        midi.write(MIDIMessage::NoteOn(76));
    }
    else if(key == 'k')
    {
        midi.write(MIDIMessage::NoteOn(77));
    }
    else if(key == 'M')
    {
        midi.write(MIDIMessage::NoteOn(78));
    }
    else if(key == 'l')
    {
        midi.write(MIDIMessage::NoteOn(79));
    }
    else if(key == 'N')
    {
        midi.write(MIDIMessage::NoteOn(80));
    }
    else if(key == 'm')
    {
        midi.write(MIDIMessage::NoteOn(81));
    }
    else if(key == 'O')
    {
        midi.write(MIDIMessage::NoteOn(82));
    }
    else if(key == 'n')
    {
        midi.write(MIDIMessage::NoteOn(83));
    }
    else if(key == 'o')
    {
        midi.write(MIDIMessage::NoteOn(84));
    }
    
    else
    {
        midi.write(MIDIMessage::AllNotesOff());

    }
}
