/*
 *******************************************************************************
 * Un exemple du clavier à l’écran sur le panneau de démonstration STM32F746NG Discovery
 Utilisation d’un ensemble standard de bibliothèques BSP et d’une
 Bibliothèques "keyboard.h"
 *******************************************************************************
 */

/* Ajouter une bibliothèque pour travailler avec LCD */
#include "stm32746g_discovery_lcd.h"
/* Ajout d’une bibliothèque de clavier à l’écran */
#include "keyboard.h"

#include "mbed.h"

#include "USBSerial.h"


/* Mémoire tampon personnalisée */
char kb_buffer[45];

void start_KB_LCD()  
{
    /* Initialisation de l’affichage
       Nous éteignons l’écran.
       Nous avons mis en place les première et deuxième couches de l’écran.*/
    BSP_LCD_Init(); // Initialisation de l'écran
    BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS); //Initialise la couche LCD 0 (background) dans le format ARGB8888 format (32 bits par pixel)
    BSP_LCD_LayerDefaultInit(1, LCD_FB_START_ADDRESS + (BSP_LCD_GetXSize() * BSP_LCD_GetYSize() * 4)); //Initialise la couche LCD 1 (forground) dans le format ARGB8888 format (32 bits par pixel)
    BSP_LCD_DisplayOn(); // Autorise l'affichage
    BSP_LCD_SelectLayer(0); // On se place sur la couche 0 ( background )
    BSP_LCD_Clear(LCD_COLOR_WHITE); // Efface le LCD tout entier
    BSP_LCD_SelectLayer(1); // On se place sur la couche 1 ( forground )
    BSP_LCD_Clear(LCD_COLOR_BLACK); // Efface le LCD tout entier
    /* Définir la couleur de fond et la couleur du texte de l’écran, ainsi que la police  */
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE); // Mets la couleur du texte du LCD en bleu
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE); // Mets la couleur de l'arrière plan du LCD en bleu
    BSP_LCD_SetFont(&Font16); // Selectionne la police d'écriture affichée à l'écran
    
    /* Initialisation de l’écran tactile*/
    BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
   
}


/* Programme de base */
int main(void)
{
      
       
      start_KB_LCD(); // Nouvel ecran ( noir )
      Keyboard_init(10, 50); // Initialisation et affichage du clavier 
      while(1)  
      {
          Keyboard_handler(); // On lance le gestionnaire d’entrée de clavier à l’écran
      }
      
}
