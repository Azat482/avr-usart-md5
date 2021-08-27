/*
 * usart.cpp
 *
 * Created: 16.03.2021 14:43:50
 *  Author: SS84_ttr
 */ 


#include "usart.h"

void USART_init(unsigned int speed)
{
	DDRB  |= (1<<PB7);
	PORTB |= (1<<PB7);
	//set speed
	//on tx and rx
	//interruption - on
	//2 stop bit, 8 bit data
	UBRR1H = (unsigned char)(speed>>8);
	UBRR1L = (unsigned char)(speed);
	UCSR1B = (1 << RXCIE1) | (1 << RXEN1) | (1 << TXEN1);
	UCSR1C = (1 << USBS1)|(1 << UCSZ11)|(1 << UCSZ10);
	UCSR1B &= ~(1<<UCSZ12);
	_delay_ms(1000);
	PORTB |= (0<<PB7);
}

void USART_TX(unsigned char mess)
{
	while( !(UCSR1A & (1<<UDRE1)) ); //waiting for emty register UDR
	UDR1 = mess;
}

unsigned char* USART_RX()
{
	while ( !(UCSR1A & (1 << UDRE1)) );
	unsigned char* mess = (unsigned char*)UDR1;
	return mess;
}