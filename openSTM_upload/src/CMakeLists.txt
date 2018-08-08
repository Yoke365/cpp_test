
find_package(Threads)
add_compile_options(-std=c99)

include_directories("${PROJECT_BINARY_DIR}/src")
add_executable(openSTM_upload main.c packet.c crc16.c uart.c firmware_send.c serial.c)

target_link_libraries(openSTM_upload ${CMAKE_THREAD_LIBS_INIT})