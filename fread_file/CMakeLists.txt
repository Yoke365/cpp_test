cmake_minimum_required (VERSION 2.6)
project (firmware_update)

include_directories("${PROJECT_BINARY_DIR}")

add_executable(main main.c packet.c crc16.c uart.c firmware_send.c)