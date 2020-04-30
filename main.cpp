/*
 *******************************************************************************
 * Un exemple du clavier de pianoà l’écran sur STM32F746NG Discovery
 Utilisation d’un ensemble standard de bibliothèques BSP et d’une
 Bibliothèques "keyboard.h"
 *******************************************************************************
 */

/* Ajouter une bibliothèque pour travailler avec LCD */
#include "stm32746g_discovery_lcd.h"
/* Ajout d’une bibliothèque de claviers à l’écran */
#include "keyboard.h"

#include "mbed.h"

   // no such file: #include "USBSerial.h"

/* Modifications auxiliaires */
uint8_t i;
uint8_t key;
uint8_t  len;

/* Mémoire tampon personnalisée */
char kb_buffer[45];

void start_KB_LCD()  
{
    /* Initialisation de l’affichage
       Nous éteignons l’écran.
       Nous avons mis en place les première et deuxième couches de l’écran.*/
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
    BSP_LCD_LayerDefaultInit(1, LCD_FB_START_ADDRESS + (BSP_LCD_GetXSize() * BSP_LCD_GetYSize() * 4));
    BSP_LCD_DisplayOn();
    BSP_LCD_SelectLayer(0);
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    BSP_LCD_SelectLayer(1);
    BSP_LCD_Clear(LCD_COLOR_BLACK);
    /* Définir la couleur de fond et la couleur du texte de l’écran, ainsi que la police  */
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetFont(&Font16);
    
    /* Initialisation de l’écran tactile*/
    BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
   
}


void get_kbd_str(char *promp, char *bufr)
{
      start_KB_LCD();
      Keyboard_init(10, 0);
      while(1)  {
          key = Keyboard_handler(promp, bufr);
          HAL_Delay(10);  
      }
 }  


/* Programme de base */
int main(void)
{
      start_KB_LCD(); // Nouvel ecran ( noir )
      BSP_LCD_SetFont(&Font24);
      get_kbd_str("Controleur MIDI", kb_buffer); // affiche le clavier + etiquette en haut de l'écran
}
