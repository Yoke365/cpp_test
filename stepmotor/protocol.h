#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include <stdint.h>

#define VALUE_FROM_0_START(x)     (x - 1)
#define VALUE_FROM_0_ADD(x)       (x + 1)

#define common_base_value          50
#define speed_init_base_value      50
#define speed_run_base_value       448
#define add_speed_time_base_value  846
#define pulse_set_base_value       6944


typedef struct {
    uint16_t value;
    uint8_t type;
    uint8_t val;
}cmd_table_t; 

void stemp_code_creat(void);
int  pwm_cmd_prase(uint16_t value, uint8_t *type, uint16_t *value_new);
void init_speed(uint16_t *base, uint16_t min, uint16_t max, uint16_t scale);

#endif /* _PROTOCOL_H */