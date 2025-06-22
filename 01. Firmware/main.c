#include <main.h> 

int32 encoder_cnt = 0;
int32 cur_speed = 0;
int16 timer1_cnt = 0;

#int_ext
void ext_isr()
{
   if(input(ENCODER))
   {
      encoder_cnt++;
   }
}

#int_timer1
void timer1_isr()
{
   timer1_cnt++;
   if(timer1_cnt == 2)
   {
      disable_interrupts(INT_EXT);
      cur_speed = (1.0 * encoder_cnt / PPR) * 60;
      encoder_cnt = 0;
      timer1_cnt = 0;
      enable_interrupts(INT_EXT);
   }
   set_timer1(3036);
}

void initialize()
{
   set_tris_b(0xFF);
   set_tris_c(0x00);
   port_b_pullups(TRUE);
   
   lcd_init();
   
   setup_timer_2(T2_DIV_BY_16, 255, 1);
   setup_ccp1(CCP_PWM);
   set_pwm1_duty(0);
   
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0);
   
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);   // 4MHz / 4 / 8 = 125kHz ~ 8us
   set_timer1(3036);    // 65536 - (0.5s / 1.6us)
   
   ext_int_edge(L_TO_H);
   enable_interrupts(INT_EXT);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
}

void main() 
{
   initialize();
   lcd_gotoxy(1, 1);
   printf(lcd_putc, "MOTOR CONTROLLER");
   set_pwm1_duty(700);
   output_bit(MOTOR_DIR_1, 0);
   output_bit(MOTOR_DIR_2, 1);
   while (1)
   {
      lcd_gotoxy(1, 2);
      printf(lcd_putc, "Speed: %4ld", cur_speed);
      delay_ms(500);
   }
}


