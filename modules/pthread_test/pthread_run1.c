#include	<pthread.h>
#include "pthread_run1.h"

extern pthread_mutex_t mutex;
extern int count;

void* consume( void *arg)
{
	while(1 )
	{

		pthread_mutex_lock(&mutex );

		printf("************************consumebegin lock\n");

		printf("************************consumed%d\n",count );

		sleep(2);

		count++;

		printf("************************consumed%d\n",count);

		printf("************************consumeover lock\n");

		pthread_mutex_unlock(&mutex );

		printf("************************I'mout of pthread_mutex\n");

		sleep(1);

	}
}