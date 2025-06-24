#include <main.h>
#include <interrupt.h>

int32 cur_speed = 0;
extern signed int16 step;
extern int8 is_start;
extern signed int is_forward;

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
         step = read_adc();
      }
      
      if(is_start)
         set_motor(is_forward * step);
      else
         set_motor(0);
         
      lcd_gotoxy(1, 2);
      printf(lcd_putc, "Speed: %4ld", cur_speed);
      delay_ms(100);
   }
}

