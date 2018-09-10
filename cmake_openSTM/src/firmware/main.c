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
extern int cct_main(int argc, char **argv);
extern int rtcm_main(int argc, char** argv);
extern int pthread_test_main(int argc, char**argv);
extern int hello_world_print_main(int argc,char **argv);
extern int px4_char_dev_main(int argc,char **argv);

int main(int argc, char **argv)
{	
	// pthread_test_main(argc, argv);
	//rtcm_main(argc, argv);
	//cct_main(argc, argv);

	//fprintf_main(argc, argv);
	px4_char_dev_main(argc, argv);
	
	return 0;
}
