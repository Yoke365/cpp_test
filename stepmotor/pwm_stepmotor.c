#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "stepmotor.h"
#include "protocol.h"

#define PWM_RUN()  printf("type: 0x%x, value, %d, value_new:0x%x\r\n", local_type, i, value); \
			pwm_cmd_run(local_type, value);

void common_test(void)
{
  for (uint16_t i = 0; i < speed_init_base_value; i+=2) {
		uint8_t local_type = 0;
		uint16_t value =0;
		if (pwm_cmd_prase(i, &local_type, &value) == 0) {
			
		}
	}
}

void speed_init_test(void)
{
	for (uint16_t i = speed_init_base_value; i < speed_run_base_value; i+=2) {
		uint8_t local_type = 0;
		uint16_t value =0;
		if (pwm_cmd_prase(i, &local_type, &value) == 0) {
			PWM_RUN();
		}
	}
}
void speed_run_test(void)
{   
	for (uint16_t i = speed_run_base_value; i < add_speed_time_base_value; i+=2) {
		uint8_t local_type = 0;
		uint16_t value =0;
		if (pwm_cmd_prase(i, &local_type, &value) == 0) {
			PWM_RUN();
		}
	}
}

void add_speed_time_test(void)
{  
	for (uint16_t i = add_speed_time_base_value; i < pulse_set_base_value; i+=2) {
		uint8_t local_type = 0;
		uint16_t value =0;
		if (pwm_cmd_prase(i, &local_type, &value) == 0) {
			PWM_RUN();
		}
	}
}

void pulse_set_test(void)
{
		for (uint16_t i = pulse_set_base_value; i < 17000; i+=2) {
		uint8_t local_type = 0;
		uint16_t value =0;
		if (pwm_cmd_prase(i, &local_type, &value) == 0) {
			PWM_RUN();
		}
	}
}

void cmd_parase_test()
{
	 //common_test();
	 //speed_init_test();
	 //speed_run_test();
	 //add_speed_time_test();
	 //pulse_set_test();
	 stepmotor_test();
}

