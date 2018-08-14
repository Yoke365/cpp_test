#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "./include/firmware_send.h"

bool task_exit = false;

void usage(void)
{
    printf("usage: ./main [--update <port>  <path> [--help]\r\n");
    printf("eg: ./main update /dev/ttyUSB0 *.bin\r\n");
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

    if (!strcmp(argv[1], "help")) {
         usage();
    }

    return 0;
}


