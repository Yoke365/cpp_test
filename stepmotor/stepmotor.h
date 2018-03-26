#ifndef _STEP_MOTOR_H
#define _STEP_MOTOR_H

#include <stdint.h>

enum {
	ok = 0x10,
	error = 0x20
};

enum {
  address_poll_cmd     = 0xFE,
  address_set_cmd      = 0x22, 
  speed_init_cmd       = 0x23,
  speed_run_cmd	       = 0x24,	 
  add_speed_time_cmd   = 0x25,

  limit_switch_cmd     = 0x26,
  pulse_set_cmd        = 0x27,
  connitue_run_cmd     = 0x28,
  stop_cmd             = 0x29,
  state_poll_cmd       = 0x30,  
};


enum {
  address_poll_len     = 0,
  address_set_len      = 1, 
  speed_init_len       = 4,
  speed_run_len	       = 4,	 
  add_speed_time_len   = 2,

  limit_switch_len     = 1,
  pulse_set_len        = 4,
  connitue_run_len     = 1,
  stop_len             = 1,
  state_poll_len       = 0,  
};


typedef struct {
	uint8_t address;
	uint8_t cmd;
	uint8_t length;
	uint8_t crc_high;
	uint8_t crc_low;
}address_poll_t;

typedef struct {
	uint8_t address;
	uint8_t cmd;
	uint8_t length;
	uint8_t new_address;
	uint8_t crc_high;
	uint8_t crc_low;
}address_set_t;

typedef struct {
	uint8_t address;
	uint8_t cmd;
	uint8_t length;
	uint8_t speed_init_value[4]; /*高字节在前，低字节在后*/
	uint8_t crc_high;
	uint8_t crc_low;
}speed_init_t;

typedef struct {
	uint8_t address;
	uint8_t cmd;
	uint8_t length;
	uint8_t speed_run[4]; /*高字节在前，低字节在后*/
	uint8_t crc_high;
	uint8_t crc_low;
}speed_run_t;

typedef struct {
	uint8_t address;
	uint8_t cmd;
	uint8_t length;
	uint8_t speed_time[2]; /*高字节在前，低字节在后*/
	uint8_t crc_high;
	uint8_t crc_low;
}add_speed_time_t;

typedef enum {
	switch_on  = 0x10,
	switch_off = 0x20,
}switch_t;

typedef struct {
	uint8_t address;
	uint8_t cmd;
	uint8_t length;
	uint8_t state; 
	uint8_t crc_high;
	uint8_t crc_low;
}limit_switch_t;

typedef struct {
	uint8_t address;
	uint8_t cmd;
	uint8_t length;
	uint8_t pulse_val[4]; /*高字节在前，低字节在后*/
	uint8_t crc_high;
	uint8_t crc_low;
}pulse_set_t;

typedef enum {
	orientation_clockwise      =  0x10,
	orientation_anti_clockwise =  0x20,
}orientation_t;

typedef struct {
	uint8_t address;
	uint8_t cmd;
	uint8_t length;
	uint8_t clockwise_state; 
	uint8_t crc_high;
	uint8_t crc_low;
}connitue_run_t;

typedef enum {
	mode_slow_down      =  0x10,
	mode_stutter_stop   =  0x20,
}stop_mode_t;

typedef struct {
	uint8_t address;
	uint8_t cmd;
	uint8_t length;
	uint8_t mode; 
	uint8_t crc_high;
	uint8_t crc_low;
}stop_t;


typedef struct {
	uint8_t address;
	uint8_t cmd;
	uint8_t length;
	uint8_t crc_high;
	uint8_t crc_low;
}state_poll_t;

/* 10 command */
typedef union {
  address_poll_t address_poll;
  address_set_t address_set;
   speed_init_t speed_init;
   speed_run_t speed_run;
   add_speed_time_t add_speed_time;

   limit_switch_t limit_switch;
   pulse_set_t pulse_set;
   connitue_run_t connitue_run;
   stop_t stop;
   state_poll_t  state_poll;
} stepmotor_packet_union_t;


// 01 23 04 00 00 27 10 00 5F 01 10返回成功

/* 
操作失败：地址(1字节)　＋　状态(0x20) : 01 20
操作ok ：地址(1字节)　＋　状态(0x10)
*/
void address_poll_handler(uint8_t address);
void address_set_handler(uint8_t address);
void speed_init_handler(uint8_t address);
void speed_run_handler(uint8_t address);
void add_speed_time_handler(uint8_t address);
void limit_switch_handler(uint8_t address, switch_t state);
void pulse_set_handler(uint8_t address);
void connitue_run_handler(uint8_t address, orientation_t orientation);
void stop_handler(uint8_t address, stop_mode_t mode);
void state_poll_handler(uint8_t address);
void stepmotor_test(void);
#endif /* _STEP_MOTOR_H */