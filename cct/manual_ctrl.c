/*******************************************************************************
*
* �ļ���  : control.c
* ����    : �ֶ�����pwm
* ����    : 2017-09-02
* ����    : �Ƹ�
*
*******************************************************************************/

#include "manual_ctrl.h"
#include "cct.h"
#include <stdio.h>

led_pwm_t led_pwm = {
	.pwm_freq = 10,
	.dmx_addr = 1,
};

ch_attr_desc_t ch_attr_priv[3] = {
	{LED_CCT_BASE_VALUE, 0},
	{LED_CCT_BASE_VALUE, 0},
	{LED_CCT_BASE_VALUE, 0}
};

void cct_test(uint8_t dimmer)
{ 	
	ch_attr_priv[0].dimmer = dimmer;

	printf("cct | led_pwm[0] | led_pwm[1] \r\n");
	printf("------------------------------\r\n");
	for (uint8_t cct = LED_CCT_BASE_VALUE; cct <= LED_CCT_BASE_MAX; cct++) {

		ch_attr_priv[0].cct = cct;		
		ch_cct_dimmer_to_pwm(&ch_attr_priv[0], &led_pwm, 0);

		printf(": %02d00K, %03d, %03d\r\n", 
			cct, led_pwm.pwm_value[0], led_pwm.pwm_value[1]);
	}
}
