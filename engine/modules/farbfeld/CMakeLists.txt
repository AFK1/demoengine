cmake_minimum_required(VERSION 3.10)

# Module Name
project(demoengine_farbfeld)

# Module config
add_library(${PROJECT_NAME}
  src/farbfeld.c

  include/farbfeld.h
  )

# Include header
target_include_directories(${PROJECT_NAME} PUBLIC
  include
  )

# CMake module name
add_library(demo::farbfeld ALIAS ${PROJECT_NAME})
