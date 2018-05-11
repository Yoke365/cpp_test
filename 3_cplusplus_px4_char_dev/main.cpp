#include "serial.hpp"
#include "fs.h"
#include <iostream>

device::serial *p;

//注册串口驱动, 使用c++实现
void cplusplus_serial_register(device::serial &tty)
{
 	fs_init();
    tty.init();
}

int main(int argc, char **argv)
{    
	std::cout<< "使用c++实现linux的驱动程序"<<std::endl;
    
    /* 注册驱动　*/
    p = new device::serial("/dev/tty1", "bluetooth");
    cplusplus_serial_register(*p);


    std::cout<< "准备打开设备驱动"<<std::endl;
    int ret = open("/dev/tty1", O_RDONLY);
    if (ret != 0) {
    	return -1;
    }

    std::cout<< "tty1 open ok"<<std::endl;

	return 0;
}


