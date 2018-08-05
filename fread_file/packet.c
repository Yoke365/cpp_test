#include  <stdbool.h>
#include  <string.h>

#include "packet.h"
#include "uart.h"
#include "crc16.h"

struct uart_dev_s *packet_uart = &uart3_dev;

#define PACKET_DEBUG_EN 1

#if PACKET_DEBUG_EN
#define PACKET_DEBUG(format,...)   printf(format, ##__VA_ARGS__)
#else 
#define PACKET_DEBUG(format,...)   
#endif 

#define RX_STATE_INST_NUM  5 
uint8_t packet_buf[IAP_CONFIG_PACKET_BUFSIZE * RX_STATE_INST_NUM];
rx_state_s rx_state_inst[RX_STATE_INST_NUM];
rx_state_s *rx_state = rx_state_inst;

void print_info_single(struct uart_buffer_s *recv, uint8_t *buf, uint8_t len)
{ 
    printf("{");
	for(int i = 0; i < len; i++) {
		printf("%02x ", buf[i]);
		 usart_irq_callback_single(recv, &buf[i]);
		//usart_tx_ringbuffer_push(recv , &buf[i]);
	}
	printf("}\r\n");
}

void print_info1(uint8_t *buf, uint8_t len)
{ 
    printf("{");
	for(int i = 0; i < len; i++) {
		printf("%02x ", buf[i]);
		 //usart_irq_callback(packet_uart, &buf[i]);
	}
	printf("}\r\n");
}

void packet_mem_init(void)
{
	memset(packet_buf, 0x00, sizeof(packet_buf));

	rx_state_s *rx_state_p = rx_state_inst;

	for(uint8_t i = 0; i < RX_STATE_INST_NUM; i++) {
		rx_state_p->buf = &packet_buf[IAP_CONFIG_PACKET_BUFSIZE*i];
		printf("rx_state: %d, 0x%x\r\n", i, rx_state_p);
		rx_state_p++;	
	}
}

rx_state_s* findRxState(uint32_t transfer_descriptor)
{
    rx_state_s *rx_state_p = rx_state_inst;

    for(uint8_t i = 0; i < RX_STATE_INST_NUM; i++) {	
		if (i == transfer_descriptor) {
			printf("rx_state_p: %d, 0x%x\r\n", i, rx_state_p);
			return rx_state_p;
		}
		rx_state_p++;
	}
   
    return NULL;
}


void pakect_send(int fd, uint8_t cmd, uint8_t *playload, uint16_t length)
{   	
	uint8_t buf[FW_PAKET_BUF_SIZE];

    buf[FW_START1_POS] = FW_HEAD_BYTE_1;
    buf[FW_START2_POS] = FW_HEAD_BYTE_2;
	buf[FW_DST_POS]    = 1;
    buf[FW_SRC_POS]    = 2;

	buf[FW_LEN_L_POS]  = (length+1) & 0xff;  //多加1个cmd的字�?
    buf[FW_LEN_H_POS]  = ((length+1) >> 8) & 0xff;
    buf[FW_CMD_POS]    = cmd;

	if (length > 0) {
    	memcpy(&buf[FW_DATA_POS], playload, length);
	}
	uint16_t cksum_pos = FW_PAKET_HEAD_LEN+length;
	uint16_t cksum;
	cksum = calc_crc((const uint8_t *)buf, FW_PAKET_HEAD_LEN+length);
	buf[cksum_pos]   = cksum & 0x00ff;
	buf[cksum_pos+1] = (cksum >> 8) & 0x00ff;
	buf[cksum_pos+2] = FW_END_BYTE_1;
    buf[cksum_pos+3] = FW_END_BYTE_2;

	uint16_t send_len = FW_PAKET_HEAD_LEN + length + FW_PAKET_TAIL_LEN;
  
   	// struct uart_buffer_s *recv = find_uart(fd);	
    print_info1(buf, send_len);
	PACKET_DEBUG("send len: %d\r\n", send_len);
}

packet_desc_t packet_tmp;


bool packet_parse(int fd, uint8_t ch, packet_desc_t *packet)
{   
	rx_state_s *rx_state = findRxState(fd);
	if (rx_state == NULL) {
		return false;
	}

    rx_state->buf[rx_state->packet_index++] = ch; //先加1
 	switch (rx_state->parse_packet_step)
	{
		case FW_HEAD:							
			if (rx_state->packet_index >= 2)
			{
		        if ((rx_state->buf[FW_START1_POS] == FW_HEAD_BYTE_1) && (rx_state->buf[FW_START2_POS] == FW_HEAD_BYTE_2))
		     	{   
					rx_state->parse_packet_step = FW_LEN;							
		     	}
				else if (rx_state->buf[FW_START2_POS] == FW_HEAD_BYTE_1)
				{   
				    rx_state->buf[FW_START1_POS] = FW_HEAD_BYTE_1;
					rx_state->packet_index = 1;
				}
				else
				{
					rx_state->packet_index = 0;							
				}
			}
			break;	
			
		case FW_LEN:	
			if (rx_state->packet_index >= 6)
			{  
			   rx_state->FrameLen  = *((uint16_t *)&rx_state->buf[FW_LEN_L_POS]) + 10; 
			   if (rx_state->FrameLen <= IAP_CONFIG_PACKET_BUFSIZE)
			   {
		      		rx_state->parse_packet_step = FW_DATA_CRC_TAIL; 
			   }
			   else
			   {
					rx_state->parse_packet_step = FW_HEAD;
					rx_state->packet_index            = 0; 
					
			   }
			}
			break;
		
		case FW_DATA_CRC_TAIL:
			if(rx_state->packet_index == rx_state->FrameLen)
			{    
	            uint16_t RxCrcCheckSum_A =  calc_crc((const uint8_t *)&rx_state->buf[0], rx_state->FrameLen-4);
			    uint16_t RxCrcCheckSum_B =  *((uint16_t *)&rx_state->buf[rx_state->FrameLen-4]);
				rx_state->parse_packet_step = FW_HEAD;
				rx_state->packet_index      = 0; 
				
				if (RxCrcCheckSum_A == RxCrcCheckSum_B)
				{    
					memcpy((uint8_t*)packet, rx_state->buf, rx_state->FrameLen);
					print_info1((uint8_t*)packet, rx_state->FrameLen);
					memset(rx_state->buf, 0x00, sizeof(rx_state->buf));
			
				    return true;
				}
				else
				{
				    rx_state->crc_error++;
				}
				
			}							
			break;
						
		default:
			break;
	}
	

	return false;
}




bool packet_parse_data_callback(uint8_t ch)
{    
    
    int fd  = 0;
    packet_desc_t *packet = &packet_tmp;

	rx_state_s *rx_state = findRxState(fd);
	if (rx_state == NULL) {
		return false;
	}

    struct uart_buffer_s *recv = find_uart(fd);
 
    rx_state->buf[rx_state->packet_index++] = ch; //先加1
 	switch (rx_state->parse_packet_step)
	{
		case FW_HEAD:							
			if (rx_state->packet_index >= 2)
			{
		        if ((rx_state->buf[FW_START1_POS] == FW_HEAD_BYTE_1) && (rx_state->buf[FW_START2_POS] == FW_HEAD_BYTE_2))
		     	{   
					rx_state->parse_packet_step = FW_LEN;							
		     	}
				else if (rx_state->buf[FW_START2_POS] == FW_HEAD_BYTE_1)
				{   
				    rx_state->buf[FW_START1_POS] = FW_HEAD_BYTE_1;
					rx_state->packet_index = 1;
				}
				else
				{
					rx_state->packet_index = 0;							
				}
			}
			break;	
			
		case FW_LEN:	
			if (rx_state->packet_index >= 6)
			{  
			   rx_state->FrameLen  = *((uint16_t *)&rx_state->buf[FW_LEN_L_POS]) + 10; 
			   if (rx_state->FrameLen <= IAP_CONFIG_PACKET_BUFSIZE)
			   {
		      		rx_state->parse_packet_step = FW_DATA_CRC_TAIL; 
			   }
			   else
			   {
					rx_state->parse_packet_step = FW_HEAD;
					rx_state->packet_index            = 0; 
					
			   }
			}
			break;
		
		case FW_DATA_CRC_TAIL:
			if(rx_state->packet_index == rx_state->FrameLen)
			{    
	            uint16_t RxCrcCheckSum_A =  calc_crc((const uint8_t *)&rx_state->buf[0], rx_state->FrameLen-4);
			    uint16_t RxCrcCheckSum_B =  *((uint16_t *)&rx_state->buf[rx_state->FrameLen-4]);
				rx_state->parse_packet_step = FW_HEAD;
				rx_state->packet_index      = 0; 
				
				if (RxCrcCheckSum_A == RxCrcCheckSum_B)
				{    
					memcpy((uint8_t*)packet, rx_state->buf, rx_state->FrameLen);
					print_info1((uint8_t*)packet, rx_state->FrameLen);
					memset(rx_state->buf, 0x00, sizeof(rx_state->buf));
					recv->tail = (recv->tail + 1) % recv->size;

				    return true;
				}
				else
				{
				    rx_state->crc_error++;
				}
				
			}							
			break;
						
		default:
			break;
	}


	return false;
}

void packet_prase( struct uart_buffer_s *recv)
{
    uint16_t data_cnt = 0;
    uint16_t i        = 0;
    
    data_cnt = ringbuffer_count(recv);
    if (data_cnt > 0) {  
        for (i = 0; i < data_cnt; i++) {
			/* get data */			
			uint8_t new_data = 0;
			uart_rx_ringbuffer_pop (recv, &new_data);
    
			/* handler */
			//sim868_close_check(new_data);         
			//acount_packet_prase(new_data);
			packet_parse_data_callback(new_data);
        }
    }
}

bool packet_parse_data_callback_open(int fd, packet_desc_t *packet)
{   
	rx_state_s *rx_state = findRxState(fd);
	if (rx_state == NULL) {
		return false;
	}

    struct uart_buffer_s *recv = find_uart(fd);

	uint16_t data_cnt = ringbuffer_count(recv);
	printf("data_cnt:%d\r\n", data_cnt);
	if (data_cnt > 0) 
	{  
		for (uint16_t i = 0; i < data_cnt; i++)
		{   
		    rx_state->buf[rx_state->packet_index++] = recv->buffer[recv->tail]; //先加1
		 	switch (rx_state->parse_packet_step)
			{
				case FW_HEAD:							
					if (rx_state->packet_index >= 2)
					{
				        if ((rx_state->buf[FW_START1_POS] == FW_HEAD_BYTE_1) && (rx_state->buf[FW_START2_POS] == FW_HEAD_BYTE_2))
				     	{   
							rx_state->parse_packet_step = FW_LEN;							
				     	}
						else if (rx_state->buf[FW_START2_POS] == FW_HEAD_BYTE_1)
						{   
						    rx_state->buf[FW_START1_POS] = FW_HEAD_BYTE_1;
							rx_state->packet_index = 1;
						}
						else
						{
							rx_state->packet_index = 0;							
						}
					}
					break;	
					
				case FW_LEN:	
					if (rx_state->packet_index >= 6)
					{  
					   rx_state->FrameLen  = *((uint16_t *)&rx_state->buf[FW_LEN_L_POS]) + 10; 
					   if (rx_state->FrameLen <= IAP_CONFIG_PACKET_BUFSIZE)
					   {
				      		rx_state->parse_packet_step = FW_DATA_CRC_TAIL; 
					   }
					   else
					   {
							rx_state->parse_packet_step = FW_HEAD;
							rx_state->packet_index            = 0; 
							
					   }
					}
					break;
				
				case FW_DATA_CRC_TAIL:
					if(rx_state->packet_index == rx_state->FrameLen)
					{    
			            uint16_t RxCrcCheckSum_A =  calc_crc((const uint8_t *)&rx_state->buf[0], rx_state->FrameLen-4);
					    uint16_t RxCrcCheckSum_B =  *((uint16_t *)&rx_state->buf[rx_state->FrameLen-4]);
						rx_state->parse_packet_step = FW_HEAD;
						rx_state->packet_index      = 0; 
						
						if (RxCrcCheckSum_A == RxCrcCheckSum_B)
						{    
							memcpy((uint8_t*)packet, rx_state->buf, rx_state->FrameLen);
							print_info1((uint8_t*)packet, rx_state->FrameLen);
							memset(rx_state->buf, 0x00, sizeof(rx_state->buf));
 							recv->tail = (recv->tail + 1) % recv->size;

						    return true;
						}
						else
						{
						    rx_state->crc_error++;
						}
						
					}							
					break;
								
				default:
					break;
			}
			recv->tail = (recv->tail + 1) % recv->size;

		}
	}

	return false;
}