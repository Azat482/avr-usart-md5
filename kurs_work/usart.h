/*
 * usart.h
 *
 * Created: 16.03.2021 14:41:22
 *  Author: SS84_ttr
 */ 


#ifndef USART_H_
#define USART_H_

#include "main.h"


void USART_init(unsigned int speed);
void USART_TX(unsigned char mess);
unsigned char* USART_RX();


#endif /* USART_H_ */