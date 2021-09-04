cmake_minimum_required(VERSION 3.10)

project(demoengine_modules)

option(LOG_SYSTEM "Enable log system" ON)
option(FARBFELD "Enable farbfeld support" ON)

if(LOG_SYSTEM)
  add_subdirectory(log_system)
endif(LOG_SYSTEM)

if(FARBFELD)
  add_subdirectory(farbfeld)
endif(FARBFELD)
