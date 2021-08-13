cmake_minimum_required(VERSION 3.19)

project(ebfswt)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(include)

add_library(${PROJECT_NAME} STATIC
src/main.cpp
src/glad.c
src/log.cpp
src/farbfeld.cpp
include/swt.hpp
include/stb_image.h
include/farbfeld.hpp
)

if(WIN32)
target_link_libraries(${PROJECT_NAME}
Ws2_32
)
endif()

target_link_libraries(${PROJECT_NAME}
glfw
OpenGL::GL
)
