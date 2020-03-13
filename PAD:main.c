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



/*  
 * Calculates the mean and standard deviation of the array in data[] 
 */ 
void GetMeanSD(float data[], int qty, float *mn, float *sd)
{
    float sum = 0.0;
    float mean;
    float stdDev = 0.0;
    int i;
    float delt;
    for(i=0; i<qty; i++)    {
        sum = sum + data[i];
    }
    mean = sum/(float)qty;

    for(i=0; i<qty; i++) {
        delt = data[i] - mean;
        stdDev = stdDev + (delt * delt);
    }    
    *sd = sqrt(stdDev/(float)qty);
    *mn = mean;
}



/* copies comma-seperate item into 
 *   rcvr_str, returns ptr to the next or end 
 */
char *get_csv_itm(char *inbufloc, char *rcvr_str) 
{
    char *p1  =  inbufloc;
    char *p2  = rcvr_str ;
    *p2 = '\0';   /* null the rcvr first */
     if (*p1 == ',')     /* this is and empty item */
     {
        p1++;
        return(p1);
     } 
     while (*p1 != '\0'  && *p1 != ',')
     {
        *p2 = *p1;
        p1++;
        p2++;
     }
     if (*p1 == ',')
     {
        p1++;   /* move to nxt item */
     }
    *p2 = '\0';
    return(p1);
}






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
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetFont(&Font16);
    
    /* Initialisation de l’écran tactile*/
    BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
   
}



void get_kbd_str(char *promp, char *bufr)
{
      start_KB_LCD();
      Keyboard_init(0, 80);
      while(1)  {
          key = Keyboard_handler(promp, bufr);
          if (key == KEY_ENTER_VALUE)   break;    // to go to another screen ?
          HAL_Delay(10);  
      }
 }  





/* Programme de base */
int main(void)
{
#define STATSIZE 128
                   
      char  sbuf[128];  
      char  dbgtlk[128];
      
      char  tstr[128];
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
    
      char msg_b[128];
      int  u_tries;
      char u_name[128];
      char u_passwd[128];
      char out_str[128];
      char out_str2[128];
      
       
      start_KB_LCD(); // Nouvel ecran ( noir )
      BSP_LCD_SetFont(&Font24);
      get_kbd_str("USE JOYSTICK TO ENTER NAME:", kb_buffer); // affiche le clavier + etiquette en haut de l'écran
      strcpy(u_name, kb_buffer); //char * strcpy ( char * destination, const char * source ) copies the C string pointed by source into the array pointed by destination
      kb_buffer[0] = '\0';
     
      start_KB_LCD();
      BSP_LCD_SetFont(&Font24);
      get_kbd_str("USE JOYSTICK TO ENTER PASSWORD:", kb_buffer);
      strcpy(u_passwd, kb_buffer);
      kb_buffer[0] = '\0';
      
      /* 
       //    DISPLAY WHAT USER PUT  IN
       start_KB_LCD(); 
      BSP_LCD_SetFont(&Font24);
      strcpy(out_str, "USER  NAME: ");
      strcat(out_str, u_name);  
      BSP_LCD_DisplayStringAtLine(2, (uint8_t *) out_str);
      strcpy(out_str, "USER PASWD: ");
      strcat(out_str, u_passwd);  
      BSP_LCD_DisplayStringAtLine(4, (uint8_t *) out_str);
      
      HAL_Delay(2000);
      
      start_KB_LCD(); 
      strcpy(out_str, " READY TO TAKE MEASUREMENT ");
      BSP_LCD_DisplayStringAtLine(2, (uint8_t *) out_str);
      
      HAL_Delay(2000);
      
      start_KB_LCD(); 
      strcpy(out_str, " TRIGGER DETECTED ");
      BSP_LCD_DisplayStringAtLine(2, (uint8_t *) out_str);
      HAL_Delay(3000);
       
      start_KB_LCD();
      BSP_LCD_SetFont(&Font16);
       
         orangecalypso 
    BSP_LCD_DisplayStringAtLine(1, (uint8_t *)"RDG  Pb     #B     #C     #E   ");
    wait(1.0);
    for (ii=0; ii<STATSIZE; ii++)   {
        
        pbf = 10.2 + (float)ii/20.1;
        bi  = 80 + ii*20;    bf = (float) bi;
        ci  = 60 + ii*6;     cf = (float) ci;
        ei  = 30 + ii*4;     ef = (float) ei;
        
        pbar[ii] = pbf;
        bar[ii]  = bf;
        car[ii]  = cf;
        ear[ii]  = ef;
            
        sprintf(tstr, "%03d  %3.2f  %05d  %05d  %05d ", ii, pbf, bi, ci, ei);
        BSP_LCD_DisplayStringAtLine((2 + (ii%5)), (uint8_t *)tstr);
                
        if (ii > 2)  {
           
           if (ii > 11) {
              GetMeanSD(pbar + ii - 11 , 10, &pb_mn, &pb_sd);
              GetMeanSD(bar  + ii - 11,  10, &b_mn, &b_sd);
              GetMeanSD(car  + ii - 11,  10, &c_mn, &c_sd);
              GetMeanSD(ear  + ii - 11 , 10, &e_mn, &e_sd);
           }
           else        {
              GetMeanSD(pbar, ii, &pb_mn, &pb_sd);
              GetMeanSD(bar, ii, &b_mn, &b_sd);
              GetMeanSD(car, ii, &c_mn, &c_sd);
              GetMeanSD(ear, ii, &e_mn, &e_sd);
           }
         
           sprintf(tstr, "Mean %4.2f  %05d  %05d  %05d", pb_mn, (int)b_mn, (int)c_mn, (int)e_mn);
           BSP_LCD_DisplayStringAtLine((8), (uint8_t *)tstr);
           sprintf(tstr, "StDv %4.2f   %05d  %05d  %05d", pb_sd, (int)b_sd, (int)c_sd, (int)e_sd); 
           BSP_LCD_DisplayStringAtLine((9), (uint8_t *)tstr);
           
           sprintf(tstr, "                   %-04.2f%% %-04.2f%%",  100.0*(c_sd/c_mn), 100.0*(e_sd/e_mn)); 
           BSP_LCD_DisplayStringAtLine((10), (uint8_t *)tstr);
                 
           strcpy (sbuf, "---trying serial----");    
           BSP_LCD_DisplayStringAtLine(LINE(11), (uint8_t *)sbuf);
           
           rawq = 0;
           strcpy (sbuf, "--currently empty---");
           rawp = sbuf;   
           rawq = duds = 0;
           gotc = 'x';  
           
           strcpy (dbgtlk, "---pt1---"); 
           BSP_LCD_DisplayStringAtLine((12), (uint8_t *)dbgtlk);
       
           strcpy (dbgtlk, "---pt4---"); 
           BSP_LCD_DisplayStringAtLine((12), (uint8_t *)dbgtlk);
             
            if (strlen(dbgtlk) > 1)
            {
               Serial pc(USBTX, USBRX);  // Serial created and destroyed each cycle
               pc.baud(9600);
               pc.gets(sbuf , 30); 
            }
            else
            {
                strcpy(sbuf, "---");
            }
           // pc.scanf("%s", sbuf);
           
           if (rawq > 0)   *rawp = '\0';
           sbuf[40] = '\0';   // just for test .... truncate the line
           BSP_LCD_DisplayStringAtLine((11), (uint8_t *)sbuf);
           
             csvp = sbuf;
             csvp = get_csv_itm(csvp,   bstr);    bi = atoi(bstr);
             csvp = get_csv_itm(csvp,   cstr);    ci = atoi(cstr);
             csvp = get_csv_itm(csvp,   estr);    ei = atoi(estr); 
             csvp = get_csv_itm(csvp,   pbstr);   pbf = atof(pbstr);
           
             sprintf(out_str2, "b>%d  c>%d e>%d Pb> %s ", bi, ci, ei, pbstr);  
             BSP_LCD_DisplayStringAtLine((12), (uint8_t *)out_str2);
        }
        wait(2.0); 
    }*/
    
    
           
       
       
}
