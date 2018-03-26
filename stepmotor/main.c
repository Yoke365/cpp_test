#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "stepmotor.h"
#include "protocol.h"

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
    
//    printf("test_desc: %d\r\n", sizeof(struct test_desc));
    //stepmotor_test();
	// printf("test\r\n");
    stemp_code_creat();

	for (uint16_t i = 0; i < 20000; i+=2) {
		uint8_t local_type = 0;
		uint16_t value;
		pwm_cmd_prase(i, &local_type, &value);
	}

	return 0;
}


