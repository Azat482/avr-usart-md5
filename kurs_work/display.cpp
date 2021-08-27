/*
 * display.cpp
 *
 * Created: 17.03.2021 18:14:56
 *  Author: SS84_ttr
 */ 

#include "display.h"

void port_init()
{
	PORTCONTROL &= (~(1 << E)) & (~(1 << RW)) & (~(1 << RS));
	DDRTCONTROL |= (1 << E) | (1 << RW) | (1 << RS); //control port init (1 = output)
	PORTDATA = 0x00;
	DDRDATA = 0b11111111;    //data port init (1 = output)
}

void display_command(unsigned char c)
{
	PORTDATA = 0b00000000;
	PORTCONTROL = (1 << E);
	_delay_us(50);
	PORTCONTROL|= (~(1 << RS)) & (~(1 << RW));
	PORTDATA |= c;
	PORTCONTROL &= ~(1 << E);
	_delay_us(100);
}

void display_init()
{
	display_command(0b00111000); 
	display_command(0b00001100); 
	display_command(0b00000110);
	display_command(0b00010100); 
	display_command(0b00000010); 
	_delay_ms(5);
}

void display_clear()
{
	PORTDATA = 0b00000000;
	PORTCONTROL = (1 << E);
	_delay_us(50);
	PORTCONTROL|= (~(1 << RS)) & (~(1 << RW));
	PORTDATA |= 0b000000001;
	PORTCONTROL &= ~(1 << E);
	_delay_ms(5);
}

void cursor_position(unsigned char x, unsigned char y)
{
	PORTDATA = 0b00000000;
	PORTCONTROL = (1 << E);
	_delay_us(70);
	PORTCONTROL|= (~(1 << RS)) & (~(1 << RW));
	PORTDATA = (0x40 * y + x)|0b10000000;
	PORTCONTROL &= ~(1 << E);
	_delay_us(70);
}
 
void display_send(unsigned char *mess, unsigned char x, unsigned char y)
{
	cursor_position(x, y);
	for(int i = 0; i < (int)strlen((char*)mess); i++)
	{
		PORTDATA = 0b00000000;
		PORTCONTROL = (1 << E);
		_delay_us(70);
		PORTCONTROL |= (1 << RS);
		PORTDATA |= (char)mess[i];
		_delay_us(70);
		PORTCONTROL  = ~(1 << E);
		_delay_us(100);
	}
}