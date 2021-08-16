cmake_minimum_required(VERSION 3.10)

project(swt_ebf_platformer
  LANGUAGES CXX
  )

include_directories(../../engine/include)

add_executable(${PROJECT_NAME}
  main.cpp
  )

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC
  swt_ebf::engine
  )
