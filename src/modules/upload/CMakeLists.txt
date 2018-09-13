

px4_add_module(
	MODULE modules__upload
	SRCS
		upload_main.c 
		packet.c 
		crc16.c 
		uart.c 
		firmware_send.c 
		serial.c
	)

