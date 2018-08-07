#ifndef _FIRMWARE_SEND_H
#define _FIRMWARE_SEND_H

#include <stdint.h>

void send_file(char *name);
void send_request(void);
void serial_recv_thread(void);
int update_firmware(char *name, char *path);

#endif /* _FIRMWARE_SEND_H*/

