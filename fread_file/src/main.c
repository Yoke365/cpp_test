#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "firmware_send.h"

#define PATH "/home/yangang/work/cpp_test/fread_file/test/bootloader_cube-v1.0.1.bin"

bool task_exit = false;

int main(int argc, char **argv)
{   
    if (argc < 2) {
        return -1;
    }
    
    if (!strcmp(argv[1], "update")) {
        char *port = argv[2];
        char *path = argv[3];
        if(update_firmware(path, port) == 0) {
            while(!task_exit) {
                sleep(2); 
            }
        }
    }

    if (!strcmp(argv[1], "help")) {
        printf("usage: ./openSTM_upload [--update <port>  <path> [--help]\r\n");
        printf("eg: ./openSTM_upload update /dev/ttyUSB0\r\n");
    }

    return 0;
}


