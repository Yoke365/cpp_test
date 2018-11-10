#include	<pthread.h>
#include "pthread_run2.h"

extern pthread_mutex_t mutex;
extern int count;

void* produce( void * arg )
{
	while(1)
	{
		pthread_mutex_lock(&mutex );

		printf("Produced %d\n", count );
		pthread_mutex_unlock(&mutex );
		sleep(1);
	}

}