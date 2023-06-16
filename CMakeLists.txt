cmake_minimum_required(VERSION 3.12)
project(water)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        src/main.cc
        src/waves.cc
        glad/src/glad.c
        )

add_executable(water ${SOURCES})
target_include_directories(water PRIVATE glad/include)
target_link_libraries(water PRIVATE glfw)
