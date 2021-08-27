
#include "md5.h"

int getNewLen(int len)
{
    int NewLen = len;
    while( NewLen%64!=56) ++NewLen;
    return (NewLen + 8);
}

bool endian()
{
    uint32_t n= 1;
    uint8_t *i = (uint8_t*)(&n);
    if(*i == 1)
    {
        return little_endian;
    }
    else{
        return big_endian;
    }
}

uint8_t* preparation(unsigned char* str, int len)
{
    int new_len = getNewLen(len);
    int ln1 = (new_len - 8);
    //uint8_t* mass = new uint8_t[new_len];
	uint8_t* mass = (uint8_t*)malloc(new_len * sizeof(uint8_t));
    for(int i = 0; i < ln1; i++)
    {
        if(i < len)
        {
            mass[i] = str[i];
        }
        else if(i == len)
        {
            mass[i] = 0b10000000;
        }
        else
        {
            mass[i] = 0b00000000;
        }

    }

    uint64_t bitlenght = (uint64_t)(len * 8);
    //uint64_t bitlenght = 10000000;
    if(endian() == little_endian)
    {
        for(int i = ln1, j = 0; i < new_len; i++, j++)
        {
            mass[i] = (uint8_t)(bitlenght>>(j * 8));
        }
    }
    else if(endian() == big_endian)
    {
        for(int i = ln1, j = 7; i < new_len; i++, j--)
        {
            mass[i] = (uint8_t)(bitlenght>>(j * 8));
        }
    }
    //printf("%d\n", (int)endian());
    //if(endian() == big_endian)
	//{
	//	sendTestMessage((unsigned char*)"BIG ENDIAN");
	//}
	//if(endian() == little_endian)
	//{
	//	sendTestMessage((unsigned char*)"LITTLE ENDIAN");
	//}
	return mass;
}

void setUpBuff(uint32_t* a, uint32_t* b, uint32_t* c, uint32_t* d)
{
    if(endian() == little_endian)
    {
        *a = 0x67452301;
        *b = 0xefcdab89;
        *c = 0x98badcfe;
        *d = 0x10325476;
    }
    else if(endian() == big_endian)
    {
        *a = 0x01234567;
        *b = 0x89abcdef;
        *c = 0xfedcba98;
        *d = 0x76543210;
    }
}

void setTElem(uint32_t* T, int n)   //it so bad in avr
{
    for(int i = 0; i < n; i++)
    {
        T[i] = ( pow(2, 32) * fabs(sin(i+1)) );
    }
}

void bit_rotate(uint32_t* value, int S)
{
    //uint32_t temp_bef = *value;
    *value = (*value << S) | (*value >> (32 - S));

    //printf("\n\nrotate bits S: %d", S);
    //uint32_t  temp_aft = *value;

    //printf("\nbefore rotate: ");
    //for(int i = 0; i < 32; i++)
    //{
    //    printf("%c", (temp_bef & 0x80000000) ? '1' : '0' );
    //    temp_bef<<=1;
    //}
    //printf("\nafter rotate: ");
    //for(int i = 0; i < 32; i++)
    //{
    //printf("%c", (temp_aft & 0x80000000) ? '1' : '0' );
    //    temp_aft<<=1;
    //}
    //printf("\n\n");

}

void raund_func(uint32_t* a, uint32_t*b, uint32_t* c, uint32_t*d, uint32_t Xk, int S,  uint32_t Ti, uint32_t F_fun)
{
    uint32_t buff = (*a + F_fun + Xk + Ti);
    bit_rotate( &buff,  S);
    *a = *b +  buff;
}

unsigned char* gethash_md5(unsigned char* input, int lenght) //main function
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;

    int firstLenght = lenght;
    int new_lenght = getNewLen(firstLenght);
    uint8_t* stream;
    stream = preparation(input, firstLenght); //padding to evelation
    //int T_N = 64;
    //uint32_t* T = (uint32_t*)malloc(T_N * sizeof(uint32_t));
	uint32_t T[64] = 
	{
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};
	
	
	///////////////////////////////////
    //USART_TX(0x0d);//переход в начало строки
    //USART_TX(0x0a);//переход на новую строку
	//for(int i = 0; i < new_lenght; i++)
    //{
    //    printf("new padded massive %d\t%d\t%d\n", new_lenght, i, stream[i]);
	//	char* buff = (char*)malloc(32);
	//	sprintf(buff, "%d", stream[i]);
	//	sendTestMessage((unsigned char*)buff);
	//	USART_TX(0x0d);//переход в начало строки
	//	USART_TX(0x0a);//переход на новую строку
	//}
    ///////////////////////////////////

    setUpBuff(&a, &b, &c, &d);
    //setTElem(T, T_N);

    //////////////////////////////
    //printf("a:  %x\n", a);
    //printf("b:  %x\n", b);
    //printf("c:  %x\n", c);
    //printf("d:  %x\n", d);
    ////////////////////////////////

    for(int _start = 0, _end = 64; _start < new_lenght; _start+=64, _end+=64)
    {
        uint32_t a_tmp = a;
        uint32_t b_tmp = b;
        uint32_t c_tmp = c;
        uint32_t d_tmp = d;
        //uint32_t* X = new uint32_t[16];
		uint32_t* X = (uint32_t*)malloc(16 * sizeof(uint32_t));
		
        for(int i = _start, j = _start + 4, index = 0; i < _end; i += 4, j += 4, index++)
        {
            //printf("index = %d\n", index);
            X[index] = 0;
            for(int p = i, q = 0; p < j; p++, q++)
            {
                //printf("p = %d\tq = %d\n", p, q);
                X[index] = X[index]  |  (  (uint32_t)stream[p] << (q * 8) );
            }
            //printf("X[%u] = %u\n", index, X[index]);
        }

        //////////////////////////////////////////////
        //USART_TX(0x0d);//переход в начало строки
        //USART_TX(0x0a);//переход на новую строку
		//for(int i = 0; i < 16; i++)
        //{
        //    uint32_t temp_bef = X[i];
        //    for(int i = 0; i < 32; i++)
        //    {
		//	char* bufff = (char*)malloc(1 * sizeof(char));
        //    sprintf(bufff, "%c",    ((temp_bef & 0x80000000) ? '1' : '0') );
        //    sendTestMessage((unsigned char*)bufff);
		//	temp_bef<<=1;
        //    }
            //printf("\t%u\n", (uint8_t)X[i]);
		//	USART_TX(0x0d);//переход в начало строки
		//	USART_TX(0x0a);//переход на новую строку
        //}
        //printf("\n");
        //USART_TX(0x0d);//переход в начало строки
        //USART_TX(0x0a);//переход на новую строку
		///////////////////////////////////////////////

        //1
        raund_func(&a, &b, &c, &d, X[0], 7, T[0],    FunF(b, c, d));
        raund_func(&d, &a, &b, &c, X[1], 12, T[1],   FunF(a, b, c));
        raund_func(&c, &d, &a, &b, X[2], 17, T[2],   FunF(d, a, b));
        raund_func(&b, &c, &d, &a, X[3], 22, T[3],   FunF(c, d, a));

        raund_func(&a, &b, &c, &d, X[4], 7, T[4],    FunF(b, c, d));
        raund_func(&d, &a, &b, &c, X[5], 12, T[5],   FunF(a, b, c));
        raund_func(&c, &d, &a, &b, X[6], 17, T[6],   FunF(d, a, b));
        raund_func(&b, &c, &d, &a, X[7], 22, T[7],   FunF(c, d, a));

        raund_func(&a, &b, &c, &d, X[8], 7, T[8],    FunF(b, c, d));
        raund_func(&d, &a, &b, &c, X[9], 12, T[9],   FunF(a, b, c));
        raund_func(&c, &d, &a, &b, X[10], 17, T[10], FunF(d, a, b));
        raund_func(&b, &c, &d, &a, X[11], 22, T[11], FunF(c, d, a));

        raund_func(&a, &b, &c, &d, X[12], 7, T[12],  FunF(b, c, d));
        raund_func(&d, &a, &b, &c, X[13], 12, T[13], FunF(a, b, c));
        raund_func(&c, &d, &a, &b, X[14], 17, T[14], FunF(d, a, b));
        raund_func(&b, &c, &d, &a, X[15], 22, T[15], FunF(c, d, a));

        //2
        raund_func(&a, &b, &c, &d, X[1], 5, T[16],   FunG(b, c, d));
        raund_func(&d, &a, &b, &c, X[6], 9, T[17],   FunG(a, b, c));
        raund_func(&c, &d, &a, &b, X[11], 14, T[18], FunG(d, a, b));
        raund_func(&b, &c, &d, &a, X[0], 20, T[19],  FunG(c, d, a));

        raund_func(&a, &b, &c, &d, X[5], 5, T[20],   FunG(b, c, d));
        raund_func(&d, &a, &b, &c, X[10], 9, T[21],  FunG(a, b, c));
        raund_func(&c, &d, &a, &b, X[15], 14, T[22], FunG(d, a, b));
        raund_func(&b, &c, &d, &a, X[4], 20, T[23],  FunG(c, d, a));

        raund_func(&a, &b, &c, &d, X[9], 5, T[24],   FunG(b, c, d));
        raund_func(&d, &a, &b, &c, X[14], 9, T[25],  FunG(a, b, c));
        raund_func(&c, &d, &a, &b, X[3], 14, T[26],  FunG(d, a, b));
        raund_func(&b, &c, &d, &a, X[8], 20, T[27],  FunG(c, d, a));

        raund_func(&a, &b, &c, &d, X[13], 5, T[28],  FunG(b, c, d));
        raund_func(&d, &a, &b, &c, X[2], 9, T[29],   FunG(a, b, c));
        raund_func(&c, &d, &a, &b, X[7], 14, T[30],  FunG(d, a, b));
        raund_func(&b, &c, &d, &a, X[12], 20, T[31], FunG(c, d, a));

        //3
        raund_func(&a, &b, &c, &d, X[5], 4, T[32],   FunH(b, c, d));
        raund_func(&d, &a, &b, &c, X[8], 11, T[33],  FunH(a, b, c));
        raund_func(&c, &d, &a, &b, X[11], 16, T[34], FunH(d, a, b));
        raund_func(&b, &c, &d, &a, X[14], 23, T[35], FunH(c, d, a));

        raund_func(&a, &b, &c, &d, X[1], 4, T[36],   FunH(b, c, d));
        raund_func(&d, &a, &b, &c, X[4], 11, T[37],  FunH(a, b, c));
        raund_func(&c, &d, &a, &b, X[7], 16, T[38],  FunH(d, a, b));
        raund_func(&b, &c, &d, &a, X[10], 23, T[39], FunH(c, d, a));

        raund_func(&a, &b, &c, &d, X[13], 4, T[40],  FunH(b, c, d));
        raund_func(&d, &a, &b, &c, X[0], 11, T[41],  FunH(a, b, c));
        raund_func(&c, &d, &a, &b, X[3], 16, T[42],  FunH(d, a, b));
        raund_func(&b, &c, &d, &a, X[6], 23, T[43],  FunH(c, d, a));

        raund_func(&a, &b, &c, &d, X[9], 4, T[44],   FunH(b, c, d));
        raund_func(&d, &a, &b, &c, X[12], 11, T[45], FunH(a, b, c));
        raund_func(&c, &d, &a, &b, X[15], 16, T[46], FunH(d, a, b));
        raund_func(&b, &c, &d, &a, X[2], 23, T[47],  FunH(c, d, a));

        //4
        raund_func(&a, &b, &c, &d, X[0], 6, T[48],   FunI(b, c, d));
        raund_func(&d, &a, &b, &c, X[7], 10, T[49],  FunI(a, b, c));
        raund_func(&c, &d, &a, &b, X[14], 15, T[50], FunI(d, a, b));
        raund_func(&b, &c, &d, &a, X[5], 21, T[51],  FunI(c, d, a));

        raund_func(&a, &b, &c, &d, X[12], 6, T[52],  FunI(b, c, d));
        raund_func(&d, &a, &b, &c, X[3], 10, T[53],  FunI(a, b, c));
        raund_func(&c, &d, &a, &b, X[10], 15, T[54], FunI(d, a, b));
        raund_func(&b, &c, &d, &a, X[1], 21, T[55],  FunI(c, d, a));

        raund_func(&a, &b, &c, &d, X[8], 6, T[56],   FunI(b, c, d));
        raund_func(&d, &a, &b, &c, X[15], 10, T[57], FunI(a, b, c));
        raund_func(&c, &d, &a, &b, X[6], 15, T[58],  FunI(d, a, b));
        raund_func(&b, &c, &d, &a, X[13], 21, T[59], FunI(c, d, a));

        raund_func(&a, &b, &c, &d, X[4], 6, T[60],   FunI(b, c, d));
        raund_func(&d, &a, &b, &c, X[11], 10, T[61], FunI(a, b, c));
        raund_func(&c, &d, &a, &b, X[2], 15, T[62],  FunI(d, a, b));
        raund_func(&b, &c, &d, &a, X[9], 21, T[63],  FunI(c, d, a));

        a += a_tmp;
        b += b_tmp;
        c += c_tmp;
        d += d_tmp;
		
		free(X);
    }
	free(stream);
    /////
	//char* ffd = (char*)malloc(32 * sizeof(char));
	//sprintf(ffd, "%u", a);
	//sendTestMessage((unsigned char*)ffd); 
	//USART_TX(0x0d);//переход в начало строки
	//USART_TX(0x0a);//переход на новую строку
	
	
	////
	
	
	uint8_t HASH_MD5[16];
    int s;
    //USART_TX(0x0d);//переход в начало строки
    //USART_TX(0x0a);//переход на новую строку
	for(int i = 0; i < 16; i++)
    {
        HASH_MD5[i] = 0;
        if( i < 4 )
        {
            s = i;
            HASH_MD5[i] = a >> (i * 8);
        }
        if( i < 8 && i >= 4)
        {
            s = i - 4;
            HASH_MD5[i] = b >> (s * 8);
        }
        if( i < 12 && i >= 8)
        {
            s = i - 8;
            HASH_MD5[i] = c >> (s * 8);
        }
        if( i < 16 && i >= 12)
        {
            s = i - 12;
            HASH_MD5[i] = d >> (s * 8);
        }
		//char* bf = (char*)malloc(1 * sizeof(char));
		//sprintf(bf, "%x", HASH_MD5[i]);
		//sendTestMessage((unsigned char*)bf);
		//USART_TX(0x0d);//переход в начало строки
		//USART_TX(0x0a);//переход на новую строку
    }
    char* RESULT = (char*)malloc(33 * sizeof(char));
	for(int i = 0, j = 0; i < 16; i++, j += 2)
    {
        char temp[2];
        sprintf(temp, "%x", HASH_MD5[i]);
        if( strlen(temp)  == 1 )
        {
            char buff = temp[0];
            temp[1] = buff;
            temp[0] = '0';
        }
        RESULT[j] = temp[0];
        RESULT[j + 1] = temp[1];
    }
    RESULT[32] = '\0';
    return (unsigned char*)RESULT;
}



