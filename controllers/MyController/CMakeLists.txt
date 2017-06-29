cmake_minimum_required(VERSION 3.7)
project(MyController)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory("freeglut")
include_directories("freeglut/include")

include_directories("C:/Program Files (x86)/Webots/include")
include_directories("C:/Program Files (x86)/Webots/include/controller/cpp")
link_directories("C:/Program Files (x86)/Webots/lib")
add_definitions(-DWIN32 -mwindows)

set(SOURCE_FILES
        common.h common.cpp
        MainController.cpp MainController.h
        Odometry.cpp Odometry.h
        Visualizer.cpp Visualizer.h
        Particle.cpp Particle.h
        SensorModel.cpp SensorModel.h
        Observation.cpp Observation.h
        Cell.cpp Cell.h
        Point.cpp Point.h
        Map.cpp Map.h
        Gaussian.cpp Gaussian.h
        ParticleFilter.cpp ParticleFilter.h
        )

add_executable(MyController main.cpp ${SOURCE_FILES})
target_link_libraries(MyController Controller CppController freeglut)

add_executable(MyPlayground playground.cpp ${SOURCE_FILES})
target_link_libraries(MyPlayground Controller CppController freeglut)
