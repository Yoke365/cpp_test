#include	<stdio.h>
#include	<stdint.h>
#include	<string.h>
#include	<stdbool.h>


#define PX4IO_RC_INPUT_CHANNELS		18

uint16_t r_raw_rc_values_output[PX4IO_RC_INPUT_CHANNELS];
int sbus_output1 = 0;
typedef struct sbus_packet{
	uint16_t r_raw_rc_values[PX4IO_RC_INPUT_CHANNELS];
	uint16_t r_raw_rc_count;
	bool sbus_failsafe;
	bool sbus_frame_drop;
	uint32_t recv_count_debug;
	int fd;
	int channel_id;
}sbus_packet_t ;

sbus_packet_t input[2] ={
	{
		.fd = 1, //PA
		.channel_id = 0,
	},
	
	{
		.fd = 2,
		.channel_id = 1,
	}
};

int sbus_merge_num(uint16_t *input1_value, uint16_t input1_num, uint16_t *input2_value, uint16_t input2_num, uint16_t *output_value)
{   
	//一共是18个通道
	if ((input1_num + input2_num) != 18) {
		return -1;
	}
    
    //input1.....input2
	memcpy(output_value, input1_value, input1_num * sizeof(uint16_t));
	// memcpy(&output_value[input1_num], &input2_value[input1_num], input2_num * sizeof(uint16_t));

	return 0;
}

void sbus_merge_unittest(void)
{
    memset(r_raw_rc_values_output, 0x00, sizeof(r_raw_rc_values_output));
   
    for(uint16_t i = 0; i < 18; i++) {
    	input[0].r_raw_rc_values[i] = i+1;
    }

     for(uint16_t i = 0; i < 18; i++) {
    	input[1].r_raw_rc_values[i] = i+1;
    }

    int ret = sbus_merge_num(input[0].r_raw_rc_values, 9, input[1].r_raw_rc_values, 18-9, r_raw_rc_values_output);
    if (ret < 0) {
    	printf("merger error\r\n");
    }

    for(uint16_t i = 0; i < 18; i++) {
    	printf("channel %d: %d\r\n", i+1, r_raw_rc_values_output[i]);
    }
    
}


int sbus_main(int argc, char**argv)
{    
    sbus_merge_unittest();
	return 0;
}
