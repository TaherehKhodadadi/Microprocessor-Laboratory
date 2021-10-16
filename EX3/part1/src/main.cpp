
#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{
	//configure outputs
   			DDRD |= (1<<PORTD0); //set pin D0 as an output
	PORTC|= (1<<PORTC4);			//set pin C4 & C5 as outputs - digital controls
	
	
	//configure timer 1
	//toggle OCR1A to CTC, run in clear timer on compare
	TCCR1A = (0<<COM1A1)|(0<<COM1A0)|(0<<WGM11)|(0<<WGM10); 
	
	//toggle CTC mode on timer, clock N=64
	TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS12)|(1<<CS11)|(0<<CS10);

	OCR1A = 62499;								//N=64--->(.5s)*(16mhz/64)
	
								
	while (1)									//do nothing until interrupt occurs every .25s, checks inputs and updates outputs
  {
	  
		  
	}
}
	
	
ISR(TIMER1_COMPA_vect)							//stores interrupt address/timer compare interrupt service routine
{
	PORTC ^=(1<<PORTC4);						//Breadcrumb toggle
							
	
		PORTC|=(1<<PORTC4);						//set digital control 1 high
		
		
		switch(PINC&0b00001111){				//read-in PINC and mask for PC0 through PC3
												//maps the correct output for 7-segment display
												
			case 0: PORTD = 0x01; break;		
			case 1: PORTD = 0x4F; break;
			case 2: PORTD = 0x12; break;		
			case 3: PORTD = 0x06; break;		
			case 4: PORTD = 0x4C; break;		
			case 5: PORTD = 0x24; break;		
			case 6: PORTD = 0x20; break;		
			case 7: PORTD = 0x0F; break;	
			case 8: PORTD = 0x00; break;		
			case 9: PORTD = 0x0C; break;									
	}
	
	
	}
