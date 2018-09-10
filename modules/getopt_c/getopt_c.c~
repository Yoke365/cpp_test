#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	//enum MPU6000_BUS busid = MPU6000_BUS_ALL;
	//int device_type = MPU_DEVICE_TYPE_MPU6000;
	int ch;
	//enum Rotation rotation = ROTATION_NONE;
	int accel_range = 8;

	/* jump over start/off/etc and look at options first */
	while ((ch = getopt(argc, argv, "T:XISsZzR:a:")) != EOF) {
		printf("ch：　％c", ch);
		switch (ch) {
		case 'X':
		    //	busid = MPU6000_BUS_I2C_EXTERNAL;
            // printf("ch：　％c", ch);
			break;

		case 'I':
		//	busid = MPU6000_BUS_I2C_INTERNAL;
			break;

		case 'S':
		   //	busid = MPU6000_BUS_SPI_EXTERNAL1;
			break;

		case 's':
		   //	busid = MPU6000_BUS_SPI_INTERNAL1;
			break;

		case 'Z':
			//busid = MPU6000_BUS_SPI_EXTERNAL2;
			break;

		case 'z':
		   //	busid = MPU6000_BUS_SPI_INTERNAL2;
			break;

		case 'T':
		    //	device_type = atoi(optarg);
			printf("T: ％s\r\n", optarg);
			break;

		case 'R':
	    	//	rotation = (enum Rotation)atoi(optarg);
			printf("R: ％s\r\n", optarg);
			break;

		case 'a':
		   // accel_range = atoi(optarg);
			break;

		default:
		    //mpu6000::usage();
			exit(0);
		}
	}


	const char *verb = argv[optind];

	/*
	 * Start/load the driver.

	 */
	//if (!strcmp(verb, "start")) {
		//mpu6000::start(busid, rotation, accel_range, device_type);
	//	exit(0);  //normal exit
	//}
    
	exit(0);
}
