cmake_minimum_required(VERSION 3.10)

# sublink
cmake_policy(SET CMP0079 NEW)

project(demo_e_platformer)

add_library(${PROJECT_NAME}
  main.c
  )

target_include_directories(${PROJECT_NAME} PRIVATE
  ../../engine/include
  )

target_link_libraries(demoengine PUBLIC
  ${PROJECT_NAME}
  )
