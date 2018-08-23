include(common/px4_base)

#user cmake 
set(config_module_list
	modules/hello
	modules/queue
	modules/upload
	modules/calibrate
	modules/orbsim
	modules/add_variable
	modules/airspeed
	modules/file_size
	modules/time_os
	modules/c_pointer_fun
	modules/fprintf
	modules/nuttx_i2c
	modules/cct_demo
	#modules/pthread_mutex_test
	)
