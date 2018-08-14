#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

extern int upload_main(int argc, char **argv);
extern int queue_unittest_main(int argc, char **argv);
extern int calibrate_main(int argc, char **argv);
extern int orbsim_main(int argc, char** argv);

int main(int argc, char **argv)
{	
	orbsim_main(argc, argv);
	
	return 0;
}
