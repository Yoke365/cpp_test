#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "work_queue.h"
#include "time.h"

void ms4525_main()
{
	printf("task1");
	printf("\r\n");
}

void ms4525_update_check()
{
	printf("task2");
	printf("\r\n");
}

void led_callback()
{
	printf("task3");
	printf("\r\n");
}

typedef struct CanardBufferBlock
{
    struct CanardBufferBlock* next;
    uint8_t data[];
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    
} CanardBufferBlock;


int main(int argc, char argv[])
{    
	 struct work_s  work_ms[5];
     memset (&work_ms, 0x00, sizeof(work_ms));

     work_queue(&work_ms[0], ms4525_main,10);
     work_queue(&work_ms[1], ms4525_update_check, 20);
     work_queue(&work_ms[2], led_callback, 20);
     
	 printf("system start\r\n");

     printf("%d\r\n", sizeof(CanardBufferBlock));
   
     while(1) {
		timestamp_tick();
        for (uint8_t i = 0; i < 3; i++) {
        	work_queue_check(&work_ms[i]);
        }	
		usleep(100*1000);
     }

     return 0;
}


