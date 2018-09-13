#include "wheel_mesg.h"
#include <string.h>

wheel_mesg_s _wheel_mesg;
bool _update = false;

void wheel_orb_publish(wheel_mesg_s *msg)
{   
	wheel_mesg_s *mesg_inst = &_wheel_mesg;
	
	memcpy(mesg_inst, msg, sizeof(wheel_mesg_s));
	_update = true;
}

void wheel_orb_check(bool *update)
{	
	if (_update) {
		*update = true;
		return;
	} 

	*update = false;
}

void wheel_orb_copy(wheel_mesg_s *msg)
{	
	wheel_mesg_s *mesg_inst = &_wheel_mesg;
	if (_update) {
		memcpy(msg, mesg_inst, sizeof(wheel_mesg_s));
		_update = false;
	} 
}
