cmake_minimum_required (VERSION 2.6)
project (cmake_openSTM)

include_directories(
	${CMAKE_SOURCE_DIR}/src/modules/queue_unittest/include
	${CMAKE_SOURCE_DIR}/src/modules/hello/include
	${CMAKE_SOURCE_DIR}/src/modules/upload/include
	)

# CMAKE_MODULE_PATH is env virable
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(config_module "${CMAKE_MODULE_PATH}/configs/${CONFIG}.cmake")

message(STATUS ${config_module})
include(${config_module})

set(module_libraries)
foreach(module ${config_module_list})
	add_subdirectory(src/${module})
	px4_mangle_name(${module} mangled_name)
	list(APPEND module_libraries ${mangled_name})
endforeach()

add_subdirectory(src/firmware)





