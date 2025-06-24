#include <main.h>
#include <interrupt.h>

int32 ms_tick = 0;
int32 encoder_cnt = 0;
int32 measured_rpm = 0;
int16 timer1_cnt = 0;
float dir = 0;
signed int16 cur_speed = 0;
int8 is_start = 0;
int8 is_adc_mode = 0;
int8 wait_stop = 0;
signed int8 is_forward = 1;

void main() 
{
   initialize();
   
   lcd_init();
   lcd_gotoxy(1, 1);
   printf(lcd_putc, "MOTOR CONTROLLER");
   set_pwm1_duty(0);
   output_bit(MOTOR_DIR_1, 0);
   output_bit(MOTOR_DIR_2, 1);
   while (1)
   {
      check_button_start();
      if(is_adc_mode)
      {
         set_adc_channel(0);
         delay_us(20);
         cur_speed = read_adc();
      }
      
      if(wait_stop)
      {
         if(measured_rpm == 0)
            wait_stop = 0;
      }
      else if(is_start)
         set_motor(is_forward * cur_speed);
      else
         set_motor(0);
      
      if(ms_tick % 100 == 0)
      {
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "Speed: %4ld", measured_rpm);
      }
   }
}

