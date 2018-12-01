
#ifndef  _CAN_H
#define  _CAN_H

#include <stdint.h>
#include <string.h>
#define CONFIG_CAN_FIFOSIZE     8
#define CAN_MAXDATALEN          8
#define CONFIG_CAN_ERRORS   
#define CONFIG_CAN_EXTID 

#define ssize_t int
//#define size_t int

#ifdef CONFIG_CAN_EXTID
struct can_hdr_s
{
  uint32_t     ch_id;         /* 11- or 29-bit ID (20- or 3-bits unused) */
  uint8_t      ch_dlc    : 4; /* 4-bit DLC */
  uint8_t      ch_rtr    : 1; /* RTR indication */
#ifdef CONFIG_CAN_ERRORS
  uint8_t      ch_error  : 1; /* 1=ch_id is an error report */
#endif
  uint8_t      ch_extid  : 1; /* Extended ID indication */
  uint8_t      ch_unused : 1; /* Unused */
} ;
#else
struct can_hdr_s
{
  uint16_t     ch_id;         /* 11-bit standard ID (5-bits unused) */
  uint8_t      ch_dlc    : 4; /* 4-bit DLC.  May be encoded in CAN_FD mode. */
  uint8_t      ch_rtr    : 1; /* RTR indication */
#ifdef CONFIG_CAN_ERRORS
  uint8_t      ch_error  : 1; /* 1=ch_id is an error report */
#endif
  uint8_t      ch_unused : 2; /* Unused */
} ;
#endif

struct can_msg_s
{
  struct can_hdr_s cm_hdr;                  /* The CAN header */
  uint8_t          cm_data[CAN_MAXDATALEN]; /* CAN message data (0-8 byte) */
};

struct can_rxfifo_s
{
//   sem_t         rx_sem;                  /* Counting semaphore */
  uint8_t       rx_head;                 /* Index to the head [IN] in the circular buffer */
  uint8_t       rx_tail;                 /* Index to the tail [OUT] in the circular buffer */
                                         /* Circular buffer of CAN messages */
  struct can_msg_s rx_buffer[CONFIG_CAN_FIFOSIZE];
};

struct can_dev_s
{
//   struct can_txfifo_s  cd_xmit;          /* Describes transmit FIFO */
  struct can_rxfifo_s  cd_recv;          /* Describes receive FIFO */

};
#define CAN_MSGLEN(nbytes)        (sizeof(struct can_msg_s) - CAN_MAXDATALEN + (nbytes))


int can_receive( struct can_dev_s *dev,  struct can_hdr_s *hdr,
                 uint8_t *data);
ssize_t can_read(int fd,  char *buffer, size_t buflen);                 
#endif
