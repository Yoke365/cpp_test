#include <iostream>

//必须生命是C编译，否则会链接不到
extern "C"{ extern int helloworld_main(int argc, char **argv);}

int helloworld_main(int argc, char **argv)
{
	std::cout << "Hello World!" << std::endl;

	return 0;
}