cmake_minimum_required (VERSION 2.6)
project (cct)

include_directories("${PROJECT_BINARY_DIR}")

add_executable(main main.c cct.c manual_ctrl.c)