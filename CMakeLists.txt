cmake_minimum_required(VERSION 3.24)
project(weather-visualizer)

set(CMAKE_CXX_STANDARD 14)

# Find necessary libraries
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(Threads REQUIRED)

# Add include directories
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

# Add executable
add_executable(weather-visualizer main.cpp)

# Link libraries
target_link_libraries(weather-visualizer
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLUT_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT})