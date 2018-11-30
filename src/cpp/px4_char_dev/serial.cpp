#include "serial.hpp"

namespace device {

 // int serial::init()
 // {   
 // 	std::cout<< "serial::init" <<std::endl;

 // 	CDev::init();
 	
 // 	return 0;
 // }

 int	serial::open(file_t *filp)
 {   
 	std::cout<< "serial::open" <<std::endl;
 	return 0;
 }

 int	serial::close(file_t *filp)
 {  
 	std::cout<< "serial::close" <<std::endl;
	return 0;
 }
 
 ssize_t	serial::read(file_t *filp, char *buffer, size_t buflen)
 {  
 	std::cout<< "serial::read" <<std::endl;
 	return 0;
 }
 
 ssize_t	serial::write(file_t *filp, const char *buffer, size_t buflen)
 {  
 	std::cout<< "serial::write" <<std::endl;
 	return 0;
 }
 
 int	serial::ioctl(file_t *filp, int cmd, unsigned long arg)
 {  
 	std::cout<< "serial::ioctl" <<std::endl;
 	return 0;
 }
 
}

