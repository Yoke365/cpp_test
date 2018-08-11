
include(CMakeParseArguments)

function(px4_parse_function_args)
	cmake_parse_arguments(IN "" "NAME" "OPTIONS;ONE_VALUE;MULTI_VALUE;REQUIRED;ARGN" "${ARGN}")
	cmake_parse_arguments(OUT "${IN_OPTIONS}" "${IN_ONE_VALUE}" "${IN_MULTI_VALUE}" "${IN_ARGN}")
	if (OUT_UNPARSED_ARGUMENTS)
		message(FATAL_ERROR "${IN_NAME}: unparsed ${OUT_UNPARSED_ARGUMENTS}")
	endif()
	foreach(arg ${IN_REQUIRED})
		if (NOT OUT_${arg})
			message(FATAL_ERROR "${IN_NAME} requires argument ${arg}\nARGN: ${IN_ARGN}")
		endif()
	endforeach()
	foreach(arg ${IN_OPTIONS} ${IN_ONE_VALUE} ${IN_MULTI_VALUE})
		set(${arg} ${OUT_${arg}} PARENT_SCOPE)
		message(STATUS "${arg} ${OUT_${arg}}")
	endforeach()
endfunction()

function(px4_add_module)

	px4_parse_function_args(
		NAME px4_add_module
		ONE_VALUE MODULE MAIN STACK PRIORITY
		MULTI_VALUE COMPILE_FLAGS LINK_FLAGS SRCS INCLUDES DEPENDS
		REQUIRED MODULE
		ARGN ${ARGN})

	add_library(${MODULE}   ${SRCS})
    
 #    add_library(MathFunctions ${CMAKE_SOURCE_DIR}/src/hello/hello.c)

	# add_library(queue ${CMAKE_SOURCE_DIR}/src/queue/dq_addafter.c 
	# 	${CMAKE_SOURCE_DIR}/src/queue/dq_addfirst.c   
	# 	${CMAKE_SOURCE_DIR}/src/queue/dq_rem.c 
	# 	${CMAKE_SOURCE_DIR}/src/queue/dq_remlast.c 
	# 	${CMAKE_SOURCE_DIR}/src/queue/sq_addafter.c 
	# 	${CMAKE_SOURCE_DIR}/src/queue/sq_addlast.c  
	# 	${CMAKE_SOURCE_DIR}/src/queue/sq_rem.c   
	# 	${CMAKE_SOURCE_DIR}/src/queue/sq_remlast.c 
	# 	${CMAKE_SOURCE_DIR}/src/queue/dq_addbefore.c 
	# 	${CMAKE_SOURCE_DIR}/src/queue/dq_addlast.c 
	# 	${CMAKE_SOURCE_DIR}/src/queue/dq_remfirst.c 
	# 	${CMAKE_SOURCE_DIR}/src/queue/sq_addfirst.c 
	# 	${CMAKE_SOURCE_DIR}/src/queue/sq_remafter.c 
	# 	${CMAKE_SOURCE_DIR}/src/queue/sq_remfirst.c)

	message(STATUS "MODULE::::::${MODULE} ${SRCS}")

    

	if(MAIN)
		set_target_properties(${MODULE} PROPERTIES
			COMPILE_DEFINITIONS PX4_MAIN=${MAIN}_app_main)
	endif()

	# if(INCLUDES)
	# 	target_include_directories(${MODULE} ${INCLUDES})
	# endif()

	if(DEPENDS)
		add_dependencies(${MODULE} ${DEPENDS})
	endif()

	#join list variables to get ready to send to compiler
	foreach(prop LINK_FLAGS COMPILE_FLAGS)
		if(${prop})
			px4_join(OUT ${prop} LIST ${${prop}} GLUE " ")
		endif()
	endforeach()

	foreach (prop COMPILE_FLAGS LINK_FLAGS STACK MAIN PRIORITY)
		if (${prop})
			set_target_properties(${MODULE} PROPERTIES ${prop} ${${prop}})
		endif()
	endforeach()

endfunction()


include_directories("${CMAKE_SOURCE_DIR}/src/hello")

# ADD_SUBDIRECTORY(queue)
# ADD_SUBDIRECTORY(hello)




include_directories("${CMAKE_SOURCE_DIR}/src/")
include_directories("${CMAKE_SOURCE_DIR}/src/queue")

add_executable(hello_bin ${CMAKE_SOURCE_DIR}/src/main.c ${CMAKE_SOURCE_DIR}/src/queue_unittest.c)

target_link_libraries(hello_bin ${MODULE})
target_link_libraries(hello_bin MathFunctions)