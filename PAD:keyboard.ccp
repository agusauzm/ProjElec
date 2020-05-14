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
USBMIDI midi(Fastspeed_Interface,0x0700,0x0101,0x0001);

/* Liste couleurs possibles */
uint32_t keycolorlist[13] = {LCD_COLOR_GREEN,LCD_COLOR_YELLOW,LCD_COLOR_LIGHTMAGENTA,LCD_COLOR_BLUE,LCD_COLOR_ORANGE,LCD_COLOR_RED,LCD_COLOR_ORANGE,LCD_COLOR_GREEN,LCD_COLOR_BLUE,LCD_COLOR_MAGENTA,LCD_COLOR_BROWN,LCD_COLOR_ORANGE};

/* Fonction definition de touches - TEST - */
void Keyboard_define(void)
{
    keyboard.key[110].value[0]='<';
    keyboard.key[110].value[1]='-';
    keyboard.key[110].value[2]=' ';
    keyboard.key[110].content[0]=-2;
    
    keyboard.key[111].value[0]='+';
    keyboard.key[111].value[1]='>';
    keyboard.key[111].value[2]=' ';
    keyboard.key[111].content[0]=-1;
    
    int i;
    
    for (i = 0; i<85; i++)
    {
        int gamme = ((int) i/12) +1;
        if (gamme == 1){
            keyboard.key[i].value[1]='1';
        }
        if (gamme == 2){
            keyboard.key[i].value[1]='2';
        }
        if (gamme == 3){
            keyboard.key[i].value[1]='3';
        }
        if (gamme == 4){
            keyboard.key[i].value[1]='4';
        }
        if (gamme == 5){
            keyboard.key[i].value[1]='5';
        }
        if (gamme == 6){
            keyboard.key[i].value[1]='6';
        }
        if (gamme == 7){
            keyboard.key[i].value[1]='7';
        }
        if (gamme == 8){
            keyboard.key[i].value[1]='8';
        }
        
        if (i%12 == 0)
        {
            keyboard.key[i].value[0]='C';
            keyboard.key[i].value[2]=' ';
            keyboard.key[i].content[0]= 24 + i;
        }
        if (i%12 == 1)
        {
            keyboard.key[i].value[0]='C';
            keyboard.key[i].value[2]='#';
            keyboard.key[i].content[0]= 24 + i;
        }
        if (i%12 == 2)
        {
            keyboard.key[i].value[0]='D';
            keyboard.key[i].value[2]=' ';
            keyboard.key[i].content[0]= 24 + i;
        }
        if (i%12== 3)
        {
            keyboard.key[i].value[0]='D';
            keyboard.key[i].value[2]='#';
            keyboard.key[i].content[0]= 24 + i;
        }
        if (i%12== 4)
        {
            keyboard.key[i].value[0]='E';
            keyboard.key[i].value[2]=' ';
            keyboard.key[i].content[0]= 24 + i;
        }
        if (i%12== 5)
        {
            keyboard.key[i].value[0]='F';
            keyboard.key[i].value[2]=' ';
            keyboard.key[i].content[0]= 24 + i;
        }
        if (i%12== 6)
        {
            keyboard.key[i].value[0]='F';
            keyboard.key[i].value[2]='#';
            keyboard.key[i].content[0]= 24 + i;
        }
        if (i%12== 7)
        {
            keyboard.key[i].value[0]='G';
            keyboard.key[i].value[2]=' ';
            keyboard.key[i].content[0]= 24 + i;
        }
        if (i%12== 8)
        {
            keyboard.key[i].value[0]='G';
            keyboard.key[i].value[2]='#';
            keyboard.key[i].content[0]= 24 + i;
        }
        if (i%12== 9)
        {
            keyboard.key[i].value[0]='A';
            keyboard.key[i].value[2]=' ';
            keyboard.key[i].content[0]= 24 + i;
        }
        if (i%12== 10)
        {
            keyboard.key[i].value[0]='A';
            keyboard.key[i].value[2]='#';
            keyboard.key[i].content[0]= 24 + i;
        }
        if (i%12== 11)
        {
            keyboard.key[i].value[0]='B';
            keyboard.key[i].value[2]=' ';
            keyboard.key[i].content[0]= 24 + i;
        }
    }
}

/*Fonction pour travailler avec le clavier à l’écran */
/* Initialisation et affichage du clavier */
int Keyboard_init(uint16_t  x_value, uint16_t   y_value)
{
    int i;
    /* Les coordonnées du coin supérieur gauche du clavier sur l’écran servent de "point
       de référence" pour déterminer l’emplacement de tous les autres éléments */
    keyboard.posX = x_value;
    keyboard.posY = y_value;
    /* La valeur par défaut sur le clavier est une disposition anglaise en MAJ. */
    keyboard.mode = MODE_LOWER_CASE;
    /* Bloc d’initialisation pour les clés standard */
    
    Keyboard_define();
    
    /* Initialisation des coordonnées des touches du clavier pour < */
    keyboard.key[110].posX = keyboard.posX + 10;
    keyboard.key[110].posY = keyboard.posY - 40;
    keyboard.key[110].dimX = KEY_SMALL_LENGTH;
    keyboard.key[110].dimY = KEY_SMALL_HEIGHT;
    keyboard.key[110].status = KEY_RELEASED;
    
    /* Initialisation des coordonnées des touches du clavier pour > */
    keyboard.key[111].posX = keyboard.posX + 380;
    keyboard.key[111].posY = keyboard.posY - 40;
    keyboard.key[111].dimX = KEY_SMALL_LENGTH;
    keyboard.key[111].dimY = KEY_SMALL_HEIGHT;
    keyboard.key[111].status = KEY_RELEASED;
    
    /* Initialisation des coordonnées des touches du clavier pour C */
    for (i = 0; i < 85; i=i+12) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 120;
        keyboard.key[i].posY = keyboard.posY + 20;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    
    /* Initialisation des coordonnées des touches du clavier pour C# */
    for (i = 1; i < 85; i=i+12) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 160;
        keyboard.key[i].posY = keyboard.posY - 40;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALLER_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    
    /* Initialisation des coordonnées des touches du clavier pour D */
    for (i = 2; i < 85; i=i+12) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 200;
        keyboard.key[i].posY = keyboard.posY + 20;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    
    /* Initialisation des coordonnées des touches du clavier pour D# */
    for (i = 3; i < 85; i=i+12) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 240;
        keyboard.key[i].posY = keyboard.posY - 40;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALLER_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    
    /* Initialisation des coordonnées des touches du clavier pour E */
    for (i = 4; i < 85; i=i+12) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 280;
        keyboard.key[i].posY = keyboard.posY + 20;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    
    /* Initialisation des coordonnées des touches du clavier pour F */
    for (i = 5; i < 85; i=i+12) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 30;
        keyboard.key[i].posY = keyboard.posY + 160;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    
    /* Initialisation des coordonnées des touches du clavier pour F# */
    for (i = 6; i < 85; i=i+12) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 90;
        keyboard.key[i].posY = keyboard.posY + 100;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALLER_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    
    /* Initialisation des coordonnées des touches du clavier pour G */
    for (i = 7; i < 85; i=i+12) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 140;
        keyboard.key[i].posY = keyboard.posY + 160;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    
    /* Initialisation des coordonnées des touches du clavier pour G# */
    for (i = 8; i < 85; i=i+12) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 200;
        keyboard.key[i].posY = keyboard.posY + 100;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALLER_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    
    /* Initialisation des coordonnées des touches du clavier pour A */
    for (i = 9; i < 85; i=i+12) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 250;
        keyboard.key[i].posY = keyboard.posY + 160;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    
    /* Initialisation des coordonnées des touches du clavier pour A# */
    for (i = 10; i < 85; i=i+12) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 310;
        keyboard.key[i].posY = keyboard.posY + 100;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALLER_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    
    /* Initialisation des coordonnées des touches du clavier pour C+ */
    for (i = 11; i < 85; i=i+12) {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 360;
        keyboard.key[i].posY = keyboard.posY + 160;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    
    /* Nous dessinons le clavier à l’écran */
    Keyboard_display_all();
    return 0;
}
/* Dessiner le clavier à l’écran */
int Keyboard_display_all(void)
{
    int i;
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
int Key_display_normal(int id)
{
    int gamme = ((int) id/12) +1;
    if (keyboard.mode == gamme || id == 110 || id == 111)
    {
        /* Nous obtenons la couleur de l’arrière-plan de l’écran et la couleur de la police */
        uint32_t back_color = BSP_LCD_GetBackColor();
        uint32_t text_color = keycolorlist[id%12];
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
        BSP_LCD_DisplayChar(keyboard.key[id].posX + 20, keyboard.key[id].posY + 8, keyboard.key[id].value[1]);
        BSP_LCD_DisplayChar(keyboard.key[id].posX + 8, keyboard.key[id].posY + 8, keyboard.key[id].value[0]);
        BSP_LCD_DisplayChar(keyboard.key[id].posX + 32, keyboard.key[id].posY + 8, keyboard.key[id].value[2]);
    }
    return 0;
}
/* Dessin d’une seule touche de clavier à l’écran (couleur inversée) */
int Key_display_inverted(int id)
{
    int gamme = ((int) id/12) +1;
    if (keyboard.mode == gamme || id == 110 || id == 111)
    {
        /* Nous obtenons la couleur de l’arrière-plan de l’écran et la couleur de la police */
        uint32_t back_color = BSP_LCD_GetBackColor();
        uint32_t text_color = keycolorlist[id%12];
        BSP_LCD_FillRect(keyboard.key[id].posX, keyboard.key[id].posY, keyboard.key[id].dimX, keyboard.key[id].dimY);
        /* Retournez les mêmes valeurs de couleur de l’arrière-plan de l’écran et de la couleur de police */
        BSP_LCD_SetTextColor(back_color);
        BSP_LCD_SetBackColor(text_color);
        /* Afficher la valeur de la touche dans la disposition actuelle du clavier. */
        BSP_LCD_DisplayChar(keyboard.key[id].posX + 20, keyboard.key[id].posY + 8, keyboard.key[id].value[1]);
        BSP_LCD_DisplayChar(keyboard.key[id].posX + 8, keyboard.key[id].posY + 8, keyboard.key[id].value[0]);
        BSP_LCD_DisplayChar(keyboard.key[id].posX + 32, keyboard.key[id].posY + 8, keyboard.key[id].value[2]);
        BSP_LCD_SetTextColor(text_color);
        BSP_LCD_SetBackColor(back_color);
    }
    return 0;
}
/* Vérifier l’entrée sur le clavier à l’écran */
int Keyboard_check(void)
{
    int i;
    /* Vérification de l’état du "conducteur" de l’écran tactile */
    BSP_TS_GetState(&tScreen);
    /* Si on appuie sur l'ecran */
    if (tScreen.touchDetected) {
        for (i = 0; i < KEY_NUMBER; i++) {
            /* Si les coordonnées tactiles se trouvent dans les limites de l’une des touches non pressés, +/- 4 pixels */
            if (((tScreen.touchX[0] >= keyboard.key[i].posX - 4) && (tScreen.touchX[0] < keyboard.key[i].posX + keyboard.key[i].dimX + 4)) &&
                    ((tScreen.touchY[0] >= keyboard.key[i].posY - 4) && (tScreen.touchY[0] < keyboard.key[i].posY + keyboard.key[i].dimY + 4)) &&
                    (keyboard.key[i].status == KEY_RELEASED)) {
                /* Changer l’état de la touche pour laquelle l'appui a été enregistré */
                keyboard.key[i].status = KEY_PRESSED;
                /* Réinitialisez l’état du conducteur de l’écran tactile */
                BSP_TS_ResetTouchData(&tScreen);
            }
        }
    }
    for(i=0;i < KEY_NUMBER; i++)
    {
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
            return keyboard.key[i].content[0];
        }
    }
    return 0;
}
/* Gestionnaire d’entrée de clavier à l’écran */
void Keyboard_handler()
{
    int key;
    /* Vérifiez s’il y a un nouveau clic */
    key = Keyboard_check();
    
        /* Si la touche "Shift" est pressée, nous modifions la disposition du clavier */
    if (key == -2)
    {
        
        if (keyboard.mode == 1)
        {
            keyboard.mode = 7;
        }
        else
        {
            keyboard.mode=keyboard.mode-1;
        }
        
        wait(0.2);
    }
    if (key == -1)
    {
        
        if (keyboard.mode == 7)
        {
            keyboard.mode = 1;
        }
        else
        {
            keyboard.mode=keyboard.mode+1;
        }
        
        wait(0.2);
    }       
    if (key >= 24 && key <= 108)
    {
        midi.write(MIDIMessage::NoteOn(24 + (keyboard.mode-1)*12 + (key%12)));
    }
    else
    {
        midi.write(MIDIMessage::AllNotesOff());

    }
}
