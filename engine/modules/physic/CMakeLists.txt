cmake_minimum_required(VERSION 3.10)

# Linking in subcategories
cmake_policy(SET CMP0079 NEW)

project(demoengine_m_physic)

add_library(${PROJECT_NAME}
  src/physic.c

  include/physic.h
  )

message("${logsystem_dirs}")

target_include_directories(${PROJECT_NAME} PUBLIC
  include
  ../../include
  ${logsystem_dirs}
  )
  
target_link_libraries(demoengine PUBLIC
  ${PROJECT_NAME}
  )
