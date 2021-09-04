cmake_minimum_required(VERSION 3.10)

project(demoengine_modules)

option(EXAMPLE_MODULE "Build example module" ON)

if(EXAMPLE_MODULE)
  message("Example module selected")
  target_compile_definitions(demoengine PUBLIC
    EXAMPLE_MODULE
    )
  add_subdirectory(example)
endif(EXAMPLE_MODULE)
