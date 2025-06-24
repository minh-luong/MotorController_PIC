#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include <main.h>

int32 time_ms = 0;
int32 encoder_cnt = 0;
extern int32 cur_speed;
int16 timer1_cnt = 0;
float dir = 0;
signed int16 step = 0;
extern int8 is_start;
int8 is_adc_mode = 0;
signed int8 is_forward = 1;

#int_ext
void ext_isr()
{
   clear_interrupt(INT_EXT);
   if(input(ENCODER_A))
   {
      encoder_cnt++;
      if(input(ENCODER_B))
         dir = -1.0;
      else
         dir = 1.0;
   }
}

#int_timer1
void timer1_isr()
{
   clear_interrupt(INT_TIMER1);
   timer1_cnt++;
   if(timer1_cnt == 2)
   {
      disable_interrupts(INT_EXT);
      cur_speed = (dir * encoder_cnt / PPR) * 60;
      encoder_cnt = 0;
      timer1_cnt = 0;
      enable_interrupts(INT_EXT);
   }
   set_timer1(3036);
}

#int_rb
void rb_change_isr()
{
   clear_interrupt(INT_RB);
   
   if(0 == input(BUTTON_STOP))
   {
      is_adc_mode = 0;
      is_start = 0;
   }
   else if(0 == input(BUTTON_FORW) && is_start)
   {
      is_adc_mode = 0;
      is_forward = 1;
   }
   else if(0 == input(BUTTON_REVR) && is_start)
   {
      is_adc_mode = 0;
      is_forward = -1;
   }
   else if(0 == input(BUTTON_ADC_MODE) && is_start)
   {
      is_adc_mode = 1;
   }
}
#endif

