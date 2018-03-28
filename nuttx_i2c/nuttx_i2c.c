#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "nuttx_i2c.h"
#include "errno.h"

#define  OK 0


// _brightness(1.0f),
// 	_max_brightness(1.0f),

#define ADDR_ID_A			0x0a
#define ADDR_ID_B			0x0b
#define ADDR_ID_C			0x0c

#define ID_A_WHO_AM_I			'H'
#define ID_B_WHO_AM_I			'4'
#define ID_C_WHO_AM_I			'3'

#define PX4_I2C_OBDEV_LED	0x55
#define PX4_I2C_OBDEV_HMC5883	0x1e

#define  MODE1      0x00  //Mode register 1
#define  MODE2      0x01  //Mode register 2
#define  PWM0       0x02  //brightness control LED0
#define  PWM1       0x03  //brightness control LED1
#define  PWM2       0x04  //brightness control LED2
#define  PWM3       0x05  //brightness control LED3
#define  GRPPWM     0x06  //group duty cycle control
#define  GRPFREQ    0x07  //group frequency
#define  LEDOUT     0x08  //LED output state
#define  SUBADR1    0x09  //I2C-bus subaddress 1
#define  SUBADR2    0x0A  //I2C-bus subaddress 2
#define  SUBADR3    0x0B  //I2C-bus subaddress 3
#define  ALLCALLADR 0x0C  //LED All Call I2C-bus address

int _dev = 0;
int _address = PX4_I2C_OBDEV_LED;
int _retries = 5;

uint8_t			_r;
uint8_t			_g;
uint8_t			_b;
float			_brightness = 1;
float			_max_brightness = 1;

//learn pc8754
int up_i2creset(int dev)
{
	return 0;
}
//read messsg+  write message 

// i2c interface 
int I2C_TRANSFER(int dev, struct i2c_msg_s *msg, uint8_t count)
{   
	for (uint8_t i =0; i < count; i++) {
		printf("addr:0x%x\r\n", msg[i].addr);
		printf("flags:0x%x\r\n", msg[i].flags);
		if (msg[i].flags) {
			printf("read cmd\r\n");
		}
		printf("length:0x%x\r\n", msg[i].length);
		for (uint8_t j =0; j < msg[i].length; j++) {
			printf("data:0x%x,", msg[i].buffer[j]);
		}
		printf("\r\n----------------\r\n");
	}
	return 0;
}

int transfer(const uint8_t *send, unsigned send_len, uint8_t *recv, unsigned recv_len)
{
	struct i2c_msg_s msgv[2];
	unsigned msgs;
	int ret;
	unsigned retry_count = 0;
    

	do {
		//	DEVICE_DEBUG("transfer out %p/%u  in %p/%u", send, send_len, recv, recv_len);

		msgs = 0;

		if (send_len > 0) {
			msgv[msgs].addr = _address;
			msgv[msgs].flags = 0;
			msgv[msgs].buffer = (uint8_t *)(send);
			msgv[msgs].length = send_len;
			msgs++;
		}

		if (recv_len > 0) {
			msgv[msgs].addr = _address;
			msgv[msgs].flags = I2C_M_READ;
			msgv[msgs].buffer = recv;
			msgv[msgs].length = recv_len;
			msgs++;
		}

		if (msgs == 0) {
			return -EINVAL;
		}

		ret = I2C_TRANSFER(_dev, &msgv[0], msgs);

		/* success */
		if (ret == OK) {
			break;
		}

		/* if we have already retried once, or we are going to give up, then reset the bus */
		if ((retry_count >= 1) || (retry_count >= _retries)) {
			up_i2creset(_dev);
		}

	} while (retry_count++ < _retries);

	return ret;

}

int
write(unsigned address, void *data, unsigned count)
{
	uint8_t buf[32];

	if (sizeof(buf) < (count + 1)) {
		return -EIO;
	}

	buf[0] = address;
	memcpy(&buf[1], data, count);

	return transfer(&buf[0], count + 1, NULL, 0);
}

int
read(unsigned address, void *data, unsigned count)
{
	uint8_t cmd = address;
	return transfer(&cmd, 1, (uint8_t *)data, count);
}


int send_led_enable(bool enable)
{
	uint8_t settings_byte = 0;

	if (enable) {
		settings_byte = 0x2A;
	}
	const uint8_t msg[2] = { LEDOUT, settings_byte};

	return transfer(msg, sizeof(msg), NULL, 0);
}

int
send_led_rgb()
{
	const uint8_t msg_b[] = {
				PWM0, (uint8_t)(_b * _brightness * _max_brightness)
			};
	transfer(msg_b, sizeof(msg_b), NULL, 0);

	const uint8_t msg_g[] = {

			PWM1, (uint8_t)(_g * _brightness * _max_brightness)
		};
	transfer(msg_g, sizeof(msg_g), NULL, 0);

	const uint8_t msg_r[] = {
				PWM2, (uint8_t)(_r * _brightness * _max_brightness)
			};
	return transfer(msg_r, sizeof(msg_r), NULL, 0);
}

void led_test()
{   
	//start
	send_led_enable(true);
    
    //pwm 
    _r = 0;
    _g = 0;
    _b = 0;

    send_led_rgb();
}

int probe()
{
	// uint8_t data[3] = {0, 0, 0};

	// _retries = 10;

	// if (read(ADDR_ID_A, &data[0], 1) ||
	//     read(ADDR_ID_B, &data[1], 1) ||
	//     read(ADDR_ID_C, &data[2], 1)) {
	// 	return -EIO;
	// }

	led_test();

	return 0;
}