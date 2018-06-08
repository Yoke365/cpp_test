#ifndef _DIMMER_H
#define _DIMMER_H

#include <stdint.h>
#include <stdbool.h>

#pragma pack(1)
struct ch_attr_desc_s{
	uint8_t dimmer;
	uint8_t cct;
};
#pragma pack ()
typedef struct ch_attr_desc_s ch_attr_desc_t;

#define LED_PWM_CHANNEL_NUM  6
struct led_pwm_s {
	uint16_t  pwm_value[LED_PWM_CHANNEL_NUM];
	uint8_t  pwm_freq ;
	uint8_t  sync_dimmer;
	uint16_t dmx_addr ;
};
typedef struct led_pwm_s led_pwm_t;


#endif /* _DIMMER_H  */

