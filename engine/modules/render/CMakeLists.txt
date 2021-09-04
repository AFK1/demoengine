cmake_minimum_required(VERSION 3.10)

# Linking in subcategories
cmake_policy(SET CMP0079 NEW)

project(demoengine_m_render)

add_library(${PROJECT_NAME}
  src/render.c
  src/glad.c

  include/render.h
  include/glad/glad.h
  include/GLFW/glfw3.h
  include/KHR/khrplatform.h
  )

target_include_directories(${PROJECT_NAME} PUBLIC
  include
  )

target_link_libraries(demoengine PUBLIC
  ${PROJECT_NAME}
  )
