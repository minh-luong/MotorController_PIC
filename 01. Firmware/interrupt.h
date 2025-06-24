#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include <main.h>

extern int32 ms_tick;
extern int32 encoder_cnt;
extern int32 measured_rpm;
extern int16 timer1_cnt;
extern float dir;
extern int8 is_start;
extern int8 is_adc_mode;
extern int8 wait_stop;
extern signed int8 is_forward;

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
   ms_tick++;
   
   timer1_cnt++;
   if(timer1_cnt == 1000)
   {
      disable_interrupts(INT_EXT);
      measured_rpm = (dir * encoder_cnt / PPR) * 60;
      encoder_cnt = 0;
      timer1_cnt = 0;
      enable_interrupts(INT_EXT);
   }
   set_timer1(64911);
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
      if(is_forward == -1)
      {
         is_forward = 1;
         set_motor(0);
         wait_stop = 1;
      }
   }
   else if(0 == input(BUTTON_REVR) && is_start)
   {
      is_adc_mode = 0;
      if(is_forward == 1)
      {
         is_forward = -1;
         set_motor(0);
         wait_stop = 1;
      }
   }
   else if(0 == input(BUTTON_ADC_MODE) && is_start)
   {
      if(is_adc_mode == 0)
      {
         is_adc_mode = 1;
         set_motor(0);
         wait_stop = 1;
      }
   }
}
#endif

