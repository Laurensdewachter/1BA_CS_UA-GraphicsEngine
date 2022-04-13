cmake_minimum_required(VERSION 3.5)

project(Engine)

############################################################
# Set compiler flags
############################################################
# If supported by your compiler, you can add the -Wall, -Wextra, –fstack-protector-all and -g3 flags here.
set(OWN_GXX_FLAGS "-std=c++14 -Wall -Werror -g3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
set(engine_sources build/utils/easy_image.cc engine.cc
        build/utils/ini_configuration.cc
        build/utils/l_parser.cc
        build/LSystems/2DLSystem.h
        build/utils/vector3d.cc
        build/3DLines.cpp
        build/CoordToPixel.cpp
        build/Intro.cpp build/LSystems/2DLSystem.cpp
        build/utils/PlatonicBodies.cpp
        build/utils/PlatonicBodies.h
        build/utils/Figure.h
        build/utils/Transformation.cpp build/utils/Transformation.h build/utils/Utils.cpp build/utils/Utils.h build/LSystems/3DLSystem.h build/LSystems/3DLSystem.cpp build/utils/ZBuffer.h)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION ${PROJECT_SOURCE_DIR}/ )
