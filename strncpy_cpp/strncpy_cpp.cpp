    #include <iostream>  
    #include <string.h>  
    #include <stdio.h>  
    
	using namespace std;  
      
	unsigned char  i = 0;
    int main()  
    {  
        char str[4] = {0};  
        char *p = "a\0bcdefg";  
        strncpy(str, p, sizeof(str) - 1);  
        cout << str << endl;  
        
	 str[1] = 'w';
	for (i = 0; i < 4; i++) {
		printf("a[i]=0x%x\r\n", str[i]);
	}
        return 0;  
    }  
