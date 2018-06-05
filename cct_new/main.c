
#include <stdio.h>
#include <stdint.h>
#include "wheel_mesg.h"
#include "manual_ctrl.h"

uint16_t buf[101];

void print_info(uint16_t *buf, uint16_t len )
{
	printf("{\r\n");
	for (uint8_t i = 0; i <=len; i++) {
		printf("%4d,", buf[i]);
		if (!(i%10)) {
			printf("\r\n");
		}
	}
	printf("};\r\n");
}

void test1()
{

	uint8_t first = 11;
	float scale = (255.0f-11.0f)/99.0f;
	printf("scale:%f\r\n", scale);
    uint8_t value = 0;
  
    printf("{\r\n");
    buf[0] = 0;
    uint8_t i = 0;
	while(value <=255) {
		
		value = (uint8_t)(first + scale *i);
		buf[++i] = value;
		if (i == 101) {
			break;
		}

	}
	printf("};\r\n");
    
    print_info(buf, 100);
} 

void test()
{
	uint16_t first = 45;
	float scale = (4500.0f-0.0f)/100.0f;
	printf("scale:%f\r\n", scale);
    uint16_t value = 0;
  
    printf("{\r\n");
    buf[0] = 0;
    uint8_t i = 0;
	while(value <=4500) {
		
		value = (uint16_t)(first + scale *i);
		buf[++i] = value;
		if (i == 101) {
			break;
		}

	}
	printf("};\r\n");
    
    print_info(buf, 100);
} 

int main(int argc, char argv[])
{    
	// for (uint8_t i = 0 ; i < 100; i++) {
	// 	 cct_test(ledLinear[i]);
	// }
	//cct_test(2.5);
	//test();
	//pwm_cct(4);
	//pwm_dimmer();
	//pwm_test();
	// for (uint16_t i = 0; i < 50; i++) {
	// 	dmx_cct_test(100, i);
	// }
//test();
	dimmer_update();
	//pwm_test1();
	
 	//test();
	return 0;
}


