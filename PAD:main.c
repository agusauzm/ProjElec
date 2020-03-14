/*
 *******************************************************************************
 * Un exemple du clavier à l’écran sur le panneau de démonstration STM32F746NG Discovery
 Utilisation d’un ensemble standard de bibliothèques BSP et d’une
 Bibliothèques "keyboard.h"
 *******************************************************************************
 */

/* Ajouter une bibliothèque pour travailler avec LCD */
#include "stm32746g_discovery_lcd.h"
/* Ajout d’une bibliothèque de claviers à l’écra */
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
    BSP_LCD_SetTransparency(0, 0);
    BSP_LCD_SetTransparency(1, 100);
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
      Keyboard_init(10, 50);
      while(1)  {
          key = Keyboard_handler(promp, bufr);
          if (key == KEY_ENTER_VALUE)   break;    // to go to another screen ?
          HAL_Delay(10);  
      }
 }  


/* Programme de base */
int main(void)
{
#define STATSIZE 126
                   
      char  sbuf[126];  
      char  dbgtlk[126];
      
      char  tstr[126];
      char  bstr[32];
      char  cstr[32];
      char  estr[32];
      char  pbstr[32];
      int   ii;
      
         char *rawp;
    char *csvp;
    int   rawq; 
    int   bi, ci, ei; 
    float pbf, bf, cf, ef;
    float pbar[STATSIZE];
    float bar[STATSIZE];
    float car[STATSIZE];
    float ear[STATSIZE];
    int duds = 0;
    char  gotc;
    
    float pb_mn, pb_sd, b_mn, b_sd, c_mn, c_sd, e_mn, e_sd;
    
      char msg_b[126];
      int  u_tries;
      char u_name[126];
      char u_passwd[126];
      char out_str[126];
      char out_str2[126];
      
       
      start_KB_LCD(); // Nouvel ecran ( noir )
      BSP_LCD_SetFont(&Font24);
      get_kbd_str("Controleur MIDI", kb_buffer); // affiche le clavier + etiquette en haut de l'écran
      strcpy(u_name, kb_buffer); //char * strcpy ( char * destination, const char * source ) copies the C string pointed by source into the array pointed by destination
      kb_buffer[0] = '\0';
     
      start_KB_LCD();
      BSP_LCD_SetFont(&Font24);
      get_kbd_str("USE JOYSTICK TO ENTER PASSWORD:", kb_buffer);
      strcpy(u_passwd, kb_buffer);
      kb_buffer[0] = '\0';
      
}
