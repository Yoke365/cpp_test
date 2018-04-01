#include <string.h>
#include <stdio.h>

typedef struct {
	char appkey[32];
	char appsecret[128];
	char device_ID[32];
	char device_Type[32];
} acount_info_t;

acount_info_t acount_info;

int fw_update_acount_info_set(char *buf, char length)
{
	char acount_buf[100];
    char i = 0;
    char found = 0;
	char len = 0;
	char found_index = 0;

	printf("fw_update_acount_info_set \r\n{");
	for(int i = 0; i < length; i++) {
		printf("%02x ", buf[i]);
	}
	printf("}\r\n");

	memset(acount_buf, 0x00, sizeof(acount_buf));
	for (int i = 0; i < length; i++) {
		acount_buf[found_index] = buf[i];
		if (buf[i] == ',') {
			char *info;
			switch (found) {
				case 0:
					info = acount_info.appkey;
					break;

				case 1:
					info = acount_info.appsecret;
					break;

				case 2:	
					info = acount_info.device_ID;
				    break;	

				case 3:	
					info = acount_info.device_Type;
				    break;
					
				default:
					break;
			}
			strncpy(info, acount_buf, found_index);
			printf("acount_buf: %s  found_index:%d\r\n", acount_buf, found_index);
			found_index = 0; 
			found++;
			memset(acount_buf, 0x00, sizeof(acount_buf));
			continue;
		} else {
			found_index++;
		}
	}
	strncpy(acount_info.device_Type, acount_buf, found_index);

	printf(acount_info.appkey); 
	printf("\r\n");
	printf(acount_info.appsecret);
	printf("\r\n");
	printf(acount_info.device_ID);
	printf("\r\n");
	printf(acount_info.device_Type);
	printf("\r\n");
}

// char buf1[] = "22927";
// char buf2[] = "3943c9913a370d2b0a005c9d0a0fc965251e1362f67e24d147b5d0688de4557a";
// char buf3[] = "456123";
// char buf4[] = "852963";


// char buf1[] = "1";
// char buf2[] = "2";
// char buf3[] = "3";
// char buf4[] = "4";

char buf1[] = "12";
char buf2[] = "23";
char buf3[] = "34";
char buf4[] = "45";

int main()
{
    char config_str[200];
	strncpy(acount_info.appkey, buf1, strlen(buf1));
	strncpy(acount_info.appsecret, buf2, strlen(buf2));
	strncpy(acount_info.device_ID, buf3, strlen(buf3));
	strncpy(acount_info.device_Type, buf4, strlen(buf4));
	
	sprintf(&config_str[1], "%s,%s,%s,%s", acount_info.appkey, acount_info.appsecret, 
		acount_info.device_ID, acount_info.device_Type);
	int len = strlen(&config_str[1]);
	config_str[0] = len;
	printf(config_str);
    printf("\r\n");

    fw_update_acount_info_set(&config_str[1], len);
	return 0;
}
