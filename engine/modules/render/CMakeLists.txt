cmake_minimum_required(VERSION 3.10)

# Linking in subcategories
cmake_policy(SET CMP0079 NEW)

project(demoengine_m_render)

add_library(${PROJECT_NAME}
  src/render.c
  src/glad.c

  include/render.h
  include/glad/glad.h
  include/KHR/khrplatform.h
  )

target_include_directories(${PROJECT_NAME} PUBLIC
  include
  )

target_link_libraries(demoengine PUBLIC
  ${PROJECT_NAME}
  )


# == GLFW ==

# GLX
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

target_link_libraries(${PROJECT_NAME} PUBLIC
  glfw
  OpenGL::GL
  )
