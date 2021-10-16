#include <avr/io.h>
#include <delay.h>
 
int key=0,p;
 
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
    TCNT1=0xFA;
    key++;
}
 
void namayesh(int n)
{
    switch(n)
    {
        case 0:PORTC=0b11000000;break;
        case 1:PORTC=0b11111001;break;
        case 2:PORTC=0b10100100;break;
        case 3:PORTC=0b10110000;break;
        case 4:PORTC=0b10011001;break;
        case 5:PORTC=0b10010010;break;
        case 6:PORTC=0b10000010;break;
        case 7:PORTC=0b11111000;break;
        case 8:PORTC=0b10000000;break;
        case 9:PORTC=0b10010000;break;
    }
}
 
void main(void)
{
    int i;
    char m[4];                                                              
    DDRA=0x00;
    PORTA=0x00;
    DDRB=0x00;
    PORTB=0x00;
    DDRC=0xFF;
    PORTC=0x00;
    DDRD=0xFF;
    PORTD=0x00;
 
TCCR1=0x05;
TCNT1=0xFA;
OCR1=0x00;
TIMSK=0x01;
 
#asm("sei")
 
 
     
  PORTD=0X00; 
 
              
while (1)
      {      
        p=key;
        for (i=0;;i++)
         {
              if(p<10) 
{ 
m[i]=p;
 break; 
}
 else
 { 
m[i]=p%10;
 p=p/10; 
} 
}
 PORTD.3=1;
 namayesh(m[0]); 
delay_ms (5);
 PORTC=0b11111111;
 PORTD.3=0;
 if(key>9)
               {      
                  PORTD.2=1; 
                  namayesh(m[1]);
                  delay_ms (5);
                  PORTC=0b11111111;
                  PORTD.2=0; 
               }   
              else if (key>99)
               {
                  PORTD.1=1; 
                  namayesh(m[2]);
                  delay_ms (5);
                  PORTC=0b11111111;
                  PORTD.1=0; 
               }
               else if(key>999)
               {
                  PORTD.0=1; 
                  namayesh(m[3]);
                  delay_ms (5);
                  PORTC=0b11111111;
                  PORTD.0=0; 
               }
             
      }
}