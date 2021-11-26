#include <mega16a.h>
#include <delay.h>
#include <alcd.h>
 
int key_pad(void)    
{
PORTA.3=0;PORTA.4=1;PORTA.5=1;PORTA.6=1;   
if(!PINA.0) return 3;
if(!PINA.1) return 2;
if(!PINA.2) return 1;
PORTA.3=1;PORTA.4=0;PORTA.5=1;PORTA.6=1;   
if(!PINA.0) return 6;
if(!PINA.1) return 5;
if(!PINA.2) return 4;
PORTA.3=1;PORTA.4=1;PORTA.5=0;PORTA.6=1;   
if(!PINA.0) return 9;
if(!PINA.1) return 8;
if(!PINA.2) return 7;
PORTA.3=1;PORTA.4=1;PORTA.5=1;PORTA.6=0;   
if(!PINA.1) return 0;
if(!PINA.2) return 10;
return 12;
}
 
void lcd(int key)    
{
if(key==1) lcd_putsf("1");
if(key==2) lcd_putsf("2");
if(key==3) lcd_putsf("3");
if(key==4) lcd_putsf("4");
if(key==5) lcd_putsf("5");
if(key==6) lcd_putsf("6");
if(key==7) lcd_putsf("7");
if(key==8) lcd_putsf("8");
if(key==9) lcd_putsf("9");
if(key==0) lcd_putsf("0");
if(key==10) lcd_clear();
 
}
 
void main(void)
{      
 int key ;
 
DDRA=(0<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (1<<PORTA2) | (1<<PORTA1) | (1<<PORTA0);
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);
lcd_init(16);
 
while (1)
      { 
      do
      key=key_pad(); 
      while(key==12);    
      lcd(key);        
      delay_ms(350);
      }
}