#include <stdio.h>
#include <stdint.h>

#define PATH "/home/yangang/work/cpp_test/fread_file/qxwz_bl.bin"

int main(int argc, char **argv)
{   
    if (argc < 2) {
        return -1;
    }

    if (!strcmp(argv[1], "request")) {
        send_request();
    }

    if (!strcmp(argv[1], "update")) {
        send_file(PATH);
    }

    return 0;
}