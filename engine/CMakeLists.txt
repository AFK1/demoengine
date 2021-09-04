cmake_minimum_required(VERSION 3.10)

# ==== Preconfig ====

# Set GLX build option
cmake_policy(SET CMP0072 NEW) # GLX

# Main project info
project(demoengine
  LANGUAGES CXX
  )

# CXX settings
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_INSTALL_MESSAGE LAZY )


# ==== Main ====

# Main compilation process
add_library(${PROJECT_NAME} STATIC
  src/demoengine.cpp
  src/opengl/render.cpp
  src/stb_image.cpp

  include/demoengine.hpp
  include/render.hpp

  src/glad.c
  include/render.hpp
  )

# Headers dirs
target_include_directories(${PROJECT_NAME} PUBLIC
  include
  )

# WIN32 fix
if(WIN32)
  target_link_libraries(${PROJECT_NAME}
    Ws2_32.lib
    )
endif(WIN32)

# CMake library name
add_library(demo::engine ALIAS ${PROJECT_NAME})


# ==== Graphics ====

# Graphics modules
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Graphics linking
target_link_libraries(${PROJECT_NAME}
  ${OPENGL_LIBRARIES}
  glfw
  )


# ==== Modules ====

add_subdirectory(modules)

if (LOG_SYSTEM)
  target_include_directories(${PROJECT_NAME} PRIVATE
    modules/log_system/include
    )
  target_link_libraries(${PROJECT_NAME}
    demo::logSystem
    )
endif(LOG_SYSTEM)

