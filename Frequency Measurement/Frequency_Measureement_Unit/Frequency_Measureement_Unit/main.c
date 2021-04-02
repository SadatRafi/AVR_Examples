/*
 * Transmitting_int_float.c
 * ATMEGA328P
 *
 * Created: 3/30/2021 12:51:55 PM
 * Author : Sadat Rafi
 *          Bangladesh
 */ 

#define F_CPU 8000000
#define F_CPU_Div_16 F_CPU/16

#include <stdio.h>         //Cointais defination for snprintf(), sprintf(), printf(), etc
#include <stdlib.h>        //Cointais defination for itoa(), dtostrf() & etc
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int i,count,f_measure_flag = 0;
float time_period=1,f=1;
volatile char k;
char f_buff[5];

ISR(INT0_vect)
{
	count = TCNT1;
	TCNT1 = 0;
	f_measure_flag = 1;
}

ISR(USART_UDRE_vect)
{
	if(k == '1' && i<=4) {UDR0 = f_buff[i];i++;}
	else if(k == '1' && i>4) {UCSR0B &=~ (1<<UDRIE0);i=0;UDR0 = ' ';}
	UCSR0B |= (1<<RXEN0);
}

ISR(USART_RX_vect)
{
	k = UDR0;
	UCSR0B |=(1<<UDRIE0);
	UCSR0B &=~ (1<<RXEN0);
}

void int_UART(int Baud_Rate)
{
	UBRR0 |= (F_CPU_Div_16/Baud_Rate)-1;
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);   //Character Size 8 Bit
}

void int_Counter1_16(void)
{
	TCCR1A &=~ 0b11110011;
	TCCR1B |= 0b00000100; 
}

void int_Ext_Hard_Int(void)
{
	EICRA |= 0b00000011;
	EIMSK |= (1<<INT0);
}

int main(void)
{	
	int_UART(9600);
	int_Counter1_16();
	int_Ext_Hard_Int();
	sei();
	
    while (1) 
    {
		if(f_measure_flag == 1)
		{
			time_period = count * 0.000032;
			f = 1/time_period;
			dtostrf(f,5,2,f_buff);
			f_measure_flag = 0;
		}
    }
}