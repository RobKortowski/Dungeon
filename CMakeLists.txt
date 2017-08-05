cmake_minimum_required (VERSION 3.0)
project (Dungeon)

file(GLOB_RECURSE src      src/main/*.cpp src/main/*.h)
file(GLOB_RECURSE test_src src/test/*.cpp)
#file(GLOB_RECURSE res res/*)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_executable(
	dungeon
	${src}	
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++14 -Wall -Wfloat-conversion")
target_include_directories(dungeon PUBLIC src/main/headers)

#target_compile_options(dungeon PUBLIC -std=c++14 -Wall -Wfloat-conversion)


