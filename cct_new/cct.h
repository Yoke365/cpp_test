#ifndef _CCT_H_
#define _CCT_H_

#include <stdint.h>
#include "dimmer.h"

#define LED_CCT_BASE_VALUE 		0
#define LED_CCT_BASE_MAX  		255
#define LED_CCT_RANGE  		    3300

#define LED_CCT_BASE_NUM  		LED_CCT_BASE_MAX
#define LED_CCT_BASE_NUM_FLOAT  (255.0f)
#define LED_CCT_GET_INDEX(val)  (val - LED_CCT_BASE_VALUE)
#define ADD_VALUE_UNIT         (LED_CCT_RANGE/LED_CCT_BASE_NUM_FLOAT)

#define LED_CCT_COVER(a)       (2700+a*13)

int ch_cct_dimmer_to_pwm2(ch_attr_desc_t *ch_attr_priv, led_pwm_t *pwm, uint8_t group);
void ch_cct_dimmer_to_pwm_dmx(ch_attr_desc_t *ch_attr_priv, led_pwm_t *pwm, uint8_t group);
void ch_cct_dimmer_to_pwm(ch_attr_desc_t *ch_attr_priv, led_pwm_t *pwm, uint8_t group);

#endif /* _CCT_H_ */
