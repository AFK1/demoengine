cmake_minimum_required(VERSION 3.10)

project(demoengine_all)

if (WIN32)
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
endif(WIN32)

option(BUILD_ENGINE "Build engine sources" ON)
option(BUILD_EXAMPLES "Build examples" ON)

if (BUILD_ENGINE)
  add_subdirectory(engine)
endif(BUILD_ENGINE)

if (BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)
