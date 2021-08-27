/*
 * code_gray.cpp
 *
 * Created: 22.03.2021 12:47:56
 *  Author: SS84_ttr
 */ 

#include "code_gray.h"

uint8_t enc_gray(uint8_t a)
{
	return a ^ (a >> 1);
}

uint8_t dec_gray(uint8_t b)
{
	uint8_t rez;
	for(rez = 0 ; b; b >>= 1)
	{
		rez ^= b;
	}
	return rez;
}