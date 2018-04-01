#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "stepmotor.h"
#include "protocol.h"

extern void cmd_parase_test();

uint32_t high_level_width=0; 
uint32_t high_level_width_old=0;
bool high_level_update = false;

uint8_t value[4] = { 12, 16, 20, 24};
uint32_t tick= 0;
uint32_t state= 0;

void test(void)
{	
	++tick;
	if ( tick == 200) {
		
		high_level_width = value[state];
		printf("high_level_width:%d\r\n", high_level_width);

		++state;
		if ( state == 4) {
			state = 0;
			printf("state:%d\r\n", state);
		}

		tick = 0;
	}
}

int main(int argc, char argv[])
{    
    printf("start\r\n");
    
    for (uint32_t i =0; i < 8000; i++) {
    	test();
    }
    //cmd_parase_test();
	return 0;
}


