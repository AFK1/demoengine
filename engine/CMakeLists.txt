cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0072 NEW) # GLX

project(swt_ebf_engine
  LANGUAGES CXX
  )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_INSTALL_MESSAGE LAZY )

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(include)

add_library(${PROJECT_NAME} STATIC
  src/demoengine.cpp
  src/logSystem.cpp
  src/farbfeld.cpp
  src/opengl/render.cpp
  src/stb_image.cpp

  include/demoengine.hpp
  include/logSystem.hpp
  include/farbfeld.hpp
  include/render.hpp

  src/glad.c
   "include/render.hpp")
add_library(swt_ebf::engine ALIAS ${PROJECT_NAME})

if(WIN32)
target_link_libraries(${PROJECT_NAME}
	Ws2_32.lib
  )
endif(WIN32)

target_link_libraries(${PROJECT_NAME}
  ${OPENGL_LIBRARIES}
  glfw
  )
