/*
 * LedControl.c
 *
 * Created: 2/2/2020 8:28:07 PM
 * Author : abHelal
 */ 

#include <avr/io.h>


int main(void)
{	DDRA &= ~(0x01);
	DDRB|=0x01;
	PORTA |= 0x01;
	
    /* Replace with your application code */
    while (1) 
    {
		if (PINA&(1<<0x00))
		{
			PORTB &= ~0x01;
		}
		else
		{
			PORTB |= 0x01;	
		}
		
		
    }
}

