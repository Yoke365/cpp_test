/**
 * @file cdev.cpp
 *
 * Character device base class.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include "cdev.hpp"

namespace device
{

//#define ENOSYS  0
#define OK  0

static int	cdev_open(file_t *filp);
static int	cdev_close(file_t *filp);
static ssize_t	cdev_read(file_t *filp, char *buffer, size_t buflen);
static ssize_t	cdev_write(file_t *filp, const char *buffer, size_t buflen);
static int	cdev_ioctl(file_t *filp, int cmd, unsigned long arg);


const struct file_operations CDev::fops = {
	.open	= cdev_open,
	.close	= cdev_close,
	.read	=cdev_read,
	.write	=cdev_write,
	.ioctl	= cdev_ioctl,
	};

CDev::CDev(const char *name,
	   const char *devname) :
	_devname(devname),
	_registered(false),
	_open_count(0)
{
}

CDev::~CDev()
{

}



int
CDev::init()
{
	int ret;
	// now register the driver
	if (_devname != NULL) {
		ret = register_driver(_devname, &fops, 0666, (void *)this);
		std::cout<< "CDev::init register_driver" <<std::endl;
		if (ret != OK) {
			goto out;
		}

		_registered = true;
	}

out:
	return ret;
}

/*
 * Default implementations of the character device interface
 */
int
CDev::open(file_t *filp)
{
	int ret = OK;
    std::cout<< "CDev::open" <<std::endl;

	/* increment the open count */
	_open_count++;

	if (_open_count == 1) {
	}


	return ret;
}

int
CDev::close(file_t *filp)
{
	int ret = OK;


	if (_open_count > 0) {
		_open_count--;

		/* callback cannot decline the close */
		if (_open_count == 0) {
		}

	} else {
		ret = -1;
	}

	return ret;
}


ssize_t
CDev::read(file_t *filp, char *buffer, size_t buflen)
{
	return -ENOSYS;
}

ssize_t
CDev::write(file_t *filp, const char *buffer, size_t buflen)
{
	return -ENOSYS;
}


int
CDev::ioctl(file_t *filp, int cmd, unsigned long arg)
{
	return 0;
}


static int
cdev_open(file_t *filp)
{
	CDev *cdev = (CDev *)(filp->f_inode->i_private);

	return cdev->open(filp);
}

static int
cdev_close(file_t *filp)
{
	CDev *cdev = (CDev *)(filp->f_inode->i_private);

	return cdev->close(filp);
}

static ssize_t
cdev_read(file_t *filp, char *buffer, size_t buflen)
{
	CDev *cdev = (CDev *)(filp->f_inode->i_private);

	return cdev->read(filp, buffer, buflen);
}

static ssize_t
cdev_write(file_t *filp, const char *buffer, size_t buflen)
{
	CDev *cdev = (CDev *)(filp->f_inode->i_private);

	return cdev->write(filp, buffer, buflen);
}

static int
cdev_ioctl(file_t *filp, int cmd, unsigned long arg)
{
	CDev *cdev = (CDev *)(filp->f_inode->i_private);

	return cdev->ioctl(filp, cmd, arg);
}

}
