
#include "can.h" 

#define NULL 0
	
struct can_dev_s *dev_group[2];

void can_dev_register(int id, struct can_dev_s *dev)
{
	dev_group[id] = dev;
}    

struct can_dev_s * can_dev_get(int fd)
{
	struct can_dev_s *dev = NULL;
	dev = dev_group[fd];

	return dev;
}


static uint8_t can_dlc2bytes(uint8_t dlc)
{
  if (dlc > 8)
    {
#ifdef CONFIG_CAN_FD
      switch (dlc)
        {
          case 9:
            return 12;
          case 10:
            return 16;
          case 11:
            return 20;
          case 12:
            return 24;
          case 13:
            return 32;
          case 14:
            return 48;
          default:
          case 15:
            return 64;
        }
#else
      return 8;
#endif
    }

  return dlc;
}

int can_receive(struct can_dev_s *dev, struct can_hdr_s *hdr, uint8_t *data)
{
    struct can_rxfifo_s *fifo = &dev->cd_recv;
    uint8_t             *dest;
    int                      nexttail;
    int                      i;
  
    nexttail = fifo->rx_tail + 1;
    if (nexttail >= CONFIG_CAN_FIFOSIZE)
    {
        nexttail = 0;
    }
    if (nexttail != fifo->rx_head)
    {
      int nbytes;
       memcpy(&fifo->rx_buffer[fifo->rx_tail].cm_hdr, hdr, sizeof(struct can_hdr_s));

      nbytes = can_dlc2bytes(hdr->ch_dlc);
      for (i = 0, dest = fifo->rx_buffer[fifo->rx_tail].cm_data; i < nbytes; i++)
        {
          *dest++ = *data++;
        }

      /* Increment the tail of the circular buffer */

      fifo->rx_tail = nexttail;

      /* The increment the counting semaphore. The maximum value should be
       * CONFIG_CAN_FIFOSIZE -- one possible count for each allocated
       * message buffer.
       */
    }

    return 0;
}

ssize_t can_read(int fd,  char *buffer, size_t buflen)                     
{
    struct can_dev_s *dev = can_dev_get(fd);
    size_t                nread;
    int                   ret   = 0;
    
    if (buflen >= CAN_MSGLEN(0))
    {
        // no data 
        while (dev->cd_recv.rx_head == dev->cd_recv.rx_tail)
        { 
            return -1;
        }
        nread = 0;
        do
        {
            /* Will the next message in the FIFO fit into the user buffer? */

            struct can_msg_s *msg = &dev->cd_recv.rx_buffer[dev->cd_recv.rx_head];
            int nbytes = can_dlc2bytes(msg->cm_hdr.ch_dlc);
            int msglen = CAN_MSGLEN(nbytes);

            if (nread + msglen > buflen)
            {
                break;
            }

            /* Copy the message to the user buffer */

            memcpy(&buffer[nread], msg, msglen);
            nread += msglen;

            /* Increment the head of the circular message buffer */

            if (++dev->cd_recv.rx_head >= CONFIG_CAN_FIFOSIZE)
            {
                dev->cd_recv.rx_head = 0;
            }
        }
        while (dev->cd_recv.rx_head != dev->cd_recv.rx_tail);

        ret = nread;
    }

	return ret;
}











