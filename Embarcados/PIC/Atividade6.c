sbit LCD_RS at RE2_bit;
sbit LCD_EN at RE1_bit;
sbit LCD_D7 at RD7_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D4 at RD4_bit;

sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D7_Direction at TRISD7_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD4_bit;

void main()
{
     float Pot = 0;
     char Pot_String[8];
     int Duty_Cycle;
 
     TRISC.RC1 = 0;
     TRISB = 0;
     PORTA = 255;
     TRISA = 255;
     TRISA0_bit = 1;
     
     ADCON0 = 0b00000001;
     ADCON1 = 0b11001110;
     ADCON2 = 0b10111110;
     CMCON = 0b00000111;

     PWM1_Init(4000);
     PWM2_Init(4000);
     PWM1_Start();
     PWM2_Start();
     ADC_Init();
     Lcd_Init();
     Lcd_Cmd(_LCD_CURSOR_OFF);
     Lcd_Cmd(_LCD_CLEAR);

     while(1)
     {
         Pot = ADC_Read(0);
         Duty_Cycle = 0.24 * Pot;
         
         PWM1_Set_Duty(Duty_Cycle);
         
         if (Pot >= 1023)
         {
             PORTB = 255;
             PWM2_Set_Duty(1023);
         }
         else
         {
             PORTB = 0;
             PWM2_Set_Duty(0);
         }
         
         Pot *= 5.0/1023.0;
         
         FloatToStr(Pot, Pot_String);
         Ltrim(Pot_String);

         Lcd_Cmd(_LCD_CLEAR);
         lcd_out(1, 1, "Voltage:");    // descomente essa função
         lcd_out(2, 1, Pot_String);     // descomente essa função
         lcd_out_cp(" V");

         delay_ms(50);
     }
}

