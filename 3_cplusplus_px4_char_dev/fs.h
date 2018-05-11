
/**
 * @file cdev.cpp
 *
 * Character device base class.
 */
#ifndef _FS_H
#define _FS_H

#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
 extern "C" {
#endif

#define O_RDONLY    (1 << 0)        /* Open for read access (only) */
#define O_RDOK      O_RDONLY        /* Read access is permitted (non-standard) */
#define O_WRONLY    (1 << 1)        /* Open for write access (only) */
#define O_WROK      O_WRONLY        /* Write access is permitted (non-standard) */
#define O_RDWR      (O_RDOK|O_WROK) /* Open for both read & write access */
#define O_CREAT     (1 << 2)        /* Create file/sem/mq object */
#define O_EXCL      (1 << 3)        /* Name must not exist when opened  */
#define O_APPEND    (1 << 4)        /* Keep contents, append to end */
#define O_TRUNC     (1 << 5)        /* Delete contents */
#define O_NONBLOCK  (1 << 6)        /* Don't wait for data */
#define O_NDELAY    O_NONBLOCK      /* Synonym for O_NONBLOCK */
#define O_SYNC      (1 << 7)        /* Synchronize output on write */
#define O_DSYNC     O_SYNC          /* Equivalent to OSYNC in NuttX */
#define O_BINARY    (1 << 8)        /* Open the file in binary (untranslated) mode. */


typedef struct file file_t;
typedef unsigned int mode_t;
struct inode
{  
   void         *i_private;  /* Per inode driver private data */
};
struct file_operations;

struct file
{
  const struct file_operations  *f_pos;      /* File position */
  struct inode     *f_inode;
  void             *f_priv;     /* Per file driver private data */
};

struct file_operations
{

  int     (*open)( struct file *filep);
  int     (*close)( struct file *filep);
  ssize_t (*read)( struct file *filep,  char *buffer, size_t buflen);
  ssize_t (*write)( struct file *filep,  const char *buffer, size_t buflen);
  int     (*ioctl)( struct file *filep, int cmd, unsigned long arg);
};


int register_driver( const char *path,  const struct file_operations *fops,
                    mode_t mode,  void *priv);
int unregister_driver( const char *path);
int open(const char *path, int oflags, ...);
void fs_init (void);

#ifdef __cplusplus
}
#endif

#endif 