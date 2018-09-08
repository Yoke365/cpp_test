#include <iostream>

extern "C" extern int hello_world_print_main(int argc, char **argv);

int hello_world_print_main(int argc, char **argv)
{
	std::cout << "Hello World!" << std::endl;

	return 0;
}