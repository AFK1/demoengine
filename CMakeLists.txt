cmake_minimum_required(VERSION 3.10)

project(swtebf_all)

option(BUILD_ENGINE "Build engine sources" ON)
option(BUILD_EXAMPLES "Build examples" ON)

add_subdirectory(engine)

if (BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)
