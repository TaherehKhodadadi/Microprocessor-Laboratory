
#include <mega16.h>

// Alphanumeric LCD functions
#include <alcd.h>

#include <delay.h> 

#define  F_CPU 1000000ul

#define FRD_RIGHT      PD0  // to input 1 of l298
#define FRD_LEFT       PD1  //  to input 2 of l298
#define BWD_RIGHT      PD2  //  to input 3 of l298
#define BWD_LEFT       PD3  //  to input 4 of l298
#define SPEED_RIGHT    OCR0 // to enable pin 1
 
#define SPEED_LEFT     OCR2 // to enable pin 2
#define READ        bit_is_clear

int s0,s1,s2,s3,s4,s5,s6,s7,error=0,off=9;
int turn=1;
uint8_t powera,powera;



void initpwm(void)
{
    

TCCR0=(1<<COM01)|(1<<CS00)|(1<<CS01)|(1<<WGM00)|(1<<WGM01); //fast pwm ,64 prescalar, 8 bit
 
TCCR2|=(1<<WGM20)|(11<<WGM21)|(1<<COM21)|(1<<CS22); //fast pwm,64 prescalar.8 bit

DDRD|=(1<<PD7);  //setting as output
DDRB|=(1<<PB3); //setting as output

OCR0=0;//intialization

OCR2=0; //initialization

}


int main(void)
{
    initpwm(); //pwm initializationj                
    DDRA=0x00; //for 8 sensor input
    PORTA=0xff; //pullup
    DDRD|=(1<<FRD_RIGHT)|(1<<FRD_LEFT)|(1<<BWD_LEFT)|(1<<BWD_RIGHT); // for motor direction selection
    
    while(1)
 {  // first reading all the values of the sensor
    s1=0;
    s2=0;
    s3=0;
    s4=0;
    s5=0;
    s6=0;
    s7=0;
    s0=0;
    if (READ(PINA,PA0))
    {
      s0=1;
    }
    if (READ(PINA,PA1))
    {
      s1=2;
    }
    if (READ(PINA,PA2))
    {
      s2=3;
    }
    if (READ(PINA,PA3))
    {
      s3=4;
    }
    if (READ(PINA,PA4))
    {
      s4=5;
    }
    if (READ(PINA,PA5))
    {
      s5=6;
    }
    if (READ(PINA,PA6))
    {
      s6=7;
    }
    if (READ(PINA,PA7))
   {
     s7=8;
   }

   error=s0+s1+s2+s3+s4+s5+s6+s7; //error
   error=error-off;       
    turn=1800*error;     // pid's Proportion
    turn=turn/1000;
   powera=150+turn;
   powera=150-turn;
   if(powera>=150)
   {
      SPEED_RIGHT=powera; // given to right motor
      PORTD|=(1<<FRD_RIGHT); //selection for directiom
      PORTD &= ~(1<<BWD_RIGHT); 
      
   }
   else
   {
     SPEED_RIGHT=powera;
     PORTD|=(1<<BWD_RIGHT);
     PORTD &= ~(1<<FRD_RIGHT);
   }
   if(powera>=150)
   {
     SPEED_LEFT=powera;   //given to enable pin of left motor 
     PORTD|=(1<<FRD_LEFT);  // selection of directiom
     PORTD|=(1<<BWD_LEFT);
   }
   else
   {
     SPEED_LEFT=powera;
	 PORTD|=(1<<BWD_LEFT);
	 PORTD&= ~(1<<FRD_LEFT);
   }

  } 
 } 