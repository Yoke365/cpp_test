
#include <stdio.h>
#include <stdint.h>
<<<<<<< HEAD
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
    cct_test(100);
    cct_test(1);
=======
#include "manual_ctrl.h"


int main(int argc, char argv[])
{    
    //cct_test(100);
    cct_test(5);
>>>>>>> 5cb9626e33b36eae2401fed794d44b7978f2d18d

	return 0;
}


