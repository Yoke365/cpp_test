#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "file_autochange_char.h"

int main(int argc, char argv[])
{    
    printf("start\r\n");

    file_change_char("file.txt", "abc");

	return 0;
}


