/*
 * Transmitting_int_float.c
 * ATMEGA328P
 *
 * Created: 3/30/2021 12:51:55 PM
 * Author : Sadat Rafi
 *          Bangladesh
 */ 

#define F_CPU 16000000
#define F_CPU_Div_16 F_CPU/16

#include <stdio.h>         //Cointais defination for snprintf(), sprintf(), printf(), etc
#include <stdlib.h>        //Cointais defination for itoa(), dtostrf() & etc
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int i;
volatile char k;
char a_buff[6];
char b_buff[6];

ISR(USART_UDRE_vect)
{
	if(k == '1') {UDR0 = a_buff[i];}
	else if (k == '2') {UDR0 = b_buff[i];}
	i++;
	if(i > 5){UCSR0B &=~ (1<<UDRIE0);i=0;}
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
	sei();
}

int main(void)
{
    int a = 1024;
	float b = 255.55;
	
	itoa(a,a_buff,10);              //itoa converts integer into array; here 10 indicates it's a decimal number
	dtostrf(b,6,2,b_buff);
	
	int_UART(9600);
	
    while (1) 
    {
		
    }
}

