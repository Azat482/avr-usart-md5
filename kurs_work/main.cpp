/*
 * kurs_work.cpp
 *
 * Created: 07.03.2021 16:13:02
 * Author : SS84_ttr
 */ 

#include "main.h"

void lightIndicator()
{
	DDRB = (1<<PB7);
	PORTB = (1 << PB7);
	_delay_ms(250);
	PORTB = (0 << PB7);
	_delay_ms(50);
	PORTB = (1 << PB7);
	_delay_ms(250);
	PORTB = (0 << PB7);
	_delay_ms(2000);
}

void sendTestMessage(unsigned char *str)
{	
	for(int i = 0; i < (int)strlen((char*)str); i++)
	{
		USART_TX(str[i]);
	}
}

ISR(USART1_RX_vect)
{	
	char request = (char)UDR1;
	USART_TX(0x0d);//переход в начало строки
	USART_TX(0x0a);//переход на новую строку
	if(request == '1')
	{
		char es6p1[16];
		char es6p2[16];
		read_encoders(es6p1, es6p2);
		char trsmt[32];
		sprintf(trsmt, "%s %s", es6p1, es6p2);
		char* hashtr = (char*)gethash_md5((unsigned char*)trsmt, (int)strlen(trsmt) );
		sendTestMessage((unsigned char*)"data: ");
		sendTestMessage((unsigned char*)trsmt);
		USART_TX(0x0d);//переход в начало строки
		USART_TX(0x0a);//переход на новую строку
		sendTestMessage((unsigned char*)"hash data: ");
		sendTestMessage((unsigned char*)hashtr);
		USART_TX(0x0d);//переход в начало строки
		USART_TX(0x0a);//переход на новую строку
		sendTestMessage((unsigned char*)"stlen: ");
		char len[10];
		sprintf(len, "%d", strlen(trsmt) );
		sendTestMessage((unsigned char*)len );
		USART_TX(0x0d);//переход в начало строки
		USART_TX(0x0a);//переход на новую строку
		free(hashtr);
	}
	else if(request == '2')
	{
		sendTestMessage((unsigned char*)"over command");
		USART_TX(0x0d);//переход в начало строки
		USART_TX(0x0a);//переход на новую строку
	}
	else
	{
		sendTestMessage((unsigned char*)"no command");
		USART_TX(0x0d);//переход в начало строки
		USART_TX(0x0a);//переход на новую строку
	}
}

void read_encoders(char* es6p1, char* es6p2)
{
	uint8_t enc1, enc2, enc11, enc22;
	char* str1  = (char*)"BVG: ";
	char* str2 = (char*)"BFG: ";
	const uint8_t smech = 80; //смещение
	enc1 = 15 + smech;									
	enc2 = 10 + smech;									
	enc1 = enc_gray(enc1);						
	enc2 = enc_gray(enc2);						
	
	enc11 =  dec_gray(enc1);					
	enc22 = dec_gray(enc2);						
	sprintf(es6p1, "%s%d", str1, (int)enc11);	
	sprintf(es6p2, "%s%d", str2, (int)enc22);	
}

int main(void)
{	
	port_init();
	display_init();
	USART_init(MYUBRR);
	sei();
	sendTestMessage((unsigned char*)"It`s working!"); 
	USART_TX(0x0d);//переход в начало строки
	USART_TX(0x0a);//переход на новую строку
	display_clear();
	display_send((unsigned char*)"Display is", 0, 0);
	display_send((unsigned char*)"work! :) ", 0, 1);
	_delay_ms(2000);
	display_clear();
	unsigned char* befHashMess = (unsigned char*)"secret information";
	unsigned char* aftHashMess = gethash_md5(befHashMess, strlen( (char*)befHashMess) );
	sendTestMessage(befHashMess);
	USART_TX(0x0d);
	USART_TX(0x0a);
	sendTestMessage(aftHashMess);
	USART_TX(0x0d);
	USART_TX(0x0a);
	lightIndicator();		
	while(1) 
    {
		char es6p1[16];
		char es6p2[16];
		read_encoders(es6p1, es6p2);
		display_clear();
		_delay_ms(80);
		display_send((unsigned char*)es6p1, 0,  0);
		display_send((unsigned char*)es6p2, 0 , 1);
		lightIndicator();
	}
	
	return 0;
}

