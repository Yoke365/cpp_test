
#include <stdio.h>
#include <stdint.h>
#include "wheel_mesg.h"
#include "manual_ctrl.h"
/**
    wheel_send_mesg : 发送消息
    wheel_recv_mesg : 接收消息
*/
wheel_mesg_s wheel_send_mesg; 
wheel_mesg_s wheel_recv_mesg;

typedef struct {
	uint8_t pwm0;
	uint8_t pwm1;
}pwm_value_list_t; 





int main(int argc, char argv[])
{    
	// for (uint8_t i = 0 ; i < 100; i++) {
	// 	 cct_test(ledLinear[i]);
	// }
	//cct_test(2.5);
	//test();
	//pwm_cct(4);
	//pwm_dimmer();
	//pwm_test();
	// for (uint16_t i = 0; i < 50; i++) {
	// 	dmx_cct_test(100, i);
	// }

	dimmer_update();
	
 	//test1();
	return 0;
}


