#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//c interface
extern int upload_main(int argc, char **argv);
extern int queue_unittest_main(int argc, char **argv);
extern int calibrate_main(int argc, char **argv);
extern int orbsim_main(int argc, char** argv);
extern int add_variable_main(int argc, char** argv);
extern int arispeed_main(int argc, char** argv);
extern int file_size_main(int argc, char **argv);
extern int string_test_main(int argc, char **argv);
extern int fprintf_main( int argc, char **argv);
extern int nuttx_i2c_main(int argc, char** argv);
extern int cct_main(int argc, char **argv);
extern int rtcm_main(int argc, char** argv);
extern int pthread_test_main(int argc, char**argv);
extern int sbus_main(int argc, char** argv);
extern int mavlink_main(int argc, char**argv);

//cpp interface 
extern int cast_main(int argc, char **argv);
extern int const_type_main(int argc, char **argv);
extern int construct_main(int argc, char **argv);
extern int helloworld_main(int argc, char **argv);
extern int parent_to_child_main(int argc, char **argv);
extern int px4_char_dev_main(int argc, char **argv);
extern int refence_main(int argc, char **argv);
extern int static_member_main(int argc, char **argv);
extern int template_main(int argc, char **argv);
extern int template_class_main(int argc, char **argv);
extern int this_private_main(int argc, char **argv);
extern int vector_main(int argc, char **argv);

int main(int argc, char **argv)
{	
	upload_main(argc, argv);
	// queue_unittest_main(argc, argv);
	// calibrate_main(argc, argv);
	// orbsim_main(argc, argv);
	// add_variable_main(argc, argv);
	// arispeed_main(argc, argv);
	// file_size_main(argc, argv);
	// string_test_main(argc, argv);
	// fprintf_main( argc, argv);
	// nuttx_i2c_main(argc, argv);
	// cct_main(argc, argv);
	// rtcm_main(argc, argv);
	// pthread_test_main(argc, argv);
	// sbus_main(argc, argv);
	 // mavlink_main(argc, argv);

	// cast_main(argc,argv);
	// const_type_main(argc,argv);
	// construct_main(argc,argv);
	// helloworld_main(argc,argv);
	// parent_to_child_main(argc,argv);
	// px4_char_dev_main(argc,argv);
	// refence_main(argc,argv);
	// static_member_main(argc,argv);
	// template_main(argc,argv);
	// template_class_main(argc,argv);
	// this_private_main(argc,argv);
	// vector_main(argc,argv);
	
	return 0;
}
