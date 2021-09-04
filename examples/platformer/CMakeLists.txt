cmake_minimum_required(VERSION 3.10)

project(demoengine_ex_platformer
  LANGUAGES CXX
  )

add_executable(${PROJECT_NAME}
  main.c
  )

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC
  demoengine
  )
