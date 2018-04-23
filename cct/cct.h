#ifndef _CCT_H_
#define _CCT_H_

#include <stdint.h>

#define LED_CCT_BASE_NUM_FLOAT  33.0f
#define LED_CCT_BASE_NUM  		33

#define LED_CCT_BASE_MAX  		60
#define LED_CCT_BASE_VALUE 		27

#define LED_CCT_GET_INDEX(VAL) (VAL - LED_CCT_BASE_VALUE)

#define A_PWM(cur_dim, cct) (uint8_t)(cur_dim * ((float)cct/LED_CCT_BASE_NUM_FLOAT))
#define B_PWM(cur_dim,a_pwm) (cur_dim-a_pwm)

#pragma pack(1)
struct ch_attr_desc_s{
	uint8_t dimmer;
	uint8_t cct;
};
#pragma pack ()

typedef struct ch_attr_desc_s ch_attr_desc_t;

#endif /* _CCT_H_ */
