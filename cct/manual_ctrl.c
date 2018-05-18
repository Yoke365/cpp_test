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

//72000000/16000 = 45000
//4500/9，500份
//100000/16000/500 = 
//10份开始

ch_attr_desc_t ch_attr_priv[3] = {
	{0, LED_CCT_BASE_VALUE},
	{0, LED_CCT_BASE_VALUE},
	{0, LED_CCT_BASE_VALUE}
};

//4400-4500k
void cct_test(uint8_t dimmer)
{ 	

	ch_attr_priv[0].dimmer = dimmer;
	
	float pause = 1000000.0f/16000.0f;
    float min = pause/256;
 //    printf("dimmer: %d%, cct pause: %0.4f, min pause:%0.6f\r\n", dimmer, pause, min);


	// printf("cct  | pc | pw us| pc v | pw v| \r\n");

	// printf("------------------------------\r\n");
	int i = 0 ;
	// static uint8_t cnt = 0;

 	// printf("cct_ch_t val%d[]={", cnt++);
 	
 	for (uint8_t cct = LED_CCT_BASE_VALUE; cct <= LED_CCT_BASE_MAX; cct++) {
		
		ch_attr_priv[0].cct = cct;		
		ch_cct_dimmer_to_pwm(&ch_attr_priv[0], &led_pwm, 0);

		printf(": %d, %02d00K, %03d, %03d, %0.3fus %0.3fus %0.5fV, %0.5fV\r\n", i,
			cct, led_pwm.pwm_value[0], led_pwm.pwm_value[1], led_pwm.pwm_value[0]*min,  led_pwm.pwm_value[1]*min, led_pwm.pwm_value[0]/100.0f*3, led_pwm.pwm_value[1]/100.0f*3);
		
		i++;
 	
        // printf("{%d, %d},", led_pwm.pwm_value[0], led_pwm.pwm_value[1]);
	}

	// printf("};\r\n");
}



