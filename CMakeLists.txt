cmake_minimum_required(VERSION 3.21)

project(ebfswt)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(include)

add_executable(${PROJECT_NAME}
src/main.cpp
src/glad.c
)


target_link_libraries(${PROJECT_NAME}
  OpenGL::GL                           # Opengl
  glfw                                 # GLFW
)
