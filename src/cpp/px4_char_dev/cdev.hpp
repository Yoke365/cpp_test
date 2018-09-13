#ifndef _DEVICE_DEVICE_H
#define _DEVICE_DEVICE_H
/*
 * Includes here should only cover the needs of the framework definitions.
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "fs.h"

namespace device
{
/**
 * Abstract class for any character device
 */
class  CDev
{
public:
	CDev(const char *name, const char *devname);
	virtual ~CDev();

	virtual int	init();

	virtual int	open(file_t *filp);
	virtual int	close(file_t *filp);
	virtual ssize_t	read(file_t *filp, char *buffer, size_t buflen);
	virtual ssize_t	write(file_t *filp, const char *buffer, size_t buflen);
	virtual int	ioctl(file_t *filp, int cmd, unsigned long arg);
protected:
	/**
	 * Pointer to the default cdev file operations table; useful for
	 * registering clone devices etc.
	 */
	static const struct file_operations fops; 
	
private:
	const char	*_devname;		/**< device node name */
	bool		_registered;		/**< true if device name was registered */
	uint16_t	_open_count;		/**< number of successful opens */


};

}


#endif  /* _DEVICE_DEVICE_H */