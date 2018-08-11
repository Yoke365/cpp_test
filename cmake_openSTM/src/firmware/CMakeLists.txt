
set(FIRMWARE_NAME c_queue)

add_executable(${FIRMWARE_NAME} 
	main.c 
	queue_unittest.c)

target_link_libraries(${FIRMWARE_NAME} ${module_libraries})