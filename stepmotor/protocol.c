#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "protocol.h"
#include "stepmotor.h"

cmd_table_t cmd_table[6] ={
    {4,   limit_switch_cmd, switch_on},
    {8,   limit_switch_cmd, switch_off},
    {12,  connitue_run_cmd, orientation_clockwise},
    {16,  connitue_run_cmd, orientation_anti_clockwise},
    {20,  stop_cmd,         mode_slow_down},
    {24,  stop_cmd,         mode_stutter_stop}
};


typedef struct {
    uint8_t    command;

    /* 转换后的  */
	uint16_t   base_val;
    uint16_t   new_val_max;
    
    /* 转换前的 */
	uint16_t   val_min;
	uint16_t   val_max;
}range_t;

const range_t val_range_table[4] = {
	{speed_init_cmd,     speed_init_base_value,    348, 1, 150},
	{speed_run_cmd,      speed_run_base_value,     746, 1, 150},
	{add_speed_time_cmd, add_speed_time_base_value,846, 1, 3000},
	{pulse_set_cmd,      add_speed_time_base_value,16942, 1, 5000}
};

void stemp_code_creat(void)
{ 
    uint16_t value = 0;

    value = 50;
	init_speed(&value, VALUE_FROM_0_START(val_range_table[0].val_min) , VALUE_FROM_0_START(val_range_table[0].val_max), 2);
    
	value+=100;
	init_speed(&value, VALUE_FROM_0_START(val_range_table[1].val_min), VALUE_FROM_0_START(val_range_table[1].val_max), 2);
    
	value+=100;
	init_speed(&value, VALUE_FROM_0_START(val_range_table[2].val_min),  VALUE_FROM_0_START(val_range_table[2].val_max), 2);
    
	value+=100;
	init_speed(&value, VALUE_FROM_0_START(val_range_table[3].val_min), VALUE_FROM_0_START(val_range_table[3].val_max), 2);
}

void init_speed(uint16_t *base, uint16_t min, uint16_t max, uint16_t scale)
{
    uint16_t min_new =0;
    uint16_t max_new =0;

    min_new = scale * min + *base;
    max_new = scale * max + *base; 
    
    *base   = max_new;
    printf("{%d, %d}\r\n",  min_new, max_new);
}

uint8_t old_type = 0;

/*　量化值　
    ＠value_new：　这个值是从０开始的，　相当于量化后的最小值，还会有自己的转换公式

    如果超出范围: 通过返回是-1得打
*/
int  pwm_cmd_prase(uint16_t value, uint8_t *type, uint16_t *value_new)
{   
    /* counter 6 */
    if (value < common_base_value) {
        for (uint8_t i = 0; i < 6; i++) {
            if (value == cmd_table[i].value) {
               *type = cmd_table[i].type; 
               *value_new = cmd_table[i].val;
                goto check;
            }
        }    
    }  else {
        /* counter 4 */
        for (uint8_t i = 0; i < 4; i++) {
            if (value >= val_range_table[i].base_val 
              && value <= val_range_table[i].new_val_max) {

                *type = val_range_table[i].command;
                *value_new  = (value - val_range_table[i].base_val) / 2 ;
                
                *value_new = VALUE_FROM_0_ADD(*value_new);
                goto check;
            }
        }
    }

error: 
    return -1;

check:  
    return 0;
}
