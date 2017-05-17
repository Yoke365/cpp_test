#include	<stdio.h>
#include	<pthread.h>
#include	"unistd.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int count = 0;

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

int main(int argc, char*argv)
{

	pthread_t thread1,thread2;

	pthread_create(&thread1, NULL, &produce, NULL );

	pthread_create(&thread2, NULL, &consume, NULL );

	pthread_join(thread1,NULL);

	pthread_join(thread2,NULL);

	return 0;

}
