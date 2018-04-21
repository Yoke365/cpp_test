
#include <stdio.h>
#include <stdint.h>

#include "wheel_mesg.h"

/**
    wheel_send_mesg : 发送消息
    wheel_recv_mesg : 接收消息
*/
wheel_mesg_s wheel_send_mesg; 
wheel_mesg_s wheel_recv_mesg;

int main(int argc, char argv[])
{    
    /* 发送orb消息 */
    wheel_send_mesg.val = 1;
    printf("send mesg: %d\r\n",  wheel_send_mesg.val);
    wheel_orb_publish(&wheel_send_mesg);
    
    /* 接收orb消息 */
    bool update = false;
    wheel_orb_check(&update);
    if (update) {
        wheel_orb_copy(&wheel_recv_mesg);
        printf("recv mesg: %d\r\n", wheel_send_mesg.val);      
    }

	return 0;
}


