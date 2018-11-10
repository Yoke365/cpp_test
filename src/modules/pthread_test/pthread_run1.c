#include	<pthread.h>
#include "pthread_run1.h"

extern pthread_mutex_t mutex;
extern int count;

void* consume( void *arg)
{
	while(1)
	{

		pthread_mutex_lock(&mutex );
		sleep(2);
		count++;
		printf("************************consumed%d\n",count);
		pthread_mutex_unlock(&mutex );
		sleep(1);

	}
}