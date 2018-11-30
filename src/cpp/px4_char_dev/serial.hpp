#ifndef _SERIAL_H
#define _SERIAL_H

#include <iostream>
#include "cdev.hpp"

namespace device {

class serial : public device::CDev 
{
public:
	serial(const char *name,
	   const char *devname): 
	CDev(name, devname){
		// std::cout<< "instance construct" <<std::endl;

	}

	~serial(){
		// std::cout<< "instance deconstruct" <<std::endl;
	};
	
    // virtual int	init();
	virtual int	open(file_t *filp);
	virtual int	close(file_t *filp);
	virtual ssize_t	read(file_t *filp, char *buffer, size_t buflen);
	virtual ssize_t	write(file_t *filp, const char *buffer, size_t buflen);
	virtual int	ioctl(file_t *filp, int cmd, unsigned long arg);
}; 

}
#endif 
