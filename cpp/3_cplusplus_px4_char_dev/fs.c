/**
 * @file cdev.cpp
 *
 * Character device base class.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "fs.h"

typedef unsigned int mode_t;

struct inode _node[2];
struct file file_serial;

void fs_init (void)
{
	file_serial.f_inode = _node;
}

int register_driver( const char *path,  const struct file_operations *fops,
                    mode_t mode,  void *priv)
{    
	file_serial.f_pos = fops;
    file_serial.f_inode->i_private = priv;
    printf("register_driver\r\n");
	return 0;
}

int unregister_driver( const char *path)
{
  int ret;

  return ret;
}


int open(const char *path, int oflags, ...)
{  
   file_serial.f_pos->open(&file_serial);

   int ret =0;
   return ret;
}
