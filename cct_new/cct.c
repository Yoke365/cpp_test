#include "cct.h"
#include "manual_ctrl.h"

#define CCT_FUN_DEBUG_EN   0

#if CCT_FUN_DEBUG_EN
#include <stdio.h>
#define CCT_FUN_DEBUG(format,...)   printf(format, ##__VA_ARGS__)
#else 
#define CCT_FUN_DEBUG(format,...)   
#endif 

uint16_t A_PWM(uint16_t cur_dim, uint16_t cct) 
{	
	uint16_t  pwm = 0;
	pwm = (cur_dim * ((float)cct/LED_CCT_BASE_NUM_FLOAT));
	return pwm;
}

uint16_t A_PWM_DMX(uint16_t cur_dim, uint16_t cct) 
{	
	uint16_t  pwm = 0;
	pwm = (cur_dim * ((float)cct/255.0f));

	return pwm;
}


const uint16_t ledLinear[] =
{
   0,
  45,  90, 135, 180, 225, 270, 315, 360, 405, 450,
 495, 540, 585, 630, 675, 720, 765, 810, 855, 900,
 945, 990,1035,1080,1125,1170,1215,1260,1305,1350,
1395,1440,1485,1530,1575,1620,1665,1710,1755,1800,
1845,1890,1935,1980,2025,2070,2115,2160,2205,2250,
2295,2340,2385,2430,2475,2520,2565,2610,2655,2700,
2745,2790,2835,2880,2925,2970,3015,3060,3105,3150,
3195,3240,3285,3330,3375,3420,3465,3510,3555,3600,
3645,3690,3735,3780,3825,3870,3915,3960,4005,4050,
4095,4140,4185,4230,4275,4320,4365,4410,4455,4500,
};

void pwm_counver(uint8_t value)
{
	uint8_t dimmer = (uint8_t)(value*255.0f/20.0f);
	CCT_FUN_DEBUG("%d,", dimmer);
}

void pwm_test(void)
{   
	CCT_FUN_DEBUG("\r\n{");
	for (uint8_t i = 0; i <=20; i++) {
		pwm_counver(i);
	}
	CCT_FUN_DEBUG("}\r\n");
}

void ch_cct_dimmer_to_pwm_dmx(ch_attr_desc_t *ch_attr_priv, led_pwm_t *pwm, uint8_t group)
{   
	uint8_t dimmer = ch_attr_priv->dimmer;
	pwm->pwm_value[2*group]   = A_PWM_DMX(dimmer, ch_attr_priv->cct);
	pwm->pwm_value[2*group+1] = B_PWM(dimmer, pwm->pwm_value[2*group]); 
}

void ch_cct_dimmer_to_pwm(ch_attr_desc_t *ch_attr_priv, led_pwm_t *pwm, uint8_t group)
{   
	uint16_t dimmer = ledLinear[ch_attr_priv->dimmer];

	pwm->pwm_value[2*group]   = A_PWM(dimmer, LED_CCT_GET_INDEX(ch_attr_priv->cct));
	pwm->pwm_value[2*group+1] = B_PWM(dimmer, pwm->pwm_value[2*group]); 
}

int16_t dimmer_abs(uint16_t in, uint16_t out)
{   
	uint16_t diff = 0;

	if (in >= out) {
		 diff = in-out;
	} else {
		 diff = out-in;
	}

	return diff;
}

static void pwm_update_calculate(uint8_t in_dimmer, uint8_t *out_dimmer)
{   
	static bool first = false;
	static float old = 0;
	if (!first) {
        old = in_dimmer;
   		first = true;
   		*out_dimmer = in_dimmer;
   		CCT_FUN_DEBUG("old: %f: \r\n", old);
   		return;
	}

	if (dimmer_abs((uint8_t)old, in_dimmer) <=1) {
		*out_dimmer = in_dimmer;
		old = in_dimmer;
		CCT_FUN_DEBUG("equal: old:%d, dimmer_out:%d\r\n", old, *out_dimmer);
		return;	
	}

	CCT_FUN_DEBUG("old: %f: \r\n", old);
	old = 0.7f*old + 0.3f * (float)in_dimmer;

	uint8_t old_interge = (uint8_t)old;
	if (old_interge >=1 && old_interge < 255) {
		old= (float)(old +0.5); //--0
	} 
     
    old = (uint8_t)old;
	*out_dimmer =old;	
}

void pwm_test1()
{
	uint8_t dimmer = 0;
	for (uint8_t i=0; i<=100; i++) {
		dimmer= ledLinear[i]; 
		CCT_FUN_DEBUG("---dimmer:%d, %d\r\n",i,dimmer);
	}
}

void cct_caculate_pwm(uint16_t dimmer, ch_attr_desc_t *ch_attr_priv, led_pwm_t *pwm, uint8_t group)
{
    // filter 
    float  pwm_float = 0;
   	uint16_t pwm_val = 0;
	pwm_float = (dimmer * ((float)LED_CCT_GET_INDEX(ch_attr_priv->cct)/LED_CCT_BASE_NUM_FLOAT));
	CCT_FUN_DEBUG("pwm_float:%f\r\n", pwm_float);
	if (pwm_float < 1) {
		if (ch_attr_priv->cct > LED_CCT_BASE_VALUE && dimmer) {
			pwm_val = 1;		
	    }
	} else {
		pwm_val = (uint16_t)pwm_float;
	}
   
    //caculate
	pwm->pwm_value[2*group]   = pwm_val;
	pwm->pwm_value[2*group+1] = B_PWM(dimmer, pwm->pwm_value[2*group]); 
}

int ch_cct_dimmer_to_pwm2(ch_attr_desc_t *ch_attr_priv, led_pwm_t *pwm, uint8_t group)
{   
	uint16_t dimmer = 0;

	dimmer= ledLinear[ch_attr_priv->dimmer];

	static uint16_t dimmer_out = 0;
	static bool limit_trigger = false;
	//pwm_update_calculate(dimmer, &dimmer_out);
	dimmer_out = dimmer;
	bool update = false;
    if (dimmer_abs(dimmer, dimmer_out) ==0) {
    	CCT_FUN_DEBUG("equal: dimmer:%d, dimmer_out:%d\r\n", dimmer, dimmer_out);
    	if (!limit_trigger) {
    		/* only run one time */
			CCT_FUN_DEBUG("dimmer_out: %d\r\n", dimmer_out);
			cct_caculate_pwm(dimmer_out, ch_attr_priv, pwm, group);
    		limit_trigger = true;
            update = true;
    	}
    } else {
    	limit_trigger = false;
    	update = true;
    }

	//cct update
	static uint8_t cct_old = 0;
	if ((cct_old != ch_attr_priv->cct) || update) {
		CCT_FUN_DEBUG("ch_attr_priv->cct:%d\r\n", ch_attr_priv->cct);
	    CCT_FUN_DEBUG("dimmer_out: %d\r\n", dimmer_out);

		cct_caculate_pwm(dimmer_out, ch_attr_priv, pwm, group);

		cct_old = ch_attr_priv->cct;
		return -1;
	} 

	return 0;
}
