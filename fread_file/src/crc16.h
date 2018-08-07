#ifndef _CRC16_H
#define _CRC16_H

//#include "stm32f10x.h"
#include <stdint.h>

uint16_t calc_crc(const uint8_t *buf, const uint32_t len);

#endif /* _CRC16_H*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

