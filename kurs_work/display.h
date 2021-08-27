/*
 * display.h
 *
 * Created: 17.03.2021 18:14:34
 *  Author: SS84_ttr
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "main.h"

#define PORTDATA PORTA
#define DDRDATA DDRA
#define PORTCONTROL PORTC
#define DDRTCONTROL DDRC
#define DB7 PA7
#define DB6 PA6
#define DB5	PA5
#define DB4 PA4
#define DB3	PA3
#define DB2 PA2
#define DB1	PA1
#define DB0 PA0
#define E PC6
#define RW PC7
#define RS PC4


void port_init();
void display_init();
void display_command(unsigned char c);
void display_clear();
void cursor_position(unsigned char x, unsigned char y);
void display_send(unsigned char* mess, unsigned char x, unsigned char y);




#endif /* DISPLAY_H_ */