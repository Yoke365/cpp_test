
px4_add_module(
	MODULE cpp__px4_char_dev
	SRCS
		px4_char_dev_main.cpp
		serial.cpp
		cdev.cpp	
		fs.c
	)
