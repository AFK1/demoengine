cmake_minimum_required(VERSION 3.19)

project(ebfswt)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(include)

add_executable(${PROJECT_NAME}
src/glLoader.cpp
src/main.cpp
include/glLoader.hpp
include/swt.hpp
include/stb_image.h
)


target_link_libraries(${PROJECT_NAME}
glfw
OpenGL::GL
)
