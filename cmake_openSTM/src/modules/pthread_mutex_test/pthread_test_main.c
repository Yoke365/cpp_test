#include	<stdio.h>
#include	<pthread.h>
#include	"unistd.h"

#include	"pthread_run1.h"
#include	"pthread_run2.h"


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int count = 0;

int pthread_test_main(int argc, char*argv)
{
	pthread_t thread1,thread2;

	pthread_create(&thread1, NULL, &produce, NULL );
	pthread_create(&thread2, NULL, &consume, NULL );

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	return 0;
}
