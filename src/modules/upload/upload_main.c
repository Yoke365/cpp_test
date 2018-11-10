#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "./include/firmware_send.h"

extern void calc_crc_unittest(void);

bool task_exit = false;

void usage(void)
{
    printf("usage: ./main [--update <port>  <path> [--help]\r\n");
    printf("eg: ./main update /dev/ttyUSB0 *.bin\r\n");
}
#include "wolz_packet.h"
extern void wolz_unittest(command_code_t code);

struct struct_a_dump{
    int d;
    int e;
};

struct struct_a_dump a_dump;

const struct struct_a{
    struct struct_a_dump *a;
    int b;
    int c;
};

const struct struct_a a ={
    .a = &a_dump,
};

void test_struct_a(void)
{    

    const struct struct_a *p = &a;
    
    p->a->d = 1;

    //编译是不过的
    // p->b = 1;

    printf("d:%d\r\n",  p->a->d);
}


void test_str(char *str) 
{
    int a = 1; 
    int b = 2;
    sprintf(str, "%d*%d", a, b);
}

int upload_main(int argc, char **argv)
{   
    if (argc < 2) {
        return -1;
    }
    
    if (!strcmp(argv[1], "update")) {
        if (argc < 4) {
            usage();
            return -1;
        }
        char *port = argv[2];
        char *path = argv[3];
        if(update_firmware(path, port) == 0) {
            while(!task_exit) {
                sleep(2); 
            }
        }
    }

    if (!strcmp(argv[1], "test_const")) {
        test_struct_a();
        return 0;
    }




    if (!strcmp(argv[1], "test_str")) {

        char buf[20]; 

        memset(buf, 0x00, 20);
        test_str(buf);
        printf(buf);

        return 0;
    }
 

    if (!strcmp(argv[1], "crctest")) {
         calc_crc_unittest();
         return 0;
    }

    if (!strcmp(argv[1], "hardtest")) {
        if (argc >= 3) {
            char *port = argv[2];
            wolz_test(port);
        }
    }

    if (!strcmp(argv[1], "softtest")) {
        wolz_unittest(ACTURATOR_COMMAND_SET);
    }
    
    if (!strcmp(argv[1], "help")) {
         usage();
    }

    return 0;
}


