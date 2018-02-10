cmake_minimum_required(VERSION 2.8)
enable_language(CXX)
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
if(GNU)

endif(GNU)

find_package(GLUT)
find_package(GLEW)
find_package(OpenGL)

set(CPOT_SRC_ROOT "../Source")

file(GLOB_RECURSE SOURCES_RECURSE
	${CPOT_SRC_ROOT}/Cycle/*.cpp)

file(GLOB SOURCES
	${CPOT_SRC_ROOT}/Pot/Atom/*.cpp
	${CPOT_SRC_ROOT}/Pot/Config/Linux/*.cpp
	${CPOT_SRC_ROOT}/Pot/Audio/Linux/*.cpp
	${CPOT_SRC_ROOT}/Pot/Fps/*.cpp
	${CPOT_SRC_ROOT}/Pot/Game/*.cpp
	${CPOT_SRC_ROOT}/Pot/Linux/*.cpp
	${CPOT_SRC_ROOT}/Pot/ModelLoader/*.cpp
	${CPOT_SRC_ROOT}/Pot/Rand/*.cpp
	${CPOT_SRC_ROOT}/Pot/RandStandard/*.cpp
	${CPOT_SRC_ROOT}/Pot/Time/*.cpp
	${CPOT_SRC_ROOT}/Pot/TimeStandard/*.cpp
	${CPOT_SRC_ROOT}/Pot/ThirdParty/Include/Zlib/*.c)

add_definitions(-DCPOT_LINUX)
add_definitions(-DCPOT_64BIT)

include_directories(${CPOT_SRC_ROOT})
include_directories(${CPOT_SRC_ROOT}/Pot/ThirdParty/Include/Zlib)
add_executable(Main ${SOURCES} ${SOURCES_RECURSE})
target_link_libraries(Main ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${GLEW_LIBRARY} m)
