#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "nuttx_i2c.h"

#define RTCM_CONFIG_NUM   6

char posave_str[] = "posave on 0.03\r\n";
char log_rtcm1074_str[] = "log com3 rtcm1074 ontime 1\r\n";
char log_rtcm1084_str[] = "log com3 rtcm1084 ontime 1\r\n";
char log_rtcm1124_str[] = "log com3 rtcm1124 ontime 1\r\n";
char log_rtcm1006_str[] = "log com3 rtcm1006 ontime 10\r\n";
char log_rtcm1033_str[] = "log com3 rtcm1033 ontime 10\r\n";

char *list[] = {posave_str, log_rtcm1074_str, log_rtcm1084_str, log_rtcm1124_str, log_rtcm1006_str, log_rtcm1033_str };

static int8_t rtcm_send_str(char *send_str,char *excepted_recv_str, uint8_t wait_time)         
{
	uint8_t ret = 0;						

	if(send_str == NULL){
		return -1;
	}

    printf("%s", send_str);

    return 0;
}


void rtcm_send_config(void)
{
	for (uint8_t i =0; i < RTCM_CONFIG_NUM; i++) {
    	rtcm_send_str(list[i], "ok", 10);
    }
}

int rtcm_main(int argc, char** argv)
{   
	rtcm_send_config();
	return 0;
}



