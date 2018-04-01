#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#define AGENT_HEAD0   0xAA
#define AGENT_HEAD1   0x44
#define AGENT_HEAD2   0x16
enum {
	CMD_ACTIVATE_REQUEST     = 0X01,
	CMD_ACTIVATE_CONFIG_INFO = 0x81,
	CMD_ACTIVATE_OK          = 0x02,
};
typedef enum {
    ST_HEAD0 = 0,
	ST_HEAD1,
	ST_HEAD2,
    ST_LEN_LOW,
    ST_LEN_HIGH,
    ST_DATA,
    ST_CRC_LOW,
    ST_CRC_HIGH
} agent_parse_state;

#pragma pack(1)

typedef struct __agent_message {
	uint8_t head0;
	uint8_t head1;
	uint8_t head2;
	uint16_t len;	
	uint8_t data[100]; 
	uint16_t crc;
} agent_message_t;

struct agent_inst_desc {
	uint8_t head[3];
	uint16_t length;	
	uint8_t data[50];
};
typedef struct agent_inst_desc agent_desc_inst_t;

typedef struct  {
   char reg_char[14];
   char cpn_str[14];
   char user_id_str[14];
}acount_info_desc_t;


typedef struct gps_info_desc {
    uint8_t   head[2];
	acount_info_desc_t playload; 
	uint16_t  crc;	
} acount_info_param_desc_t;

#pragma pack() 

#define ACTIVATE_CONFIG_INFO_LEN 40

//crc16table
/** CRC table for the CRC-16. The poly is 0x8005 (x^16 + x^15 + x^2 + 1) */
uint16_t const osmo_crc16_table[256] = {
	0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
	0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
	0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
	0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
	0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
	0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
	0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
	0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
	0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
	0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
	0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
	0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
	0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
	0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
	0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
	0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
	0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
	0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
	0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
	0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
	0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
	0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
	0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
	0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
	0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
	0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
	0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
	0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
	0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
	0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
	0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
	0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};


uint16_t osmo_crc16_byte(uint16_t crc, const uint8_t data)
{
	return (crc >> 8) ^ osmo_crc16_table[(crc ^ data) & 0xff];
}

/**
 * crc16 - compute the CRC-16 for the data buffer
 * @crc:	previous CRC value
 * @buffer:	data pointer
 * @len:	number of bytes in the buffer
 *
 * Returns the updated CRC value.
 */
uint16_t osmo_crc16(uint16_t crc, uint8_t const *buffer, size_t len)
{
	while (len--)
		crc = osmo_crc16_byte(crc, *buffer++);
	return crc;
}

void *encrypt(void *text, size_t text_n, uint8_t xor_key)
{
	unsigned char *p_convert = (unsigned char*)text;
	while (text_n-- > 0)
		{
			*p_convert = *p_convert ^ xor_key;
			p_convert++;
		}
	return text;
}
bool agent_prase_config(uint8_t ch, agent_message_t *user_packet)
{
    static agent_parse_state state = ST_HEAD0;
    static uint8_t data_index = 0;
	static uint16_t crc_data_cal =0;
	static uint16_t crc_data =0;

	// printf("ch:%02x\r\n", ch);
	switch (state) {
	    case ST_HEAD0: 
		   if (ch == AGENT_HEAD0) {
			   user_packet->head0 = AGENT_HEAD0;
			   state = ST_HEAD1; 
			   // printf("state = ST_HEAD1\r\n"); 
		   } else {
			   state = ST_HEAD0;
		   }
		   break;

	    case ST_HEAD1: 
		   if (ch == AGENT_HEAD1) {
			   user_packet->head1 = AGENT_HEAD1;
			   state = ST_HEAD2;
			   // printf("state = ST_HEAD1\r\n");   
		   } else {
			   state = ST_HEAD0;
		   } 
		   
		   break;

	    case ST_HEAD2: 
		   if (ch == AGENT_HEAD2) {
			   user_packet->head2 = AGENT_HEAD2;
			   state = ST_LEN_LOW;
			   // printf("state = ST_LEN_HIGH\r\n");  
		   } else {
			   state = ST_HEAD0;
		   } 
		   
		   break;

	   case ST_LEN_LOW:
	   	   user_packet->len &= 0xff00;
	   	   user_packet->len = (uint16_t)ch; 
	       state = ST_LEN_HIGH;
		   // printf("state = ST_LEN_LOW\r\n");
		   break;

		case ST_LEN_HIGH:
		   user_packet->len &= 0x00ff;
		   user_packet->len |= (uint16_t)(ch << 8);
		   data_index = 0;
		   state = ST_DATA;
		   // printf("state = ST_DATA\r\n");
		   break;
		   
	   case ST_DATA:  
		   user_packet->data[data_index++] = ch;
		   if (data_index >= user_packet->len) {
		   	   uint8_t *crc_head = (uint8_t *) &user_packet->len;
		   	   crc_data_cal = osmo_crc16(0, crc_head, user_packet->len+2); //
			   state = ST_CRC_LOW;
			   printf("state = ST_CRC_LOW\r\n");
  		   }
		   
		   break;

	    case ST_CRC_LOW:  
		   crc_data &= 0x0000;
	   	   crc_data = (uint16_t)ch; 			 
		   state = ST_CRC_HIGH;
		    printf("state = ST_CRC_HIGH\r\n");
		   break;

		case ST_CRC_HIGH:  
		   crc_data &= 0x00ff;
		   crc_data |= (uint16_t)(ch << 8);
		     
		   if (crc_data_cal == crc_data) {
			   state = ST_HEAD0;
			   printf("next state = ST_HEAD0\r\n");
			   return true;
		   }
		   
		   break;   
	 } 
	 return false;
}


void agent_packet_create_inst(agent_desc_inst_t *agent_priv, uint8_t *buf, uint8_t len)
{   
	/* 包头 */
	agent_priv->head[0] = 0xAA;
	agent_priv->head[1] = 0x44;
	agent_priv->head[2] = 0x16;
    
    printf("<");
	for(int i = 0; i < len; i++) {
		printf("%c ", buf[i]);
	}
	printf(">\r\n");

	agent_priv->length = len; 
	memcpy((uint8_t *)&agent_priv->data, (uint8_t *)buf, len);

	/* 计算crc */
	uint8_t *mesg = (uint8_t *)agent_priv;
	uint16_t crc = osmo_crc16(0, &mesg[3], agent_priv->length+2);
	agent_priv->data[agent_priv->length]   = crc & 0x00ff;
	agent_priv->data[agent_priv->length+1] = (crc >> 8) & 0x00ff;

    printf("{");
	for(int i = 0; i < (ACTIVATE_CONFIG_INFO_LEN + 7); i++) {
		printf("%02x ", mesg[i]);
	}
	printf("}\r\n");
}

int acount_info_param_write(acount_info_param_desc_t *param, acount_info_desc_t *buf, uint8_t len)
{ 	 	
	//包头
	param->head[0] = 0xA5;
	param->head[1] = 0x5A;
    
	//数据段
	memcpy((uint8_t*)&param->playload, (uint8_t*)buf, len);
   
	//crc值
	param->crc = osmo_crc16(0,  (uint8_t*)&param->playload, len);	
}

void test_param(void)
{
	const char reg_char[14] 	= "0BUAS00000197";
	const char cpn_str[14] 		= "0017G0tChsyoD";
	const char user_id_str[14]	= "1234567890123";
    acount_info_desc_t acount_info;

    memcpy(acount_info.reg_char, reg_char, 13);
	memcpy(acount_info.cpn_str, cpn_str, 13);
	memcpy(acount_info.user_id_str, user_id_str, 13);
    acount_info.reg_char[13]     = '\0';
    acount_info.cpn_str[13]      = '\0';
    acount_info.user_id_str[13]  = '\0';
    
    acount_info_param_desc_t acount_info_param;
    memset(&acount_info_param, 0x00, sizeof(acount_info_param));
	acount_info_param_write(&acount_info_param, &acount_info, sizeof(acount_info_desc_t));
	// printf("%d{",sizeof(acount_info_param_desc_t));
	// uint8_t *mesg1 = (uint8_t *)&acount_info_param;
	// for(int i = 0; i < sizeof(acount_info_param_desc_t); i++) {
	// 	printf("%02x ", mesg1[i]);
	// }
	// printf("}\r\n");
}

void creat_param(void)
{
	const char reg_char[14] 	= "0BUAS00000197";
	const char cpn_str[14] 		= "0017G0tChsyoD";
	const char user_id_str[14]	= "1234567890123";
     
    char  buf[13+13+13+1] = {CMD_ACTIVATE_CONFIG_INFO};

    memcpy(&buf[1], reg_char, 13);
	memcpy(&buf[14], cpn_str, 13);
	memcpy(&buf[27], user_id_str, 13);

    agent_desc_inst_t agent; 
	agent_packet_create_inst(&agent, buf, sizeof(buf));
    agent_message_t agent_message;

	uint8_t *message = (uint8_t *)&agent;
    for(int i = 0; i < sizeof(agent_desc_inst_t); i++) {
		agent_prase_config(message[i], &agent_message);
	}
     
    uint8_t *mesg = (uint8_t *)&agent_message;
	printf("{");
	for(int i = 0; i < (ACTIVATE_CONFIG_INFO_LEN + 7); i++) {
		printf("%02x ", mesg[i]);
	}
	printf("}\r\n");
}

#define CONNECT_IP_PORT_STR_WORK       "AT+CIPSTART=\"TCP\",\"211.137.43.166\",\"8180\"\r"  
#define CONNECT_IP_PORT_STR_ZHUHAIYANG "AT+CIPSTART=\"TCP\",\"223.100.24.135\",\"2000\"\r"   
#define CONNECT_IP_PORT_STR_CLOUD      "AT+CIPSTART=\"TCP\",\"223.100.24.135\",\"2480\"\r"
#define CONNECT_IP_PORT_STR_MAQINGLIN  "AT+CIPSTART=\"TCP\",\"223.100.24.135\",\"12000\"\r"
#define CONNECT_IP_PORT_STR_WENBORUI   "AT+CIPSTART=\"TCP\",\"223.100.25.9\",\"9001\"\r"
#define CONNECT_IP_PORT_STR_YANGANG    "AT+CIPSTART=\"TCP\",\"223.100.25.9\",\"9004\"\r"

char connet_ip_port_str_work[]        = CONNECT_IP_PORT_STR_WORK;
char connect_ip_port_str_zhuhaiyang[] = CONNECT_IP_PORT_STR_ZHUHAIYANG;
char connect_ip_port_str_cloud[]      = CONNECT_IP_PORT_STR_CLOUD;
char connect_ip_port_str_maqinglin[]  = CONNECT_IP_PORT_STR_MAQINGLIN;
char connect_ip_port_str_wenborui[]   = CONNECT_IP_PORT_STR_WENBORUI;
char connect_ip_port_str_yangang[]    = CONNECT_IP_PORT_STR_YANGANG;
#define CONNECT_IP_PORT_STR  CONNECT_IP_PORT_STR_WORK

struct AT_Command
{
    uint8_t Sent_AT[50] ;    
    uint8_t Read_AT[20] ;    
    uint8_t WaitTime    ;   
} ;

struct AT_Command  sim868_user_at[12] = {
	{"AT\r","OK",2},
	{"AT+CPIN?\r","+CPIN: READY",2},  
	{"AT+CSQ\r", "+CSQ:",2},           
	{"AT+CREG?\r","OK",2},	
 	{"AT+CGATT?\r","OK",2},	
 	
 	{"AT+BTPOWER=0\r","OK",2},
	{"AT+CIPSHUT\r","OK",2},
	{"AT+CIPMODE=1\r","OK",2},
    {"AT+CSTT\r","OK",2},	
	{"AT+CIICR\r","OK",2},
	
 	{"AT+CIFSR\r",".",2},
	{CONNECT_IP_PORT_STR,"OK\r\n\r\nCONNECT",2},     
} ;
#define AT_IP_INDEX                 11

void sim868_ip_config_callback(void)
{
	uint8_t str_len = strlen(connect_ip_port_str_yangang);
	if (str_len < 50) 
		str_len = 49;
	
	char *p = connect_ip_port_str_yangang;
    printf(p);

	strncpy((uint8_t *)sim868_user_at[AT_IP_INDEX].Sent_AT, connect_ip_port_str_yangang , str_len);

    //printf(&sim868_user_at[AT_IP_INDEX].Sent_AT[0]);
}


int main()
{   
	// char  buf[13] = {CMD_ACTIVATE_REQUEST, 1,2,3,4,5,6,7,8,9,10,11,12 };
 //    agent_desc_inst_t agent; 
 //    agent_message_t agent_message;
 //    agent_packet_create_inst(&agent, buf, sizeof(buf));
    
 //    uint8_t *message = (uint8_t *)&agent;
 //    for(int i = 0; i < sizeof(agent_desc_inst_t); i++) {
	// 	agent_prase_config(message[i], &agent_message);
	// }
    
    // char *p1 = "12";
    // printf(p1);
    // printf("\r\n");
    // printf("p1 length: %d\r\n", strlen(p1));

    // char *p2 = "34";
    // printf(p2);
    // printf("\r\n");
    // printf("p2 length: %d\r\n", strlen(p2));
    
    //sim868_ip_config_callback();
	//test_param();
	creat_param();
    return 0;
}


