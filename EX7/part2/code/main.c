#include <mega16.h>
#include <delay.h>
#include <lcd.h>
#include <keypad.h>

void function()
{
LCDclr();
LCDGotoXY(0,0);
LCDdisplay("ENTER PASSWORD");
LCDGotoXY(1,0);
}

int i=0,j=0;
char k=0,arr[16]="NUL",pass[16]="1234";

void main()
{
DDRA=1;
PORTA=0;
LCDinit();
LCDcursorOFF();
while(1)
{
if(PINA&1)
{
  LCDdisplay("SAFE OPEN");
  LCDGotoXY(1,0);
}
else
  function();
  while(i<15000)
{
  if(!k)
  i++;
  else
  {
   if(k!='#' && k!='E')
   {
   arr[j++]=k;
   if(PINA&1)
   LCDsendChar(k);
   else
   LCDsendChar('*');
   }
  else if(k=='E' && j!=0) 
   {
   j--;
   LCDcursorLeft(1);
   LCDsendChar(' ');
   LCDcursorLeft(1);
   }
  else if(k!='E')   
   {
   if(!strcmp(arr,"NUL"))
   {
    PORTA=0;
    LCDclr();
    LCDdisplay("SAFE LOCKED");
    _delay_ms(1000);
    function();
   }
   else 
    {
    arr[j]='';
    j=0;
    LCDclr();
    if(PINA&1)
    {
     if(strlen(arr)>=4)
    {
     strcpy(pass,arr);
     PORTA=0;//lock the safe
     LCDclr();
     LCDdisplay("SAFE LOCKED");
     _delay_ms(1000);
     function();
    }
    else
    {
     LCDdisplay("ERROR");
     LCDGotoXY(1,0);
     LCDdisplay("WEAK PASSWORD");
     _delay_ms(1000);
     LCDclr();
     LCDdisplay("SAFE OPEN");
     LCDGotoXY(1,0);
    }
    }
    else
{
     if(!strcmp(arr,pass))
     {
      LCDdisplay("SAFE OPEN");
      LCDGotoXY(1,0);
      PORTA=1;//open the safe
     }
     else
     {
      LCDdisplay("ERROR");
      LCDGotoXY(1,0);
      LCDdisplay("WRONG PASSWORD");
      _delay_ms(1000);
      function();
     }
    }
    strcpy(arr,"NUL");
   }
  }
  i=0;
}
k=Read_Keypad();
}
LCDclr();
DDRC=0x0f;
PORTC=0x00;
SREG|=(1<<7); //initializes the global interrupt i.e. sei();
DDRD&=~(1<<2); //declares INT0 as input pin
PORTD|=(1<<2); //pull-up enabled
GICR|=(1<<INT0); //enables INT0
GIFR|=(1<<INTF0); //enables INT0 flag for ISR recognition
MCUCR|=(1<<SM0)|(1<<SM1)|(1<<SE); //sleep mode enabled
MCUCR&=~(1<<SE); //sleep mode disabled
}
}
ISR(INT0_vect)
{
k=Read_Keypad();
GICR&=~(1<<INT0);
GIFR&=~(1<<INTF0);
i=0;j=0;strcpy(arr,"NUL");
}
