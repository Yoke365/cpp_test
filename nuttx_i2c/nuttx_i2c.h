#ifndef _STEP_MOTOR_H
#define _STEP_MOTOR_H

#include <stdint.h>

#define I2C_M_READ           0x0001          /* read data, from slave to master */
#define I2C_M_TEN            0x0002          /* ten bit address */
#define I2C_M_NORESTART      0x0080          /* message should not begin with (re-)start of transfer */

#define ADDR_ID_A			0x0a
#define ADDR_ID_B			0x0b
#define ADDR_ID_C			0x0c

#define ID_A_WHO_AM_I			'H'
#define ID_B_WHO_AM_I			'4'
#define ID_C_WHO_AM_I			'3'
//I2C address >> 1: 	0x5D  => 0xBA/0xBB
struct i2c_msg_s
{
  uint16_t  addr;                  /* Slave address */
  uint16_t  flags;                 /* See I2C_M_* definitions */
  uint8_t  *buffer;
  int       length;
};

int probe();
#endif /* _STEP_MOTOR_H */
