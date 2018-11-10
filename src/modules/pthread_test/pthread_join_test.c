#include	<stdio.h>
#include	<pthread.h>
#include	<unistd.h>

#include "pthread_join_test.h"
#include <pthread.h>
#include <stdio.h>

void* pthread_join_entry(void *arg)
{   
	for (int i = 0; i < 5; i++) {
		printf("run count:%d\r\n", i);
	}
}

int pthread_join_test(void)
{
	pthread_t pthread_join_test;

	pthread_create(&pthread_join_test, NULL, &pthread_join_entry, NULL );

	printf("pthread_join_test wait exit \r\n");
	pthread_join(pthread_join_test,NULL);
	printf("pthread_join_test exit \r\n");

	return 0;
}
