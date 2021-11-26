#ifndef F_CPU
#define F_CPU 12000000UL
#endif

#include<atmega16.h>
#include<delay.h> 
#define KEY_PRT PORTB 
#define KEY_DDR DDRB 
#define KEY_PIN PINB 
#define LCD_PRT PORTC
#define LCD_DDR DDRC
#define LCD_PIN PINC

#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2
void lcdinit(void);
void lcd_gotoxy(unsigned char,unsigned char );
void lcdprint(char*);
void lcdcommand(unsigned char);
void delay_us(unsigned int);
void delay_ms(unsigned int );
void lcddata(unsigned char);
void keypadcall();
void stepperCW();
void stepperCCW();
unsigned char keypad[4][4]={{'7','8','9','L',},
{'4','5','6','R',},
{'1','2','3',' ',},
{'r','0','E',' ',}};
int main(void)
{
DDRC=0x00;
DDRA=0xFF;
lcdinit();
lcd_gotoxy(1,1);
lcdprint("DIRECTION:");
lcd_gotoxy(1,2);
lcdprint("SPEED:");
delay_us(100);
lcd_gotoxy(11,1);
keypadcall();
/*if(((PINA) & (0x01))==1)
{
//lcdcommand(0x01);
lcd_gotoxy(1,1);
lcdprint(" RESET ");
//lcd_gotoxy(7,2);
//lcdprint("0");
while(1)
{
PORTD=0x00;
}
} */
if(((PINA) & (0x40))==0)
//keypad[0][3])
{
lcd_gotoxy(11,1);
//keypadcall();
lcdprint("LEFT");
//lcdcommand(0x01);
lcd_gotoxy(7,2);
keypadcall();
keypadcall();
keypadcall();
keypadcall();
while(1)
{
stepperCCW();
delay_ms(10);
}
}
else
{
lcd_gotoxy(11,1);
//keypadcall();
lcdprint("RIGHT");
delay_us(100);
lcd_gotoxy(7,2);
keypadcall();
keypadcall();
keypadcall();
keypadcall();
while(1)
{
stepperCW();
delay_ms(10);
}
return 0;
}
void lcdinit()
{
LCD_DDR=0XFF;
LCD_PRT&=~(1<<LCD_EN);
delay_us(2000);
lcdcommand(0x33);
delay_us(100);
lcdcommand(0x32);
delay_us(100);
lcdcommand(0x28);
delay_us(100);
lcdcommand(0x0E);
delay_us(100);
lcdcommand(0x01);
delay_us(2000);
lcdcommand(0x06);
delay_us(100);
}
void lcdcommand(unsigned char cmnd)
{
LCD_PRT=(LCD_PRT & 0x0F)|(cmnd & 0xF0);
LCD_PRT&=~(1<<LCD_RS);
LCD_PRT&=~(1<<LCD_RW);
LCD_PRT|=(1<<LCD_EN);
delay_us(1);
LCD_PRT&=~(1<<LCD_EN);
delay_us(20);
LCD_PRT=(LCD_PRT & 0X0F)|(cmnd<<4);
LCD_PRT|=(1<<LCD_EN);
delay_us(1);
LCD_PRT&=~(1<<LCD_EN);
}
void delay_us(unsigned int d)
{
_delay_us(d);
}
void delay_ms(unsigned int d)
{
_delay_ms(d);
}
void lcd_gotoxy(unsigned char x,unsigned char y)
{
unsigned char firstcharadr[]={0x80,0xC0,0x94,0xD4};
lcdcommand(firstcharadr[y-1]+x-1);
delay_us(100);
}
void lcdprint(char *str)
{
unsigned char i=0;
while(str[i]!=0)
{
lcddata(str[i]);
i++;
}
}
void lcddata(unsigned char data)
{
LCD_PRT =(LCD_PRT & 0X0F)|(data & 0XF0);
LCD_PRT|=(1<<LCD_RS);
LCD_PRT&=~(1<<LCD_RW);
LCD_PRT|=(1<<LCD_EN);
delay_us(1);
LCD_PRT&= ~(1<<LCD_EN);
delay_us(20);
LCD_PRT=(LCD_PRT & 0X0F)|(data<<4);
LCD_PRT|=(1<<LCD_EN);
delay_us(1);
LCD_PRT&=~(1<<LCD_EN);
}
void keypadcall(void)
{
KEY_DDR=0XF0;
KEY_PRT=0XFF;
do
{
KEY_PRT &=0X0F; 
colloc=(KEY_PIN&0X0F); 
}while(colloc!=0X0F) ; 
do
{
do
{ delay_ms(5); //call delay
colloc=(KEY_PIN&0X0F);
} while (colloc==0X0F); 
delay_ms(5); 
colloc=(KEY_PIN&0X0F);
} while (colloc==0X0F);
while(1)
{KEY_PRT=0XEF; //ground row 0
colloc=(KEY_PIN&0X0F); //read the columns
if(colloc!=0X0F) //column detected
{
rowloc=0; 
break;
}
KEY_PRT=0XDF;
colloc=(KEY_PIN&0X0F);
if(colloc!=0X0F) 
{
rowloc=1;
break; 
}
KEY_PRT=0XBF; 
colloc=(KEY_PIN&0X0F); 
if(colloc!=0X0F)
{
rowloc=2; 
break; 
}
KEY_PRT=0X7F; 
colloc=(KEY_PIN&0X0F);
rowloc=3; 
break; 
}
if (colloc==0X0E)
lcddata(keypad[rowloc][0]);
else if (colloc==0x0D)
lcddata(keypad[rowloc][1]);
else if (colloc==0X0B)
lcddata(keypad[rowloc][2]);
else
lcddata(keypad[rowloc][3]);
}
void stepperCW()
{
PORTD=0x0C;
_delay_ms(5);
PORTD=0x06;
_delay_ms(5);
PORTD=0x03;
_delay_ms(5);
PORTD=0x09;
_delay_ms(5);
}
void stepperCCW()
{
PORTD=0x09;
_delay_ms(5);
PORTD=0x03;
_delay_ms(5);
PORTD=0x06;
_delay_ms(5);
PORTD=0x0C;
_delay_ms(5);
}
