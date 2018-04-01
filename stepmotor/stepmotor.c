#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "stepmotor.h"

#define TYPE_32BIT_HH(X) (uint8_t) ((X >> 24) & 0xff)
#define TYPE_32BIT_MH(X) (uint8_t) ((X >> 16) & 0xff)
#define TYPE_32BIT_H(X) (uint8_t) ((X >> 8) & 0xff)
#define TYPE_32BIT_L(X) (uint8_t) ((X) & 0xff)

#define STEPMOTOR_HEAD_LEN   3  /* address+len+cmd*/

/* 启动过程:　
　　　1. 设置启动速度　
　　 2.　　设置
 */

/* 地址+命令+长度+数据+校验和 */

/* crc高字节在前, 低字节在后 */
uint16_t  cal_sum(uint8_t *playload, uint8_t length)
{
	if (playload == 0 || length == 0) {
		return -1;
	} 

	uint16_t sum = 0;
	for (uint8_t i = 0; i < length; i++) {
		sum += playload[i];
	}

	return sum;
}

void print_info(uint8_t *buf, uint8_t len)
{ 
#ifdef STEPMOTOR_DEBUG
    printf("{");
	for(int i = 0; i < len; i++) {
		printf("%02x ", buf[i]);
	}
	printf("}\r\n");
#endif
}


void address_poll_handler(uint8_t address)
{
	stepmotor_packet_union_t p;

	p.address_poll.address = address;
    p.address_poll.cmd = address_poll_cmd;
    p.address_poll.length  = address_poll_len;
    
    uint16_t cksum;
	cksum = cal_sum((uint8_t *)&p, STEPMOTOR_HEAD_LEN+p.address_poll.length);
	p.address_poll.crc_high   = (cksum >> 8) & 0x00ff;
	p.address_poll.crc_low = cksum & 0x00ff;
    
    print_info((uint8_t *)&p, p.address_poll.length + 5);
}

void address_set_handler(uint8_t address, uint8_t new_address)
{
	stepmotor_packet_union_t p;

	p.address_set.address = address;
    p.address_set.cmd = address_set_cmd;
    p.address_set.length  = address_set_len;
    p.address_set.new_address = new_address;

    uint16_t cksum;
	cksum = cal_sum((uint8_t *)&p, STEPMOTOR_HEAD_LEN+p.address_set.length);
	p.address_set.crc_high   = (cksum >> 8) & 0x00ff;
	p.address_set.crc_low = cksum & 0x00ff;
    
    print_info((uint8_t *)&p, p.address_set.length + 5);
}


void speed_init_handler(uint8_t address, uint32_t val)
{
	stepmotor_packet_union_t p;

	p.speed_init.address =  address;
    p.speed_init.cmd     =  speed_init_cmd;
    p.speed_init.length  =  speed_init_len;
    
	p.speed_init.speed_init_value[0] = TYPE_32BIT_HH(val);
	p.speed_init.speed_init_value[1] = TYPE_32BIT_MH(val);
	p.speed_init.speed_init_value[2] = TYPE_32BIT_H(val);
	p.speed_init.speed_init_value[3] = TYPE_32BIT_L(val);

    uint16_t cksum;
	cksum = cal_sum((uint8_t *)&p, STEPMOTOR_HEAD_LEN+p.speed_init.length);
	p.speed_init.crc_high   = (cksum >> 8) & 0x00ff;
	p.speed_init.crc_low = cksum & 0x00ff;

	print_info((uint8_t *)&p, p.speed_init.length + 5);
}


void speed_run_handler(uint8_t address,  uint32_t val)
{
	stepmotor_packet_union_t p;

	p.speed_run.address = address;
    p.speed_run.cmd = speed_run_cmd;
    p.speed_run.length  = speed_run_len;
    p.speed_run.speed_run[0] = TYPE_32BIT_HH(val);
	p.speed_run.speed_run[1] = TYPE_32BIT_MH(val);
	p.speed_run.speed_run[2] = TYPE_32BIT_H(val);
	p.speed_run.speed_run[3] = TYPE_32BIT_L(val);

    uint16_t cksum;
	cksum = cal_sum((uint8_t *)&p, STEPMOTOR_HEAD_LEN+p.speed_run.length);
	p.speed_run.crc_high   = (cksum >> 8) & 0x00ff;
	p.speed_run.crc_low = cksum & 0x00ff;
    
	print_info((uint8_t *)&p, p.speed_run.length + 5);
}


void add_speed_time_handler(uint8_t address, uint16_t time)
{
	stepmotor_packet_union_t p;

	p.add_speed_time.address = address;
    p.add_speed_time.cmd = add_speed_time_cmd;
    p.add_speed_time.length  = add_speed_time_len;
    p.add_speed_time.speed_time[0] = (uint8_t) ((time >> 8) & 0xff); 
    p.add_speed_time.speed_time[1] = (uint8_t) ((time     ) & 0xff); 

    uint16_t cksum;
	cksum = cal_sum((uint8_t *)&p, STEPMOTOR_HEAD_LEN+p.add_speed_time.length);
	p.add_speed_time.crc_high   = (cksum >> 8) & 0x00ff;
	p.add_speed_time.crc_low = cksum & 0x00ff;

	print_info((uint8_t *)&p, p.add_speed_time.length + 5);
}


void limit_switch_handler(uint8_t address, switch_t state)
{
	stepmotor_packet_union_t p;

	p.limit_switch.address = address;
    p.limit_switch.cmd = limit_switch_cmd;
    p.limit_switch.length  =limit_switch_len;
    p.limit_switch.state  = state;
  
    uint16_t cksum;
	cksum = cal_sum((uint8_t *)&p, STEPMOTOR_HEAD_LEN+p.limit_switch.length);
	p.limit_switch.crc_high   = (cksum >> 8) & 0x00ff;
	p.limit_switch.crc_low = cksum & 0x00ff;

	print_info((uint8_t *)&p, p.limit_switch.length + 5);
}


/**
　　１个字节的数据段
*/
void pulse_set_handler(uint8_t address, uint32_t pulse_val)
{
	stepmotor_packet_union_t p;

	p.pulse_set.address = address;
    p.pulse_set.cmd = pulse_set_cmd;
    p.pulse_set.length  = pulse_set_len;
    p.pulse_set.pulse_val[0] = TYPE_32BIT_HH(pulse_val);
	p.pulse_set.pulse_val[1] = TYPE_32BIT_MH(pulse_val);
	p.pulse_set.pulse_val[2] = TYPE_32BIT_H(pulse_val);
	p.pulse_set.pulse_val[3] = TYPE_32BIT_L(pulse_val);

    uint16_t cksum;
	cksum = cal_sum((uint8_t *)&p, STEPMOTOR_HEAD_LEN+p.pulse_set.length);
	p.pulse_set.crc_high   = (cksum >> 8) & 0x00ff;
	p.pulse_set.crc_low = cksum & 0x00ff;

	print_info((uint8_t *)&p, p.pulse_set.length + 5);
}

/**
　　１个字节的数据段
*/
void connitue_run_handler(uint8_t address, orientation_t orientation)
{
	stepmotor_packet_union_t p;

	p.connitue_run.address = address;
    p.connitue_run.cmd = connitue_run_cmd;
    p.connitue_run.length  = connitue_run_len;
    p.connitue_run.clockwise_state = orientation;

    uint16_t cksum;
	cksum = cal_sum((uint8_t *)&p, STEPMOTOR_HEAD_LEN+p.connitue_run.length);
	p.connitue_run.crc_high   = (cksum >> 8) & 0x00ff;
	p.connitue_run.crc_low = cksum & 0x00ff;
     
    print_info((uint8_t *)&p, p.connitue_run.length + 5);
}

/**
　　１个字节的数据段
*/
void stop_handler(uint8_t address, stop_mode_t mode)
{
	stepmotor_packet_union_t p;

	p.stop.address = address;
    p.stop.cmd = stop_cmd;
    p.stop.length  = stop_len;
    p.stop.mode =  mode;

    uint16_t cksum;
	cksum = cal_sum((uint8_t *)&p, STEPMOTOR_HEAD_LEN+p.stop.length);
	p.stop.crc_high   = (cksum >> 8) & 0x00ff;
	p.stop.crc_low = cksum & 0x00ff;

	print_info((uint8_t *)&p, p.stop.length + 5);
}

/**
 　　@没有数据段 
*/
void state_poll_handler(uint8_t address)
{
	stepmotor_packet_union_t p;

	p.state_poll.address = address;
    p.state_poll.cmd = state_poll_cmd;
    p.state_poll.length  = state_poll_len;
    
    uint16_t cksum;
	cksum = cal_sum((uint8_t *)&p, STEPMOTOR_HEAD_LEN+p.state_poll.length);
	p.state_poll.crc_high   = (cksum >> 8) & 0x00ff;
	p.state_poll.crc_low = cksum & 0x00ff;

	print_info((uint8_t *)&p, p.state_poll.length + 5);
}

// /*
//   正传和逆转都可以随时切换
// */
// void stepmotor_test(void)
// { 
// 	/* ＃8. 　可以随时手动干预电机的转动方向。*/
// 	connitue_run_handler(1, orientation_anti_clockwise); 
// 	// connitue_run_handler(1, orientation_clockwise);    
     
//  //    /* 停止模式　*/
//  //    stop_handler(1, mode_slow_down);
//  //    stop_handler(1, mode_stutter_stop);
// }