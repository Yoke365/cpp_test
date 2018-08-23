#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

extern int upload_main(int argc, char **argv);
extern int queue_unittest_main(int argc, char **argv);
extern int calibrate_main(int argc, char **argv);
extern int orbsim_main(int argc, char** argv);
extern int add_variable_main(int argc, char** argv);
extern int arispeed_main(int argc, char** argv);
extern int file_size_main(int argc, char **argv);
extern int string_main(int argc, char **argv);
extern int fprintf_main( int argc, char **argv);
extern int nuttx_i2c_main(int argc, char** argv);
extern int cct_main(int argc, char** argv);
extern int rtcm_main(int argc, char** argv);
extern int pthread_test_main(int argc, char*argv);

int main(int argc, char **argv)
{	
	// pthread_test_main(argc, argv);
	
	return 0;
}
