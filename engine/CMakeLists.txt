cmake_minimum_required(VERSION 3.10)

project(demoengine)

add_executable(${PROJECT_NAME}
  src/demoengine.c
  src/ecs.c

  include/demoengine.h
  include/ecs.h
  )
add_executable(demoengine::main ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
  include
  )

add_subdirectory(modules)
