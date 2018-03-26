#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include <stdint.h>
typedef struct {
    uint16_t value;
    uint8_t type;
    uint8_t val;
}cmd_table_t; 

void stemp_code_creat(void);
void  pwm_cmd_prase(uint16_t value, uint8_t *type, uint16_t *value_new);
void init_speed(uint16_t *base, uint16_t min, uint16_t max, uint16_t scale);

#endif /* _PROTOCOL_H */