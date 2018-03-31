#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "c_pointer_fun.h"

int main(int argc, char argv[])
{    
    printf("start\r\n");

    acount_info_t *p ;
    p = GetNum();

	printf("appkey:%s\r\n", p->appkey);
	printf("appsecret:%s\r\n", p->appsecret);
	printf("device_ID:%s\r\n", p->device_ID);
	printf("device_Type:%s\r\n", p->device_Type);

	return 0;
}


