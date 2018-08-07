/*******************************************************************************
*
* �ļ�����: UART.c
* ����    : ������������
* ����    : 2017-07-11
* ����    : �Ƹ�
*
*******************************************************************************/

#include "uart.h"

char g_uart4_rxbuffer[CONFIG_UART4_RXBUFSIZE];
char g_uart4txbuffer[CONFIG_UART4_TXBUFSIZE];

struct uart_buffer_s  uart4_tx = {
	.size    = CONFIG_UART4_TXBUFSIZE,
	.head 	= 0,
	.tail   = 0,
	.buffer	 = g_uart4txbuffer,
	
	.total_len 	   = 0,
	.over  		   = 0,
	.user_buf_over = 0	
};	

struct uart_buffer_s uart4_recv = {
	.size	= CONFIG_UART4_RXBUFSIZE,
	.head 	= 0,
	.tail   = 0,
	.buffer = g_uart4_rxbuffer,	

	.total_len 		= 0,
	.over   		= 0,
	.user_buf_over  = 0	
}; 	

struct uart_dev_s uart4_dev = {
	.xmit	= &uart4_tx,
	.recv 	= &uart4_recv,
	.uart   = 1,
};

char g_uart3_rxbuffer[CONFIG_UART3_RXBUFSIZE];
char g_uart3txbuffer[CONFIG_UART3_TXBUFSIZE];

struct uart_buffer_s  uart3_tx = {
	.size    = CONFIG_UART3_TXBUFSIZE,
	.head 	= 0,
	.tail   = 0,
	.buffer	 = g_uart3txbuffer,
	
	.total_len 	   = 0,
	.over  		   = 0,
	.user_buf_over = 0	
};	

struct uart_buffer_s uart3_recv = {
	.size	= CONFIG_UART3_RXBUFSIZE,
	.head 	= 0,
	.tail   = 0,
	.buffer = g_uart3_rxbuffer,	

	.total_len 		= 0,
	.over   		= 0,
	.user_buf_over  = 0	
}; 	

struct uart_dev_s uart3_dev = {
	.xmit	= &uart3_tx,
	.recv 	= &uart3_recv,
	.uart   = 1,
};

uint8_t g_uart_rxbuffer[500];
struct uart_buffer_s uart_recv[5]; 

void uart_buffer_init(void)
{	
	struct uart_buffer_s  *rx_state_p = uart_recv;

	for(uint8_t i = 0; i < 5; i++) {

		memset(rx_state_p, 0x00, sizeof(struct uart_buffer_s));

		rx_state_p->size = 100;
		rx_state_p->buffer = &g_uart_rxbuffer[100*i];
		printf("uart_buffer_init: %d, 0x%x, buf: 0x%x\r\n", i, rx_state_p, rx_state_p->buffer);
		rx_state_p++;	
	}
}

struct uart_buffer_s* find_uart(uint32_t transfer_descriptor)
{
    struct uart_buffer_s *rx_state_p = uart_recv;

    for(uint8_t i = 0; i < 5; i++) {	
		if (i == transfer_descriptor) {
			printf("find_uart: %d, 0x%x\r\n", i, rx_state_p);
			return rx_state_p;
		}
		rx_state_p++;
	}
   
    return NULL;
}

/*******************************************************************************
* ������  : void iap_write_data(void)
* ����    : iapд������
* ����    : 
* ���    :
* ����    :  
* ˵��    : 
*******************************************************************************/
int ringbuffer_count(struct uart_buffer_s *lb)
{
	int n = lb->head - lb->tail;

	if (n < 0) {
		n += lb->size;
	}

	return n;
}

void usart_irq_callback(struct uart_dev_s *dev, uint8_t *u_data)
{
	dev->recv->buffer[dev->recv->head] = *u_data;
	dev->recv->head = (dev->recv->head + 1) % dev->recv->size;
}

/* 接收数据 */
void usart_irq_callback_single(struct uart_buffer_s *recv , uint8_t *u_data)
{	
	recv->buffer[recv->head] = *u_data;
	recv->head = (recv->head + 1) % recv->size;
}

int uart_rx_ringbuffer_pop (struct uart_buffer_s *recv, uint8_t *data)
{
	*data = recv->buffer[recv->tail];
    recv->tail = (recv->tail + 1) % recv->size;
	
	return 0;
}


#define UART_SIM

#ifdef UART_SIM
	#define USART_TX_IRQ_ENABLE()     irq_request = 1
	#define USART_TX_IRQ_DISENABLE()  irq_request = 0
	#define USART_TX_IRQ_GET()			irq_request
#else 
	#define USART_TX_IRQ_DISENABLE()  USART_ITConfig(USART2, USART_IT_TXE, DISABLE)
	#define USART_TX_IRQ_ENABLE()  USART_ITConfig(USART2, USART_IT_TXE, ENABLE)	
#endif 

uint8_t usart_tx_ringbuffer_pop_to_usart(struct uart_buffer_s *xmit);
int irq_request = 0;


void irq_sim(void)
{   
	if (irq_request) {

		if ( usart_tx_ringbuffer_pop_to_usart(&uart3_tx) == 0)
		{   
			printf("buffer null\r\n");	
			/* Disable the Transmit interrupt if buffer is empty */
			USART_TX_IRQ_DISENABLE();
		}
	}

}

void usart_tx_ringbuffer_push(struct uart_buffer_s *xmit , uint8_t *u_data)
{	
 	USART_TX_IRQ_DISENABLE();

	xmit->buffer[xmit->head] = *u_data;
	xmit->head = (xmit->head + 1) % xmit->size;

	USART_TX_IRQ_ENABLE();

	irq_sim();
}


uint8_t usart_tx_ringbuffer_pop_to_usart(struct uart_buffer_s *xmit)
{    
	if (xmit->head != xmit->tail)
	{
		printf("send: 0x%x\r\n", (uint8_t )xmit->buffer[xmit->tail]);
		xmit->tail = (xmit->tail + 1) % xmit->size;

		return 1;
	}

	return 0;
}



