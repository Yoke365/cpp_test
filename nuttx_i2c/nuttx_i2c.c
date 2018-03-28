#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "nuttx_i2c.h"

// int　transfer(const uint8_t *send, unsigned send_len, uint8_t *recv, unsigned recv_len)
// {
// 	struct i2c_msg_s msgv[2];
// 	unsigned msgs;
// 	int ret;
// 	unsigned retry_count = 0;

// 	do {
// 		//	DEVICE_DEBUG("transfer out %p/%u  in %p/%u", send, send_len, recv, recv_len);

// 		msgs = 0;

// 		if (send_len > 0) {
// 			msgv[msgs].addr = _address;
// 			msgv[msgs].flags = 0;
// 			msgv[msgs].buffer = const_cast<uint8_t *>(send);
// 			msgv[msgs].length = send_len;
// 			msgs++;
// 		}

// 		if (recv_len > 0) {
// 			msgv[msgs].addr = _address;
// 			msgv[msgs].flags = I2C_M_READ;
// 			msgv[msgs].buffer = recv;
// 			msgv[msgs].length = recv_len;
// 			msgs++;
// 		}

// 		if (msgs == 0) {
// 			return -EINVAL;
// 		}

// 		ret = I2C_TRANSFER(_dev, &msgv[0], msgs);

// 		/* success */
// 		if (ret == OK) {
// 			break;
// 		}

// 		/* if we have already retried once, or we are going to give up, then reset the bus */
// 		if ((retry_count >= 1) || (retry_count >= _retries)) {
// 			up_i2creset(_dev);
// 		}

// 	} while (retry_count++ < _retries);

// 	return ret;

// }