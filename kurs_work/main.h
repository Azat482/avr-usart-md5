/*
 * main.h
 *
 * Created: 07.03.2021 16:15:29
 *  Author: SS84_ttr
 */ 


#ifndef MAIN_H_
#define MAIN_H_
#define F_CPU 16000000UL// Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "md5.h"
#include "display.h"
#include "code_gray.h"
 


void lightIndicator();
void sendTestMessage(unsigned char *str);
void read_encoders(char* es6p1, char* es6p2);

#endif /* MAIN_H_ */