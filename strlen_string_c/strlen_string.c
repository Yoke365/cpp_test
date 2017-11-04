#include <string.h>
#include <stdio.h>

void send_char(char *p)
{
   printf("char: 0x%x\r\n", *p);
}

int main()
{
    char a[10]="hello";
    int  len = strlen(a);
	printf("len = %d\r\n", len);
  
    send_char((char *)0x1B);
}
