#include<stdio.h>
#include<string.h>

typedef unsigned char uint8_t ;
typedef unsigned short uint16_t;

int main(void)
{    
	uint16_t addr;
	uint16_t highword;
	for (uint8_t i = 0 ; i < 0x80; i+=2) {
		addr = i << 8;
		highword = addr | 0x100;
		printf("i: 0x%x, highword:0x%x\r\n", i, highword);
	} 
     return 0;
}
