#include "cct.h"
#include "manual_ctrl.h"

uint16_t A_PWM(uint16_t cur_dim, uint16_t cct) 
{	
	uint16_t  pwm = 0;
	pwm = (cur_dim * ((float)cct/LED_CCT_BASE_NUM_FLOAT));
	if (pwm < 10) {
		pwm = 10;
	}

	return pwm;
}


void ch_cct_dimmer_to_pwm(ch_attr_desc_t *ch_attr_priv, led_pwm_t *pwm, uint8_t group)
{
	pwm->pwm_value[2*group]   = A_PWM(ch_attr_priv->dimmer, LED_CCT_GET_INDEX(ch_attr_priv->cct));
	pwm->pwm_value[2*group+1] = B_PWM(ch_attr_priv->dimmer, pwm->pwm_value[2*group]); 
}


