/*
 *******************************************************************************
 * Библиотека Keyboard виртуальной клавиатуры для дисплея с тач-экраном на демо-
 * плате STM32F746NG Dicovery
 * 
 * Файл "keyboard.h"
 *******************************************************************************
 */

/* Определяем для предотвращения множественного включения */
#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

/* На случай использования в составе C++ проекта */
#ifdef __cplusplus
extern "C" {
#endif

/* Добавляем библиотеку <string.h> для импорта функции strlen() */
#include <string.h>

/* Добавляем библиотеки для работы с LCD и контроллером тач-экрана */
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"

/* Определения */
/* Различные раскладки клавиатуры */
#define MODE_NUMBER                     3
#define MODE_UPPER_CASE                 0
#define MODE_LOWER_CASE                 1
#define MODE_SYMBOLS                    2

/* Общее количество клавиш */
#define KEY_NUMBER                      8
#define KEY_BUFFER_LEN                  8

/* Размеры клавиш в пикселях */
#define KEY_SMALL_LENGTH                70
#define KEY_SMALL_HEIGHT                70
#define KEY_ENTER_LENGTH                88
#define KEY_SHIFT_LENGTH                64
#define KEY_BACKSPACE_LENGTH            64
#define KEY_SPACE_LENGTH                136
#define KEY_DISTANCE                    25

/* ASCII-коды для специальных клавиш */
#define KEY_ENTER_VALUE                 0x0D
#define KEY_SHIFT_VALUE                 0x10
#define KEY_SPACE_VALUE                 0x20
#define KEY_BACKSPACE_VALUE             0x08
#define KEY_DELETE_VALUE                0x7F

/* Состояние клавишы */
#define KEY_RELEASED                    0
#define KEY_PRESSED                     1

/* Структура для отдельной клавишы */
typedef struct
{
    uint8_t         id;
    uint8_t         status;
    uint16_t        posX;
    uint16_t        posY;
    uint8_t         dimX;
    uint8_t         dimY;
    uint8_t         value[MODE_NUMBER];
}   Key_TypeDef;

/* Структура для всей клавиатуры */
typedef struct
{
    uint16_t        posX;
    uint16_t        posY;
    Key_TypeDef key[KEY_NUMBER];
    uint8_t         mode;    
    char            buffer[KEY_BUFFER_LEN];
}   Keyboard_TypeDef;

/* Функции для работы с экранной клавиатурой */
uint8_t Keyboard_init(uint16_t x_value, uint16_t y_value);
uint8_t Keyboard_display_all(void);
uint8_t Key_display_normal(uint8_t id);
uint8_t Key_display_inverted(uint8_t id);
uint8_t Key_display_specials(uint8_t id);
uint8_t Keyboard_check(void);
uint8_t Keyboard_handler(char *prompt, char buffer[]);

#ifdef __cplusplus
}
#endif

/* Конец файла "keyboard.h" */
#endif
