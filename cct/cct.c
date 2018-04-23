/*
    1.32个等级线性调光
	1.调光是线性调光
	
	cct_max = 32;
	dim_max = 100us
	dim_scale = 0~100%
	
	cur_dim;
	cur_cct;
	高色温: a_pwm_pulse_width = (uint8_t)(cur_dim * cur_cct/cct_max)
	低色温: b_pwm_pulse_width  = cur_dim - a_pwm_pulse_width(pulse/us ); 

	调光:
	b_dimmer=a_dimmer=cur_dim;

	色温和调光值同时决定了，a,b两路的数据输出。
*/
#include "cct.h"
#include "manual_ctrl.h"

void ch_cct_dimmer_to_pwm(ch_attr_desc_t *ch_attr_priv, led_pwm_t *pwm, uint8_t group)
{
	pwm->pwm_value[2*group]   = A_PWM(ch_attr_priv->dimmer, LED_CCT_GET_INDEX(ch_attr_priv->cct));
	pwm->pwm_value[2*group+1] = B_PWM(ch_attr_priv->dimmer, pwm->pwm_value[2*group]); 		
}


