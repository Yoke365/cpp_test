#include	<pthread.h>
#include "pthread_run2.h"

extern pthread_mutex_t mutex;
extern int count;

void* produce( void * arg )
{
	while(1 )
	{
		pthread_mutex_lock(&mutex );

		printf("productbegin lock\n");

		printf("Produced %d\n", count );

		printf("productover lock\n");

		pthread_mutex_unlock(&mutex );

		printf("I'mout of pthread_mutex\n");

		sleep(1);

	}

}