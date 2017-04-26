/**
  字符串是以\0结束,但是字符串的长度不包括\0, 比如字符串是"abcde"
,那么字符串的长度就是5
*/

#include <string.h>
#include <stdio.h>

int main()
{
   char a[10]="hello";
    int  len = strlen(a);
	printf("len = %d\r\n", len);
}
