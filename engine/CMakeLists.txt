cmake_minimum_required(VERSION 3.10)

project(swt_ebf_engine
  LANGUAGES CXX
  )

find_package(glfw3 REQUIRED)
find_package(opengl REQUIRED)

include(include)

add_library(${CMAKE_PROJECT_NAME}
  src/swtebf.cpp
  )

target_link_libraries(${CMAKE_PROJECT_NAME}
  opengl32
  glfw
  )
