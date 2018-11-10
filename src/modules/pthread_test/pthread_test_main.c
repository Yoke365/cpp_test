#include	<stdio.h>

void usage_help(void)
{
	printf("./main jointest\r\n");
	printf("./main mutextest\r\n");
}

int pthread_test_main(int argc, char**argv)
{    
	if (argc >= 2) {
		if (!strcmp(argv[1], "jointest")) {		
			pthread_join_test();
			return 0;
		}

		if (!strcmp(argv[1], "mutextest")) {
			pthread_mutex_test();
			return 0;
		}

		if (!strcmp(argv[1], "help")) {
			usage_help();
			return 0;
		}
	} else {
		usage_help();
	}

	return 0;
}
