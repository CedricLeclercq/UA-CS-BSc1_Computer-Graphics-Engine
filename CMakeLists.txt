cmake_minimum_required(VERSION 3.5)

project(engine)

############################################################
# Set compiler flags
############################################################
set(OWN_GXX_FLAGS "-Wall -Wextra -fstack-protector-all -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS} -g -O1 -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS} -O1 -pthread")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS} -O1 -pthread")

############################################################
# List all sources
############################################################
set(engine_sources
	engine.cc
		Utilities/ini_configuration.cc
		ExtraFeatures/Lsystems/l_parser.cc
		Lines/vector3d.cc
		Utilities/Utils.cpp Utilities/Utils.h
		ExtraFeatures/Lsystems/LSystemUtils.cpp
		ExtraFeatures/Lsystems/LSystemUtils.h
		ExtraFeatures/ViewFrustum.h
		Figure/ExtraAndUtils/FigureDrawer.h
		Figure/ExtraAndUtils/FigureUtils.h
		Figure/Figure.h
		Figure/Figure.cpp
		ExtraFeatures/ZBuffer.h
		ExtraFeatures/Light.h
		ExtraFeatures/InfPointLight.h
		Image/GenerateImage.h
		Image/easy_image.cc
		Image/easy_image.h ExtraFeatures/Shadow.h)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION ${PROJECT_SOURCE_DIR}/ )
