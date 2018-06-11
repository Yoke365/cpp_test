#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "nuttx_i2c.h"

uint32_t high_level_width=0; 
uint32_t high_level_width_old=0;
bool high_level_update = false;

uint8_t value[4] = { 12, 16, 20, 24};
uint32_t tick= 0;
uint32_t state= 0;

const uint8_t ledLinear[] =
{0,9,10,11,12,13,15,17,19,22,24,26,28,30,32,35,38,41,44,47,49,51,53,56,58 ,60,63,65,67,69,71,73,75,77,79,81,82,84,86,88,70,72,74,76,78,80,82,84,86, 88,90,92,94,97,99,101,103,105,107,109,111,113,115,117,119,121,124,127,131 ,135,138,142,146,149,153,157,160,164,168,172,176,180,184,188,192,196,200, 204,208,212,216,220,224,228,232,236,240,243,247,252,255
};

typedef struct  {
	uint8_t a;
	uint8_t b;
}frame_t;

frame_t frame_1 ;
frame_t frame_2 ;
frame_t frame_3 ;

frame_t *frame_group[] = {&frame_1, &frame_2, &frame_3};

void test()
{
	
}

int main(int argc, char argv[])
{    
    printf("b\r\n");

    uint16_t len = 0;

    len = sizeof(ledLinear);
    printf("len:%d\r\n", len);
	return 0;
}


