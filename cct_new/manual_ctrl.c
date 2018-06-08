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

#define CCT_DEBUG_EN  1

#if CCT_DEBUG_EN
#define CCT_DEBUG(format,...)   printf(format, ##__VA_ARGS__)
#else 
#define CCT_DEBUG(format,...)   
#endif 

led_pwm_t led_pwm = {
	.pwm_freq = 10,
	.dmx_addr = 1,
};

float pwm_0;
float pwm_1;

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
	int i = 0 ;

 	for (uint8_t cct = LED_CCT_BASE_VALUE; cct <= LED_CCT_BASE_MAX; cct++) {
		
		ch_attr_priv[0].cct = cct;		
		ch_cct_dimmer_to_pwm(&ch_attr_priv[0], &led_pwm, 0);

		CCT_DEBUG(": %d, %02d00K, %03d, %03d, %0.3fus %0.3fus %0.5fV, %0.5fV\r\n", i,
			cct, led_pwm.pwm_value[0], led_pwm.pwm_value[1], led_pwm.pwm_value[0]*min,  led_pwm.pwm_value[1]*min, led_pwm.pwm_value[0]/100.0f*3, led_pwm.pwm_value[1]/100.0f*3);
		 i++;
	}
}

void dmx_cct_test(uint8_t dimmer, uint8_t cct)
{  
	ch_attr_priv[0].dimmer = dimmer;
	ch_attr_priv[0].cct = cct;
	ch_cct_dimmer_to_pwm_dmx(&ch_attr_priv[0], &led_pwm , 0);
	CCT_DEBUG("{%d, %d},", led_pwm.pwm_value[0], led_pwm.pwm_value[1]);
}

void pwm_cct(uint8_t dimmer)
{  
    float all = 2.5f + dimmer*5;
 	float min = all/10.0f;
    uint8_t i = 0;
 	for (uint8_t cct = LED_CCT_BASE_VALUE; cct <= LED_CCT_BASE_MAX; cct++) {

		 pwm_0 = min * LED_CCT_GET_INDEX(cct);
		 pwm_1 = all-pwm_0;

		 CCT_DEBUG("pwm0:pwm:%d, %f, %f\r\n", i, pwm_0, pwm_1);
		 i++;
	}
}

// (62.5-2.5)/12 = 0.5u add 
void pwm_dimmer()
{
	float min = 2.5f;

	for (uint8_t i = 0; i < 13; i++) {
		 CCT_DEBUG("dimmer:%d, %f\r\n", i, min+5*i);
	}
}

void dimmer_update()
{   
	printf("cct : %f\r\n", ADD_VALUE_UNIT);
    
    char value_str[6];

	memset(value_str, 0x00, 6);	
	snprintf(value_str, 4+1, "%04d", LED_CCT_COVER(1));
    printf("value_str:%s\r\n", value_str);
 

	// ch_attr_priv[0].dimmer = 255;
 //    for (uint16_t cct = LED_CCT_BASE_VALUE; cct <= LED_CCT_BASE_MAX; cct++) {
	// 	ch_attr_priv[0].cct = cct;
 //    	ch_cct_dimmer_to_pwm2(&ch_attr_priv[0], &led_pwm , 0);

	// 	CCT_DEBUG(": %02d00K, %4d, %04d,\r\n",
	// 		cct, led_pwm.pwm_value[0], led_pwm.pwm_value[1]);
	// }

	// ch_attr_priv[0].dimmer = 1;
 //    for (uint8_t cct = LED_CCT_BASE_VALUE; cct <= LED_CCT_BASE_MAX; cct++) {
	// 	ch_attr_priv[0].cct = cct;
 //    	ch_cct_dimmer_to_pwm2(&ch_attr_priv[0], &led_pwm , 0);

	// 	CCT_DEBUG(": %02d00K, %4d, %04d,\r\n",
	// 		cct, led_pwm.pwm_value[0], led_pwm.pwm_value[1]);
	// }


 //    ch_attr_priv[0].dimmer = 20;
	// ch_attr_priv[0].cct = 27;
    
 //    for (uint8_t i = 0; i < 100; i++) {
 //    	ch_attr_priv[0].dimmer = 20;
	// 	ch_attr_priv[0].cct = 27;
	//     int ret = ch_cct_dimmer_to_pwm2(&ch_attr_priv[0], &led_pwm , 0);
	//     if (ret == 0) {
	//     	break;
	//     }
 //    }
     
 //    printf("--------------------------------------");

 //     for (uint8_t i = 0; i < 100; i++) {
 //    	ch_attr_priv[0].dimmer = 10;
	// 	ch_attr_priv[0].cct = 27;
	//     int ret = ch_cct_dimmer_to_pwm2(&ch_attr_priv[0], &led_pwm , 0);
	//     if (ret == 0) {
	//     	break;
	//     }
	//     CCT_DEBUG("pmw0: pwm1: %d, %d\r\n", led_pwm.pwm_value[0], led_pwm.pwm_value[1]);
 //    }

 //     printf("--------------------------------dd------");

 //     for (uint8_t i = 0; i < 20; i++) {
 //    	ch_attr_priv[0].dimmer = 0;
	// 	ch_attr_priv[0].cct = i;
	//     int ret = ch_cct_dimmer_to_pwm2(&ch_attr_priv[0], &led_pwm , 0);
	//     if (ret == 0) {
	//     	break;
	//     }
	//     CCT_DEBUG("pmw0: pwm1: %d, %d\r\n", led_pwm.pwm_value[0], led_pwm.pwm_value[1]);
 //    }
}
