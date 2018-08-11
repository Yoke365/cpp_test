cmake_minimum_required (VERSION 2.6)
project (firmware_update)

include (cmake/config/nuttx_px4fmu-v2_default.cmake)




include_directories("${CMAKE_SOURCE_DIR}/src/lib/include")
include_directories("${CMAKE_SOURCE_DIR}/src/lib/firmware")

#user cmake 
set(config_module_list
	math/hello
	lib/queue
	)

set(module_libraries)
foreach(module ${config_module_list})
	add_subdirectory(src/${module})
	px4_mangle_name(${module} mangled_name)
	list(APPEND module_libraries ${mangled_name})
endforeach()
message(STATUS "module_libraries: ${module_libraries}")

add_subdirectory(src/firmware)







