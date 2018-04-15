#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "file_autochange_char.h"

long 
filesize(FILE*stream)
{
	long curpos,length;
	
	curpos=ftell(stream);
	fseek(stream,0L,SEEK_END);
	length=ftell(stream);
	fseek(stream,curpos,SEEK_SET);
	
	return length;
}

int file_change_char(char *path, char *find_str)
{
	FILE *stream;
	
	stream=fopen(path,"rw+");
     
    /*　实现字符序号的替换功能　abc0, abc0. abc0...替换成　abc0, abc1, abc2*/
	fclose(stream); 
	
	return 0;
}