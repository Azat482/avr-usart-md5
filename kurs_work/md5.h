#ifndef MD5_H_
#define MD5_H_

#include "main.h"

#include<math.h>
#include<stdio.h>
#include<stdint.h>
#include<string.h>

#define little_endian 0
#define big_endian    1

#define FunF(x,y,z) (x & y) | (~x & z)
#define FunG(x,y,z) (x & z) | (~z & y)
#define FunH(x,y,z) (x ^ y ^ z)
#define FunI(x,y,z) (y ^ (~z | x))


void raund_func(uint32_t* a, uint32_t*b, uint32_t* c, uint32_t*d, uint32_t Xk, int S,  uint32_t Ti, uint32_t F_fun);
void bit_rotate(uint32_t* value, int S);
bool endian();
void setUpBuff(uint32_t* a, uint32_t* b, uint32_t* c, uint32_t* d);
int getNewLen(int len);
uint8_t* preparation(unsigned char* str, int len);
unsigned char* gethash_md5(unsigned char* input, int lenght);

#endif