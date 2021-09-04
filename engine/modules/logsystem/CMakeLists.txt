cmake_minimum_required(VERSION 3.10)

# Linking in subcategories
cmake_policy(SET CMP0079 NEW)

project(demoengine_m_logsystem)

add_library(${PROJECT_NAME}
  src/logsystem.c

  include/logsystem.h
  )

target_include_directories(${PROJECT_NAME} PUBLIC
  include
  )

target_link_libraries(demoengine PUBLIC
  ${PROJECT_NAME}
  )
