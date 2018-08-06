#include <stdio.h>
#include <stdint.h>

#define PATH "/home/yangang/work/cpp_test/fread_file/qxwz_bl.bin"

int _fd = -1;

int main(int argc, char **argv)
{   
    if (argc < 2) {
        return -1;
    }
    
    if (!strcmp(argv[1], "start")) {
        printf("_fd:%d\r\n", _fd);
        if (_fd <0) {
          _fd = serial_open(argv[2]);  
        }
        packet_fd(_fd);
        printf("fd:%d\r\n", _fd);
        goto out;
    }

    if (!strcmp(argv[1], "request")) {
        if (_fd <0) {
          _fd = serial_open(argv[2]);  
        }
        packet_fd(_fd);
        send_request();
        goto out;
    }

    if (!strcmp(argv[1], "update")) {
        if (_fd <0) {
          _fd = serial_open(argv[2]);  
        }
        packet_fd(_fd);
        send_file(PATH);
        goto out;
    }

out:
    close(_fd);

    return 0;
}