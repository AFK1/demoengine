cmake_minimum_required(VERSION 3.10)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

project(swt_ebf_all)

option(BUILD_ENGINE "Build engine sources" ON)
option(BUILD_EXAMPLES "Build examples" ON)

add_subdirectory(engine)

if (BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)
