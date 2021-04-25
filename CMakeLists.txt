cmake_minimum_required(VERSION 3.5)

project(engine)

############################################################
# Set compiler flags
############################################################
set(OWN_GXX_FLAGS "-Wall -Wextra -fstack-protector-all -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS} -g -O3 -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS} -O3 -pthread")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS} -O3 -pthread")

############################################################
# List all sources
############################################################
set(engine_sources
		Utilities/easy_image.cc
	engine.cc
		Utilities/ini_configuration.cc
		2Dobjects/Point2D.cpp
        Figure/Face.cpp
        3Dobjects/vector3d.cc
        2Dobjects/Line2D.cpp
		Utilities/Color.cpp
		Utilities/Utils.cpp Utilities/Utils.h)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION ${PROJECT_SOURCE_DIR}/ )
