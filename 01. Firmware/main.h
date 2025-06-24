#ifndef _MAIN_H
#define _MAIN_H

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
#define ENCODER_A         PIN_B0
#define ENCODER_B         PIN_B1

// Motor
#define MOTOR_DIR_1     PIN_C6
#define MOTOR_DIR_2     PIN_C7

#define PPR    330

extern signed int16 step;
void initialize()
{
   set_tris_b(0xFF);
   set_tris_c(0x00);
   port_b_pullups(TRUE);
   
   setup_timer_2(T2_DIV_BY_16, 255, 1);
   setup_ccp1(CCP_PWM);
   set_pwm1_duty(0);
   
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0);
   set_adc_channel(0);
   delay_us(20);
   step = read_adc();
   
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);   // 4MHz / 4 / 8 = 125kHz ~ 8us
   set_timer1(3036);    // 65536 - (0.5s / 1.6us)
   
   ext_int_edge(L_TO_H);
   enable_interrupts(INT_EXT);
   enable_interrupts(INT_RB);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
}

void set_motor(signed int16 speed)
{
   if(speed > 0)
   {
      set_pwm1_duty(speed);
      output_bit(MOTOR_DIR_1, 1);
      output_bit(MOTOR_DIR_2, 0);   
   }
   else
   {
      set_pwm1_duty(-speed);
      output_bit(MOTOR_DIR_1, 0);
      output_bit(MOTOR_DIR_2, 1); 
   }
}

int8 is_start = 0;
extern int8 is_adc_mode;
void check_button_start()
{
   if(0 == input(BUTTON_START))
   {
      is_start = 1;
      is_adc_mode = 0;
   }
}

#endif
