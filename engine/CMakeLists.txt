cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0072 NEW) # GLX

project(swt_ebf_engine
  LANGUAGES CXX
  )

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(include)

add_library(${CMAKE_PROJECT_NAME}
  src/swtebf.cpp
  )

target_link_libraries(${CMAKE_PROJECT_NAME}
  opengl32
  glfw
  )
