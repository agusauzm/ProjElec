/*
 *******************************************************************************
 * Keyboard Library virtual keyboard for touch screen display on demo
 * Découverte STM32F746NG
 *
 * Fichier "keyboard.c"
 *******************************************************************************
 */  

/*Ajouter le fichier header*/
#include "keyboard.h"

/* Les structures de la clavature et de l’écran tactile */
Keyboard_TypeDef keyboard;
TS_StateTypeDef tScreen;

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
    
    for (i = 0; i < 10; i++)
    {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 3 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * i;
        keyboard.key[i].posY = keyboard.posY + 3;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED; 
    }
    
    /* Valeurs ASCII de chaque touche de la première rangée pour différentes 
       dispositions du clavier 
    */
    keyboard.key[0].value[0] = 'Q';
    keyboard.key[0].value[2] = '1';
    
    keyboard.key[1].value[0] = 'W';
    keyboard.key[1].value[2] = '2';
    
    keyboard.key[2].value[0] = 'E';
    keyboard.key[2].value[2] = '3';
    
    keyboard.key[3].value[0] = 'R';
    keyboard.key[3].value[2] = '4';
    
    keyboard.key[4].value[0] = 'T';
    keyboard.key[4].value[2] = '5';
    
    keyboard.key[5].value[0] = 'Y';
    keyboard.key[5].value[2] = '6';
    
    keyboard.key[6].value[0] = 'U';
    keyboard.key[6].value[2] = '7';
    
    keyboard.key[7].value[0] = 'I';
    keyboard.key[7].value[2] = '8';
    
    keyboard.key[8].value[0] = 'O';
    keyboard.key[8].value[2] = '9';
    
    keyboard.key[9].value[0] = 'P';
    keyboard.key[9].value[2] = '0';
    
    /* Initialisation des coordonnées des touches du clavier pour la rangée du milieu */    
    
    for (i = 10; i < 19; i++)
    {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 27 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * (i - 10);
        keyboard.key[i].posY = keyboard.posY + 3 + KEY_SMALL_HEIGHT + KEY_DISTANCE;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED; 
    }
    
    /* Valeurs ASCII de chaque touche de la rangée du milieu pour différentes 
       dispositions du clavier 
    */
    
    keyboard.key[10].value[0] = 'A';
    keyboard.key[10].value[2] = '1';
    
    keyboard.key[11].value[0] = 'S';
    keyboard.key[11].value[2] = '2';
    
    keyboard.key[12].value[0] = 'D';
    keyboard.key[12].value[2] = '3';
    
    keyboard.key[13].value[0] = 'F';
    keyboard.key[13].value[2] = '4';
    
    keyboard.key[14].value[0] = 'G';
    keyboard.key[14].value[2] = '5';
    
    keyboard.key[15].value[0] = 'H';
    keyboard.key[15].value[2] = '6';
    
    keyboard.key[16].value[0] = 'J';
    keyboard.key[16].value[2] = '7';
    
    keyboard.key[17].value[0] = 'K';
    keyboard.key[17].value[2] = '8';
    
    keyboard.key[18].value[0] = 'L';
    keyboard.key[18].value[2] = '9';
    
    /* Initialisation des coordonnées des touches du clavier pour la dernière rangée */    
    for (i = 19; i < 26; i++)
    {
        keyboard.key[i].id = i;
        keyboard.key[i].posX = keyboard.posX + 51 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * (i - 19);
        keyboard.key[i].posY = keyboard.posY + 3 + (KEY_SMALL_HEIGHT + KEY_DISTANCE) * 2;
        keyboard.key[i].dimX = KEY_SMALL_LENGTH;
        keyboard.key[i].dimY = KEY_SMALL_HEIGHT;
        keyboard.key[i].status = KEY_RELEASED;
    }
    
    /* Valeurs ASCII de chaque touche de la dernière rangée pour différentes 
       dispositions du clavier 
    */
    keyboard.key[19].value[0] = 'Z';
    keyboard.key[19].value[2] = '1';
    
    keyboard.key[20].value[0] = 'X';
    keyboard.key[20].value[2] = '2';
    
    keyboard.key[21].value[0] = 'C';
    keyboard.key[21].value[2] = '3';
    
    keyboard.key[22].value[0] = 'V';
    keyboard.key[22].value[2] = '4';
    
    keyboard.key[23].value[0] = 'B';
    keyboard.key[23].value[2] = '5';
    
    keyboard.key[24].value[0] = 'N';
    keyboard.key[24].value[2] = '6';
    
    keyboard.key[25].value[0] = 'M';
    keyboard.key[25].value[2] = '7';
    
    /*Bloc d’initialisation pour les touches spéciales*/
      
    /* Touche "Enter" */
    keyboard.key[26].id = 26;
    keyboard.key[26].posX = 51 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * 7;
    keyboard.key[26].posY = keyboard.posY + 3 + (KEY_SMALL_HEIGHT + KEY_DISTANCE) * 2;
    keyboard.key[26].dimX = KEY_ENTER_LENGTH;
    keyboard.key[26].dimY = KEY_SMALL_HEIGHT;
    keyboard.key[26].status = KEY_RELEASED;
    keyboard.key[26].value[0] = KEY_ENTER_VALUE;
    keyboard.key[26].value[1] = KEY_ENTER_VALUE;
    keyboard.key[26].value[2] = KEY_ENTER_VALUE;
    

    
    /* Touche "Space" */
    keyboard.key[28].id = 28;
    keyboard.key[28].posX = 27 + (KEY_SMALL_LENGTH + KEY_DISTANCE) * 3;
    keyboard.key[28].posY = keyboard.posY + 3 + (KEY_SMALL_HEIGHT + KEY_DISTANCE) * 3;
    keyboard.key[28].dimX = KEY_SPACE_LENGTH;
    keyboard.key[28].dimY = KEY_SMALL_HEIGHT;
    keyboard.key[28].status = KEY_RELEASED;
    keyboard.key[28].value[0] = KEY_SPACE_VALUE;
    keyboard.key[28].value[1] = KEY_SPACE_VALUE;
    keyboard.key[28].value[2] = KEY_SPACE_VALUE;
    
    /* Touche "Backspace" */
    keyboard.key[29].id = 29;
    keyboard.key[29].posX = keyboard.posX + 27 + (KEY_DISTANCE + KEY_SMALL_LENGTH) * 8;
    keyboard.key[29].posY = keyboard.posY + 3 + (KEY_SMALL_HEIGHT + KEY_DISTANCE) * 3;
    keyboard.key[29].dimX = KEY_BACKSPACE_LENGTH;
    keyboard.key[29].dimY = KEY_SMALL_HEIGHT;
    keyboard.key[29].status = KEY_RELEASED;
    keyboard.key[29].value[0] = KEY_BACKSPACE_VALUE;
    keyboard.key[29].value[1] = KEY_BACKSPACE_VALUE;
    keyboard.key[29].value[2] = KEY_BACKSPACE_VALUE;
    
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

    for (i = 0; i < KEY_NUMBER; i++)
    {
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
    
    /* Pour les touches spéciales, nous affichons plus d’un caractère */
    Key_display_specials(id);
    
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
    
    /* Pour les touches spéciales, nous affichons plus d’un caractère */
    Key_display_specials(id);
    
    /* Retour de la couleur de fond d’écran précédente et la couleur de police */
    BSP_LCD_SetTextColor(text_color);
    BSP_LCD_SetBackColor(back_color);
    
    return 0;
}

/* Déterminer la valeur des touches spéciales de clavier */ 
uint8_t Key_display_specials(uint8_t id)
{
    /* Touche "Enter" */
    if (keyboard.key[id].value[keyboard.mode] == KEY_ENTER_VALUE)
    {
        BSP_LCD_DisplayStringAt(keyboard.key[id].posX + 8, keyboard.key[id].posY + 8, (uint8_t *) "Enter", LEFT_MODE);
    }
    /* Touche "Shift" */
    if (keyboard.key[id].value[keyboard.mode] == KEY_SHIFT_VALUE)
    {
        BSP_LCD_DisplayStringAt(keyboard.key[id].posX + 4, keyboard.key[id].posY + 8, (uint8_t *) "Shft", LEFT_MODE);
    }
    
    /* Touche "Space" */
    if (keyboard.key[id].value[keyboard.mode] == KEY_SPACE_VALUE)
    {
        BSP_LCD_DisplayStringAt(keyboard.key[id].posX + 32, keyboard.key[id].posY + 8, (uint8_t *) "Space", LEFT_MODE);
    }
    
    /* Touche "Backspace" */
    if (keyboard.key[id].value[keyboard.mode] == KEY_BACKSPACE_VALUE)
    {
        BSP_LCD_DisplayStringAt(keyboard.key[id].posX + 4, keyboard.key[id].posY + 8, (uint8_t *) "Bspc", LEFT_MODE);
    }
    
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
    if (tScreen.touchDetected)
    {
        for (i = 0; i < KEY_NUMBER; i++)
        {
            /* Si les coordonnées tactiles se trouvent dans les limites de l’une des touches non pressés, +/- 4 pixels */
            if (((tScreen.touchX[0] >= keyboard.key[i].posX - 4) && (tScreen.touchX[0] < keyboard.key[i].posX + keyboard.key[i].dimX + 4)) &&
                    ((tScreen.touchY[0] >= keyboard.key[i].posY - 4) && (tScreen.touchY[0] < keyboard.key[i].posY + keyboard.key[i].dimY + 4)) && 
                    (keyboard.key[i].status == KEY_RELEASED))
            {
                /* Dessinez la bonne clé dans la couleur inversée */
                Key_display_inverted(i);
                
                /* Si l'appui a déjà été fixée sur une autre clé, "appuyez-la" et redessiner */
                for (j = 0; j < KEY_NUMBER; j++)
                {
                    if (keyboard.key[j].status == KEY_PRESSED)
                    {
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
       
    else
    {
        for (i = 0; i < KEY_NUMBER; i++)
        {
            /* Si la clé touche est pressée, "appuyez-la" et redessiner */
            if (keyboard.key[i].status == KEY_PRESSED)
            {
                Key_display_normal(i);
                
                keyboard.key[i].status = KEY_RELEASED;
                BSP_TS_ResetTouchData(&tScreen);
                
                /* On retourne la valeur de l'entrée */
                return keyboard.key[i].value[keyboard.mode];
            }
        }
    }
    
    return 0;
}

/* Gestionnaire d’entrée de clavier à l’écran */
uint8_t Keyboard_handler(char *prompt, char buffer[])
{
    uint8_t i;
    uint8_t len;
    uint8_t key;
    
    /* Vérifiez s’il y a un nouveau clic */
    key = Keyboard_check();
    
     BSP_LCD_ClearStringLine(0);
     BSP_LCD_DisplayStringAtLine(0, (uint8_t *) prompt);
            
    
    /* Si vous appuyez sur une clé standard ou une clé " Espace " */
    if ((key >= KEY_SPACE_VALUE) && (key != KEY_DELETE_VALUE))
    {
        /* Vérifiez le tampon du clavier et, s’il y a un espace libre, ajoutez
           un symbole avec une clé pressée dans le tampon du clavier
         */
        i = strlen(keyboard.buffer);
        if (i < KEY_BUFFER_LEN)
        {
            keyboard.buffer[i] = key;
            keyboard.buffer[i + 1] = '\0';
            
            /* Afficher le tampon du clavier en haut de l’écran */
                        
            BSP_LCD_ClearStringLine(0);
            BSP_LCD_DisplayStringAtLine(0, (uint8_t *) prompt);
            
            BSP_LCD_ClearStringLine(1);
            BSP_LCD_DisplayStringAtLine(1, (uint8_t *) keyboard.buffer);
            
        }
    }
    /* Si une clé spéciale est pressée */
    else
    {
        /* Si vous appuyez sur la clé "Enter", nous compilons les données du tampon du
           clavier au tampon de l’utilisateur et nous avons collé les données dans le tampon du clavier
         */
        if (key == KEY_ENTER_VALUE)
        {
            len = strlen(keyboard.buffer);
            
            for (i = 0; i <= len; i++)
            {
                buffer[i] = keyboard.buffer[i];
            }
            
            keyboard.buffer[0] = '\0';
            
            /* Essuyer la ligne supérieure sur l’écran */
            BSP_LCD_ClearStringLine(0);
            BSP_LCD_DisplayStringAtLine(0, (uint8_t *) prompt);
            
            BSP_LCD_ClearStringLine(1);
            BSP_LCD_DisplayStringAtLine(1, (uint8_t *) keyboard.buffer);
        }
        
        /* Si la touche "Shift" est pressée, nous modifions la disposition du clavier */
        if (key == KEY_SHIFT_VALUE)
        {
            keyboard.mode = !keyboard.mode;
            
            for (i = 0; i < KEY_NUMBER; i++)
            {
                /* Nous affichons la valeur clé de la nouvelle mise en page */
                BSP_LCD_DisplayChar(keyboard.key[i].posX + 8, keyboard.key[i].posY + 8, keyboard.key[i].value[keyboard.mode]);
                Key_display_specials(i);
            }
        }
        
        /* Si la touche "Backspace" est pressée, retirez le dernier symbole du tampon du clavier */ 
        if (key == KEY_BACKSPACE_VALUE)
        {
            len = strlen(keyboard.buffer);
            if (len != 0)
            {
                keyboard.buffer[len - 1] = '\0'; 
                              
                BSP_LCD_ClearStringLine(1);
                BSP_LCD_DisplayStringAtLine(1, (uint8_t *) keyboard.buffer);
            }
        }
    }
    
    /* Retourner la valeur de la dernière touche pressée */
    return key;
}
