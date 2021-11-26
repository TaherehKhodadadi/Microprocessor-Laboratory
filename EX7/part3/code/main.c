#include <mega16.h>
#include <delay.h> 

int i=0;
int period=6;
void main()
{
 
//int period;
DDRA = 0x0F;
 
while (1)
{
 
/* Rotate Stepper Motor clockwise with Half step sequence */
for( i=0;i<50;i++)
{
PORTA = 0x09;
delay_ms(period);
PORTA = 0x08;
delay_ms(period);
PORTA = 0x0C;
delay_ms(period);
PORTA = 0x04;
delay_ms(period);
PORTA = 0x06;
delay_ms(period);
PORTA = 0x02;
delay_ms(period);
PORTA = 0x03;
delay_ms(period);
PORTA = 0x01;
delay-ms(period);

}
PORTA = 0x09; /* Last step to initial position */


 
/* Rotate Stepper Motor Anticlockwise with Full step sequence */
for(int i=0;i<50;i++)
{
PORTA = 0x01;
delay_ms(period);
PORTA = 0x03;
delay_ms(period);
PORTA = 0x02;
delay_ms(period);
PORTA = 0x06;
delay_ms(period);
PORTA = 0x04;
  delay_ms(period);
PORTA = 0x0C;
  delay_ms(period);
PORTA = 0x08;
delay_ms(period);  
PORTA = 0x09;
delay_ms(period);  
 
}
PORTA = 0x09;
delay_ms(period);
}
}