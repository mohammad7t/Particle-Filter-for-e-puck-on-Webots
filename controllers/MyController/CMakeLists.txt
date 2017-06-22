cmake_minimum_required(VERSION 3.7)
project(MyController)

#set(CMAKE_CXX_STANDARD 98)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

include_directories("C:/Program Files (x86)/Webots/include")
include_directories("C:/Program Files (x86)/Webots/include/controller/cpp")
add_definitions(-DWIN32 -mwindows)
link_directories("C:/Program Files (x86)/Webots/lib")

set(SOURCE_FILES MainController.cpp MainController.h Odometry.cpp Odometry.h common.h)
add_executable(MyController ${SOURCE_FILES})

target_link_libraries(MyController Controller CppController)
