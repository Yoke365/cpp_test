#ifndef __PACKET_H
#define	__PACKET_H

#include <stdint.h>
#include <stdbool.h>
#include "uart.h"

#define FW_HEAD_BYTE_1                         0X55
#define FW_HEAD_BYTE_2                         0XAA
#define FW_END_BYTE_1                          0XA5
#define FW_END_BYTE_2		                   0X5A

#define FW_PAKET_BUF_SIZE   					200   
#define IAP_CONFIG_PACKET_BUFSIZE 		       2048
#define IAP_FW_DATA_LEN 		               128
enum {
	FW_START1_POS 	=   	0,
	FW_START2_POS	=   	1,
	FW_DST_POS		=       2,
	FW_SRC_POS   	=       3,
	FW_LEN_L_POS 	=       4,
	FW_LEN_H_POS	=       5,
	FW_CMD_POS   	=       6,
	FW_DATA_POS		=       7,
};

enum {
	FW_HEAD     =           0,
	FW_LEN      =           1,
	FW_END      =           2, 
};

enum {
	FW_DATA_CRC_TAIL    = 2,
	FW_PAKET_TAIL_LEN   = 4,     
	FW_PAKET_HEAD_LEN   = 7 , 
};

enum {  
	FW_UPDATE_REQ           =  	          1,
	FW_UPDATE_ACK	        = 	          2,
	FW_UPDATE_DATA 	  	    = 	          3,
	FW_UPDATE_ERROR  		=	          4,
	FW_UPDATE_OK     	    =             5,
	FW_UPDATE_VERREQ  	    =             6,
	FW_UPDATE_VERREPLY      =             7,
	FW_UPDATE_ACCOUNT_INFO_SET    =       8,
	FW_UPDATE_ACCOUNT_INFO_GET    =		  9,
	FW_UPDATE_ACCOUNT_INFO_REPLY  = 	  10,

	SPEED_INIT_CODE       = 0X13,
	SPEED_RUN_CODE	      = 0X14,	 
	ADD_SPEED_TIME_CODE   = 0X15,
	LIMIT_SWITCH_CODE     = 0X16,
	PULSE_SET_CODE        = 0X17,
	CONNITUE_RUN_CODE     = 0X18,
	STOP_CODE             = 0X19,
	STATE_POLL_CODE       = 0X1A,  
	STATE_POLL_REPLY_CODE = 0X81,
	SENSOR_TRIGGER_CODE    = 0X21, 

	CMD_LED_COLOR         =   0x31,
};

#pragma pack(push, 1)
typedef struct  {
    uint8_t head0;
    uint8_t head1;
	uint8_t dest;
	uint8_t src;
	uint16_t length;
	uint8_t data[IAP_CONFIG_PACKET_BUFSIZE];
}packet_desc_t;
#pragma pack(pop)

struct CanardRxState
{
    uint8_t *buf;
    uint8_t  parse_packet_step ;
    uint16_t packet_index;
    uint16_t FrameLen;
    uint16_t crc_error;

}CanardRxState;
typedef struct CanardRxState rx_state_s;
typedef rx_state_s rx_state_t;

#pragma pack(push, 1)
typedef struct {
	uint16_t total_block;
	uint16_t cur_block;
	uint16_t block_len;
	uint8_t data[IAP_FW_DATA_LEN];
} fw_packet_t;
#pragma pack(pop)

void pakect_send(int fd, uint8_t cmd, uint8_t *playload, uint16_t length);
void print_info_single(struct uart_buffer_s *recv, uint8_t *buf, uint8_t len);
bool packet_parse_data_callback_open(int fd, packet_desc_t *packet);
bool packet_parse_data_callback_buf(uint8_t ch, packet_desc_t *packet);

#endif /* __PACKET_H */
