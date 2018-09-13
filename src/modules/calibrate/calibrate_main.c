#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "firmware_send.h"

#define PATH "/home/yangang/work/cpp_test/fread_file/test/bootloader_cube-v1.0.1.bin"

bool task_exit = false;

//2.5 24bit
//accel  100mv/g  == > 
//2.5v   0g
//2.4v   -1g 
//2.6    1g
//+18g: 18g: 2.5V+1.8v = 4.3v   -18g : 2.5v - 1.8v = 0.7v 
// xxlsb/g
// y(g) = vlaue/xxlsb/g  y(g) = 


/* typedef定义    */
typedef struct
{
    int32_t x;
    int32_t y;
    int32_t z;
    
}ADXL356_AccRawXYZ;  

typedef struct
{
    int32_t ACC_X_Offset;
    float   ACC_X_Gain;
    
    int32_t ACC_Y_Offset;
    float   ACC_Y_Gain;
    
    int32_t ACC_Z_Offset;
    float   ACC_Z_Gain;
}ADXL356_AccCalibXYZ;    

ADXL356_AccCalibXYZ ADXL356_AccCalib;

void accel_scale_init(void)
{
    ADXL356_AccCalib.ACC_X_Offset = 0x3c0000;
    ADXL356_AccCalib.ACC_X_Gain = (7864320.0f * 0.1f)/5.0f;
    
    // ADXL356_AccCalib.ACC_Y_Offset = ADXL356_AccCalib.ACC_X_Offset;
    // ADXL356_AccCalib.ACC_Y_Gain = ADXL356_AccCalib.ACC_X_Gain;
    
    // ADXL356_AccCalib.ACC_Z_Offset = ADXL356_AccCalib.ACC_X_Offset;
    // ADXL356_AccCalib.ACC_Z_Gain = ADXL356_AccCalib.ACC_X_Gain;

    printf("offset:%d, sacle:%f\r\n", ADXL356_AccCalib.ACC_X_Offset, ADXL356_AccCalib.ACC_X_Gain);
}

void accel_covert(ADXL356_AccRawXYZ *in,  ADXL356_AccRawXYZ *out)
{
    out->x = ((in->x - ADXL356_AccCalib.ACC_X_Offset) / ADXL356_AccCalib.ACC_X_Gain);
    out->y = ((in->y - ADXL356_AccCalib.ACC_Y_Offset) / ADXL356_AccCalib.ACC_Y_Gain);
    out->z = ((in->z - ADXL356_AccCalib.ACC_Z_Offset) / ADXL356_AccCalib.ACC_Z_Gain);
}

ADXL356_AccRawXYZ in_data;
ADXL356_AccRawXYZ out_data;

int calibrate_main(int argc, char **argv)
{   
    accel_scale_init();

    // in_data.x = 0x3c0000
    // in_data.y = 0x3c0000
    // in_data.z = 0x3c0000

    //accel_covert(&in_data, &out_data);

    // if (argc < 2) {
    //     return -1;
    // }
    
    // if (!strcmp(argv[1], "update")) {
    //     char *port = argv[2];
    //     char *path = argv[3];
    //     if(update_firmware(path, port) == 0) {
    //         while(!task_exit) {
    //             sleep(2); 
    //         }
    //     }
    // }

    // if (!strcmp(argv[1], "help")) {
    //     printf("usage: ./openSTM_upload [--update <port>  <path> [--help]\r\n");
    //     printf("eg: ./openSTM_upload update /dev/ttyUSB0\r\n");
    // }

    return 0;
}


