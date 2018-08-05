#ifndef __UART1_H
#define __UART1_H

#include <stdint.h>

#define NULL 0

#define CONFIG_UART4_TXBUFSIZE    			100
#define CONFIG_UART4_RXBUFSIZE 	 			  100
#define USART3                         1

#define CONFIG_UART3_TXBUFSIZE    			100
#define CONFIG_UART3_RXBUFSIZE 	 			  100

struct uart_buffer_s
{
  volatile int16_t head;   /* Index to the head [IN] index in the buffer */
  volatile int16_t tail;   /* Index to the tail [OUT] index in the buffer */
  int16_t      size;   	   /* The allocated size of the buffer */
  char        *buffer;     /* Pointer to the allocated buffer memory */

  uint32_t     total_len; 
  uint32_t     over;
  uint32_t     user_buf_over;
};

struct uart_dev_s {
	struct uart_buffer_s *xmit;
	struct uart_buffer_s *recv;
  int uart;
};

extern struct uart_dev_s uart4_dev;
extern struct uart_dev_s uart3_dev;
int ringbuffer_count(struct uart_buffer_s *lb);
void usart_irq_callback(struct uart_dev_s *dev, uint8_t *u_data);
void usart_irq_callback_single(struct uart_buffer_s *recv , uint8_t *u_data);
struct uart_buffer_s* find_uart(uint32_t transfer_descriptor);
void uart_buffer_init(void);
int uart_rx_ringbuffer_pop (struct uart_buffer_s *recv, uint8_t *data);

#endif /* __UART1_H  */

