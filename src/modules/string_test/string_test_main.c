#include<stdio.h>
#include<string.h>

char out_buf[10][20];

int string_test_main(void)
{
    char buf[]="hello@boy@this@is@heima";
    char*temp = strtok(buf,"@");
	int next = 0;
    while(temp){
		strcpy(out_buf[next], temp);
        printf("%s ",out_buf[next]);
		next++;
        temp = strtok(NULL,"@");
    }
 
   printf("\r\n ");
   return 0;
}
