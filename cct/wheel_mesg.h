#ifndef _WHEEL_MESG_H
#define _WHEEL_MESG_H

#include <stdint.h> 
#include <stdbool.h>

typedef struct {
	bool val;
}wheel_mesg_s;

void wheel_orb_publish(wheel_mesg_s *msg);
void wheel_orb_check(bool *update);
void wheel_orb_copy(wheel_mesg_s *msg);

#endif /* _WHEEL_MESG_H */

