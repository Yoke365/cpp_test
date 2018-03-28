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



int main(int argc, char argv[])
{    
    printf("start\r\n");
    probe();
	return 0;
}


