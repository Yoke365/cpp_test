#ifndef __MANUAL_CTRL_H
#define __MANUAL_CTRL_H

// #include "Common.h"
// #include "param.h"
#include "dimmer.h"

#define DEBUG_PWM_UPDATE  0  
extern ch_attr_desc_t ch_attr_priv[3];
extern led_pwm_t led_pwm;
extern led_pwm_t led_sync_pwm;

void function_manual_mode_update(void);
void function_sync_mode_update(void);
void function_manual_mode_force_update(void);
void function_manual_mode_light_off(void);
#endif /* __MANUAL_CTRL_H  */

