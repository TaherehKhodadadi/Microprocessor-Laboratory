#include <mega16.h>
#include <delay.h>

int i=10,x=0;
 char step[4]={0x01,0x03,0x02,0x06};  
    void main()
    {
        DDRC=(0<<DDC7) | (0<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
        PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);
        DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
        PORTA=(0<<PORTA7) | (1<<PORTA6) | (0<<PORTA5) | (1<<PORTA4) | (0<<PORTA3) | (1<<PORTA2) | (0<<PORTA1) | (1<<PORTA0);
       
        while(1)
        {
            if(PINA.0==0)
            {
              delay_ms(5);
              i+=10;
              delay_ms(5);
            }
            if(PINA.2==0)
            {
              delay_ms(5);
              i-=10;
              delay_ms(5);
            }
            if(i==0)i=50;
            x=0;
            for(x=0;x<4;x++)
            {
                PORTC=step[x]|0X30;
                delay_ms(i);
            }
        }
    }