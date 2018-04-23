/*******************************************************************************
*
* �ļ�����: UART.H
* ����    : sd���洢������������
* ����    : 2017-07-11
* ����    : �Ƹ�
*
*******************************************************************************/

#ifndef __MANUAL_CTRL_H
#define __MANUAL_CTRL_H

/* �ⲿͷ�ļ�����  ---------------------------------------------------------*/
//#include "Common.h"
//#include "param.h"

#include <stdint.h> 
#include <stdbool.h>

#define LED_PWM_CHANNEL_NUM  6
struct led_pwm_s {
	uint8_t  pwm_value[LED_PWM_CHANNEL_NUM];
	uint8_t  pwm_freq ;
	uint8_t  sync_dimmer;
	uint16_t dmx_addr ;
};

typedef struct led_pwm_s led_pwm_t;

void function_manual_mode_update(void);
void function_sync_mode_update(void);
void cct_test(uint8_t dimmer);
#endif /* __MANUAL_CTRL_H  */

