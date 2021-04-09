/*
 * SPI.c
 *
 * Created: 4/6/2021 10:24:57 PM
 * Author : Sadat Rafi
 * Bangladesh
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile char exit_permission = '0';

ISR(SPI_STC_vect){PORTD = SPDR; exit_permission = '1';}

int main(void)
{
    SPCR |= 0b11010011;
	sei();
	/* Replace with your application code */
    while (1) 
    {
		DDRB |= (1<<3)|(1<<5);
		DDRD |= 0xFF;	
		SPDR = 5;
		exit_permission = '0';
		while(1)
		{
			if(exit_permission == '1') 
				break;
		}
		_delay_ms(1000);
    }
}

