/*
 * UART_TX.h
 * This code does not use interrupts
 * Created: 4/30/2021 7:17:27 AM
 * Processor Amega328p
 * Author: Sadat Rafi
 */ 

#include <stdlib.h> 
#define F_CPU_Div_16 F_CPU/16

#ifndef UART_TX_H_
#define UART_TX_H_

void space(void)
{
	if((UCSR0A & 32) != 0) UDR0 = ' ';
	while(1) {if((UCSR0A & 32) != 0) break;}
}

void int_UART(int Baud_Rate)
{
	UBRR0 |= (F_CPU_Div_16/Baud_Rate)-1; //Baud Rate Selected
	UCSR0B |= (1<<TXEN0);                //TX Enabled
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);   //Character Size 8 Bit
}

void send_int(int a)
{
	char a_buff[4];
	itoa(a,a_buff,10);
	int i_h=0;
	while(1)
	{
		if((UCSR0A & 32) != 0)
		{
			UDR0 = a_buff[i_h];
			i_h++;
			if(i_h >= 4) break;
		}
	}
	while(1) {if((UCSR0A & 32) != 0) break;}
}

void send_float(float b)
{
	char b_buff[6];
	dtostrf(b,6,2,b_buff);
	int i_h=0;
	while(1)
	{
		if((UCSR0A & 32) != 0)
		{
			UDR0 = b_buff[i_h];
			i_h++;
			if(i_h > 5) break;
		}
	}
	while(1) {if((UCSR0A & 32) != 0) break;}
}



#endif /* UART_TX_H_ */