#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

extern int upload_main(int argc, char **argv);
extern int queue_unittest_main(int argc, char **argv);
extern int calibrate_main(int argc, char **argv);

int main(int argc, char **argv)
{	
	// upload_main(argc, argv);
	// queue_unittest_main(argc, argv);
	calibrate_main(argc, argv);
	return 0;
}
