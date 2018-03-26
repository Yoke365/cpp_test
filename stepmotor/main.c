#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "stepmotor.h"

#define PACKED __attribute__((packed))

struct test_desc{
	uint8_t a;
	uint16_t b;
	uint8_t c;
}PACKED;


int main(int argc, char argv[])
{    
	// address_poll_handler(0x00);
	// address_set_handler(0x01);
	// speed_init_handler(0x01);
	// speed_run_handler(0x01);
	// add_speed_time_handler(0x01);

	// limit_switch_handler(0x01);
	// pulse_set_handler(0x01);
	
	// stop_handler(0x01);
	// state_poll_handler(0x01);
    
    printf("test_desc: %d\r\n", sizeof(struct test_desc));
    //stepmotor_test();
	printf("test\r\n");
	return 0;
}


