/*
 * GccApplication1.c
 *
 * Created: 2/9/2020 7:57:07 PM
 * Author : abHelal
 */ 

#include <avr/io.h>


int main(void)
{	DDRD=0xff;
	DDRA=0x00;
    /* Replace with your application code */
    while (1) 
    {
		if(PINA==0x01)
		{
			PORTD=0xFF;
		}
		else
		{
			PORTD=0x00;
		}

	}

}