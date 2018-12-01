
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "./include/packet.h"

#define STREAM_REQ_CODE(fd, x)              pakect_send(fd, FW_UPDATE_REQ, x, 0);
#define STREAM_STATE_POLL_CODE(fd, x)       pakect_send(fd, STATE_POLL_CODE, x, 0);
#define STREAM_CONINUE_CODE(fd, x)          pakect_send(fd, CONNITUE_RUN_CODE, x, 2);
#define STREAM_STOP_CODE(fd, x)             pakect_send(fd, STOP_CODE, x, 2);

typedef struct color{
    uint8_t red_color;
    uint8_t green_color;
    uint8_t blue_color;
}color_t;

color_t color[3] = {
    {0xff, 0x00, 0x00},
    {0x00, 0xff, 0x00},
    {0x00, 0x00, 0xff},
};

void cmd_test(void)
{   

    for (uint8_t i = 0; i < 3 ; i++) {
       pakect_send(0, CMD_LED_COLOR, &color[i], 3);     
    }  
}


int _fd = -1;
uint8_t buf[128];
bool req = false;
bool ack = false;
packet_desc_t packet;
fw_packet_t _firmware_data;

int send_file(char *name)
{
    FILE *fp = NULL;
    char tmp[128];
    fp = fopen(name, "r");
    if (NULL == fp)
    {
        printf("File:%s open fail!\n", name);
        return -1;
    }
    
    fseek(fp, 0L, SEEK_END);  
    unsigned long filesize = ftell(fp); 
    printf("firmware len:%d\r\n", sizeof(fw_packet_t));
   
    _firmware_data.total_block = (filesize+IAP_FW_DATA_LEN)/IAP_FW_DATA_LEN;    
    _firmware_data.block_len = IAP_FW_DATA_LEN;

    fseek(fp, 0L, SEEK_SET);

    int time = 0;
    bool finish = false; 
    _firmware_data.cur_block = 1;
    do {
        int cnt = fread(tmp, 1, 128, fp);
        if (cnt < 128) { 
            printf("read finish: size: %dbytes, read cnt:%d\r\n", (_firmware_data.cur_block-1)*128+cnt, _firmware_data.cur_block);
            finish = true;
        } else {          
            printf("file read len: %dbytes, read cnt:%d\r\n", _firmware_data.cur_block*128, _firmware_data.cur_block);
        } 

        //create packet 
        memcpy(_firmware_data.data, tmp, cnt);
        _firmware_data.block_len = cnt;
        printf("total: %d, cur:%d, len:%d\r\n", _firmware_data.total_block, _firmware_data.cur_block, _firmware_data.block_len);
        pakect_send(0, FW_UPDATE_DATA, &_firmware_data, 6+_firmware_data.block_len);   
        _firmware_data.cur_block++;

        if (finish) {
            break;
        }
        usleep(200*1000);
    } while(1);
    fclose(fp);
    fp = NULL;

    return 0;
}

int protocal_send_frame_write(char *frame, int len)
{  
    if (_fd < 0)
    {  
        printf("error:%d\r\n",_fd);
        return 0;
    }

    int wlen = write(_fd, frame, len);
    return wlen;
    return 0;
}

int protocal_read(char *buf, int len)
{  
    if (_fd < 0) {  
        printf("error:%d\r\n",_fd);
        return -1;
    }

    if (len < 1) {  
        printf("len error:%d\r\n",len);
        return -1;
    }

    usleep(50*1000);

    return read(_fd, buf, len);
}

void send_request(void)
{
    int8_t val[2] = {1, 0x10};

    STREAM_REQ_CODE(0, val);
}

void packet_reply_cmd(uint8_t cmd)
{
    switch(cmd) {        
    case FW_UPDATE_ACK:
         printf("recv: FW_UPDATE_ACK\r\n"); 
         req = true;
        break;

    case FW_UPDATE_OK:
         printf("recv: FW_UPDATE_OK\r\n"); 
         ack = true;
         break;

    case FW_UPDATE_ERROR:
         printf("recv: FW_UPDATE_ERROR\r\n"); 
         ack = true;
         break;

    default :
        break;
    }
}

void serial_recv_thread(void)
{
    while(1)  {
        int cnt = read(_fd, buf, 128);
        if (cnt > 0) {
            printf("{ ");
            for (uint8_t i = 0; i < cnt; i++) {
                printf("%02x,", buf[i]);
                if(packet_parse_data_callback_buf(buf[i], &packet)) {
                    packet_reply_cmd(packet.data[0]);
                }
            }
            printf("}\r\n");
        }
        usleep(100*1000);
    }
}

int status_timeout(bool *flag, uint16_t time)
{   
    if (time  ==0 ) {
        printf("error\n");
    }

    do {
        if(*flag) {
            *flag = false; 
            return 0;
        }
        sleep(1);
        printf("1s timeout\r\n");
    } while(--time);

    return -1;
}

void update_file(char *name)
{   
    int ret = -1;

    //send request
    send_request();

    ret = status_timeout(&req, 5) ;
    if (ret < 0) {
        printf("req: timeout\r\n");
        return;  
    }

    //send file
    ret = send_file(name);
    if (ret < 0) {
        printf("send file filed\r\n");
        return;  
    }

    ret = status_timeout(&ack, 5) ;
    if (ret < 0) {
        printf("ack: timeout\r\n");
        return;  
    }
}


int update_firmware(char *name, char *path)
{
     //open serial
    _fd = serial_open(path);
    if(_fd < 0) {
        goto error;
    }   

    //create phtread 
    pthread_t thread;
    pthread_create(&thread, NULL, &serial_recv_thread, NULL );

    update_file(name);

    close(_fd); 
    return 0;
error:
    close(_fd);
    return -1;
}
#include "wolz_packet.h"

int wolz_test(char *path)
{
    const char*path_default = "/dev/ttyUSB0";

     //open serial
    _fd = serial_open(path);
    if(_fd < 0) {
        goto error;
    }   

    wolz_unittest(ACTURATOR_COMMAND_SET);

    close(_fd); 
    return 0;
error:
    close(_fd);
    return -1;
}