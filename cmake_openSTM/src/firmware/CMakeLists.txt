
find_package(Threads)
add_compile_options(-std=c99)

set(FIRMWARE_NAME main)

add_executable(${FIRMWARE_NAME} 
	main.c)

target_link_libraries(${FIRMWARE_NAME} ${module_libraries})

target_link_libraries(${FIRMWARE_NAME} ${CMAKE_THREAD_LIBS_INIT})