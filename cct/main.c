
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


int main(int argc, char argv[])
{    
	// for (uint8_t i = 0 ; i < 100; i++) {
	// 	 cct_test(ledLinear[i]);
	// }
	cct_test(3);
	//pwm_test();
 	//test1();
	return 0;
}


