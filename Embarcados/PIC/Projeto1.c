#define PIN_OUTPUT 0
#define PIN_INPUT 1

void main()
{
    int Btn_Count = -1;
    int Btn_Flag = 0;
    int Display_Aux;
    unsigned char toDisplay[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
    
    ADCON1 = 0x0f;
     
    TRISC.RC1 = PIN_OUTPUT;     // Buzzer
    TRISB.RB0 = PIN_INPUT;      // Push Button
    TRISB.RB7 = PIN_OUTPUT;     // LED
    
    TRISA = 0; //define porta como saida
    PORTA = 0; //resseta todos os pinos do porta
    TRISD = 0; //define portd como saida
    PORTD = 0; //seta todos os pinos do portd
     
    while(1)
    {
        if ((PORTB.RB0 == 0) && (Btn_Flag == 0))
        {
            Btn_Flag = 1;
            Btn_Count++;
            if (Btn_Count > 9999) Btn_Count = 9999;
        }
        if ((PORTB.RB0 == 1) && (Btn_Flag == 1))
        {
            Btn_Flag = 0;
        }
    
        Display_Aux = Btn_Count;
    
        PORTD = toDisplay[Display_Aux%10];
        PORTA.RA5 = 1;
        Delay_ms(2);
        PORTA.RA5 = 0;
        Display_Aux/=10;

        PORTD = toDisplay[Display_Aux%10];
        PORTA.RA4 = 1;
        Delay_ms(2);
        PORTA.RA4 = 0;
        Display_Aux/=10;

        PORTD = toDisplay[Display_Aux%10];
        PORTA.RA3 = 1;
        Delay_ms(2);
        PORTA.RA3 = 0;
        Display_Aux/=10;

        PORTD = toDisplay[Display_Aux%10];
        PORTA.RA2 = 1;
        Delay_ms(2);
        PORTA.RA2 = 0;

        delay_ms(50);

        PORTC.RC1 = 0;
        PORTB.RB7 = 0;

        if (Btn_Count % 5 == 0)
        {
            PORTC.RC1 = 1;
        }
        
        if (Btn_Count % 2 == 0)
        {
            PORTB.RB7 = 1;
        }

    }
}