#include <16F877A.h>

#device ADC=10
#fuses NOWDT, NOBROWNOUT, NOLVP, HS 
#use delay(crystal=4000000)

// LCD1602
#define LCD_ENABLE_PIN  PIN_D2
#define LCD_RS_PIN      PIN_D0
#define LCD_RW_PIN      PIN_D1
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D5
#define LCD_DATA6       PIN_D6
#define LCD_DATA7       PIN_D7
#include <lcd.c>

// Buttons
#define BUTTON_START       PIN_B3
#define BUTTON_STOP        PIN_B4
#define BUTTON_ADC_MODE    PIN_B5
#define BUTTON_FORW        PIN_B6  
#define BUTTON_REVR        PIN_B7

// Encoder
#define ENCODER         PIN_B0 

// Motor
#define MOTOR_DIR_1     PIN_C6
#define MOTOR_DIR_2     PIN_C7

#define PPR    24

