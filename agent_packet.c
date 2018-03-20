#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "work_queued.h"

uint32_t LocalTime = 0;

uint32_t timestamp_get()
{
	return LocalTime;
}

void timestamp_tick()
{
	 LocalTime++;
}


void work_callback(uint8_t time)
{   
	time = time;
	printf("123\r\n");
}

int work_queue( struct work_s *work, worker_t worker, uint32_t delay)          
{
  work->worker = worker;           /* Work callback */
  work->delay  = delay;            /* Delay until work performed */
  work->qtime  = timestamp_get();

  return 0;
}

void ms4525_main()
{
	printf("ms4525_main");
	printf("\r\n");
}

void ms4525_update_check()
{
	printf("ms4525_update_check");
	printf("\r\n");
}

void led_callback()
{
	printf("led_callback");
	printf("\r\n");
}

int main()
{    
	 struct work_s  work_ms[5];
     memset (&work_ms, 0x00, sizeof(work_ms));

     work_queue(&work_ms[0], ms4525_main,10);
     work_queue(&work_ms[1], ms4525_update_check, 20);
     work_queue(&work_ms[2], led_callback, 20);
	 printf("abc\r\n");
	 struct work_s  *work_m;
   
     while(1) {
		timestamp_tick();
        work_m = work_ms;
		for (uint8_t i = 0; i < 3; i++)
		{	 			
			if((timestamp_get() - work_m->qtime) >= work_m->delay) {
		      	work_m->worker();
				work_m->qtime = timestamp_get();
			}
			work_m++;
		}
		//printf("LocalTime:%d\r\n", LocalTime);
		usleep(100*1000);
     }

     return 0;
}


