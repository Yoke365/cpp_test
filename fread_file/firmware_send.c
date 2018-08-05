#include "packet.h"
#include <stdio.h>
 #include <unistd.h>

#define STREAM_REQ_CODE(fd, x)              pakect_send(fd, FW_UPDATE_REQ, x, 0);
#define STREAM_STATE_POLL_CODE(fd, x)       pakect_send(fd, STATE_POLL_CODE, x, 0);
#define STREAM_CONINUE_CODE(fd, x)          pakect_send(fd, CONNITUE_RUN_CODE, x, 2);
#define STREAM_STOP_CODE(fd, x)             pakect_send(fd, STOP_CODE, x, 2);

void send_file(char *name)
{
    FILE *fp = NULL;
    char tmp[128];
    fp = fopen(name, "r");
    if (NULL == fp)
    {
        printf("File open fail!\n");
        return;
    }
    int time = 0;
    do {
        int cnt = fread(tmp, 1, 128, fp);
        if (cnt < 128) {
            time++;  
            printf("read finish: size: %dbytes, read cnt:%d\r\n", (time-1)*128+cnt, time);
            pakect_send(0, FW_UPDATE_DATA, tmp, cnt);          
            break;
        } else {
            time++;
            printf("file read len: %dbytes, read cnt:%d\r\n", time*128, time);
            pakect_send(0, FW_UPDATE_DATA, tmp, cnt); 
        }  
        usleep(200*1000);
    } while(1);
    fclose(fp);
    fp = NULL;
}

void send_request(void)
{
    int8_t val[2] = {1, 0x10};

    STREAM_REQ_CODE(0, val);
}

