#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "firmware_send.h"

#define PATH "/home/yangang/work/cpp_test/fread_file/test/bootloader_cube.bin"

bool task_exit = false;

int main(int argc, char **argv)
{   
    if (argc < 2) {
        return -1;
    }
    
    if (!strcmp(argv[1], "update")) {
        char *port = argv[2];
        if(update_firmware(PATH, port) == 0) {
            while(!task_exit) {
                sleep(2); 
            }
        }
    }

    if (!strcmp(argv[1], "help")) {
        printf("usage: ./openSTM_upload [--update <port> [--help]\r\n");
        printf("eg: ./openSTM_upload upload /dev/ttyUSB0\r\n");
    }

    return 0;
}


