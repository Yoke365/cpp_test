/*
    1.32���ȼ����Ե���
	1.���������Ե���
	
	cct_max = 32;
	dim_max = 100us
	dim_scale = 0~100%
	
	cur_dim;
	cur_cct;
	��ɫ��: a_pwm_pulse_width = (uint8_t)(cur_dim * cur_cct/cct_max)
	��ɫ��: b_pwm_pulse_width  = cur_dim - a_pwm_pulse_width(pulse/us ); 

	����:
	b_dimmer=a_dimmer=cur_dim;

	ɫ�º͵���ֵͬʱ�����ˣ�a,b��·�����������
*/
#include "cct.h"
#include "manual_ctrl.h"

void ch_cct_dimmer_to_pwm(ch_attr_desc_t *ch_attr_priv, led_pwm_t *pwm, uint8_t group)
{
	pwm->pwm_value[2*group]   = A_PWM(ch_attr_priv->dimmer, LED_CCT_GET_INDEX(ch_attr_priv->cct));
	pwm->pwm_value[2*group+1] = B_PWM(ch_attr_priv->dimmer, pwm->pwm_value[2*group]); 		
}


