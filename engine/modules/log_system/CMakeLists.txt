cmake_minimum_required(VERSION 3.10)

# Module Name
project(demoengine_logsystem)

# Module config
add_library(${PROJECT_NAME}
  src/logSystem.c

  include/logSystem.h
  )

# Include header
target_include_directories(${PROJECT_NAME} PUBLIC
  include
  )

target_include_directories(${PROJECT_NAME} PUBLIC demo::engine)
target_link_libraries(${PROJECT_NAME} PUBLIC demo::engine)

# CMake module name
add_library(demo::logSystem ALIAS ${PROJECT_NAME})
