#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "stepmotor.h"
#include "protocol.h"



void common_test(void)
{
  for (uint16_t i = 0; i < speed_init_base_value; i+=2) {
		uint8_t local_type = 0;
		uint16_t value =0;
		if (pwm_cmd_prase(i, &local_type, &value) == 0) {
			printf("type: 0x%x, value, %d, value_new:0x%x\r\n", local_type, i, value);
		}
	}
}


void speed_init_test(void)
{
	for (uint16_t i = speed_init_base_value; i < speed_run_base_value; i+=2) {
		uint8_t local_type = 0;
		uint16_t value =0;
		if (pwm_cmd_prase(i, &local_type, &value) == 0) {
			printf("type: 0x%x, value, %d, value_new:%d\r\n", local_type, i, value);
		}
	}
}
void speed_run_test(void)
{   
	for (uint16_t i = speed_run_base_value; i < add_speed_time_base_value; i+=2) {
		uint8_t local_type = 0;
		uint16_t value =0;
		if (pwm_cmd_prase(i, &local_type, &value) == 0) {
			printf("type: 0x%x, value, %d, value_new:%d\r\n", local_type, i, value);
		}
	}
	
}

void add_speed_time_test(void)
{  
	for (uint16_t i = add_speed_time_base_value; i < pulse_set_base_value; i+=2) {
		uint8_t local_type = 0;
		uint16_t value =0;
		if (pwm_cmd_prase(i, &local_type, &value) == 0) {
			printf("type: 0x%x, value, %d, value_new:%d\r\n", local_type, i, value);
		}
	}
   
}

void pulse_set_test(void)
{
	//for (uint16_t i = pulse_set_base_value; i < 17000; i+=2) {
		for (uint16_t i = pulse_set_base_value; i < (pulse_set_base_value + 20); i+=2) {
		uint8_t local_type = 0;
		uint16_t value =0;
		if (pwm_cmd_prase(i, &local_type, &value) == 0) {
			printf("type: 0x%x, value, %d, value_new:%d\r\n", local_type, i, value);
		}
	}
}

void run()
{
	if (pwm_cmd_prase(i, &local_type, &value) == 0) {
		printf("type: 0x%x, value, %d, value_new:%d\r\n", local_type, i, value);
	}
    
	switch (local_type) {
		case 0:
		    //执行a
			break;
		case 1:
	        //执行B
			break;
		case 2:
		    //执行c
			break;	
	}
}
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
    //stemp_code_creat();

    // common_test();
    // speed_init_test();
    // speed_run_test();
     //add_speed_time_test();
	  pulse_set_test();
	return 0;
}


