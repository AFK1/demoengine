cmake_minimum_required(VERSION 3.10)

project(demoengine_modules)

option(EXAMPLE_MODULE "Build example module" ON)
option(RENDER_MODULE "Build render module" ON)
option(LOGSYSTEM_MODULE "Build logSystem module" ON)
option(PHYSIC_MODULE "Build physic module" ON)

if(EXAMPLE_MODULE)
  message("Example module selected")
  target_compile_definitions(demoengine PUBLIC
    EXAMPLE_MODULE
    )
  add_subdirectory(example)
endif(EXAMPLE_MODULE)

if(RENDER_MODULE)
  message("Render module selected")
  target_compile_definitions(demoengine PUBLIC
    RENDER_MODULE
    )
  add_subdirectory(render)
endif(RENDER_MODULE)

if(LOGSYSTEM_MODULE)
  target_compile_definitions(demoengine PUBLIC
    LOGSYSTEM_MODULE
    )
  add_subdirectory(logsystem)
  set(logsystem_dirs "${CMAKE_CURRENT_SOURCE_DIR}/logsystem/include") 
else()
  set(logsystem_dirs "${CMAKE_CURRENT_SOURCE_DIR}/logsystem/include")
  target_include_directories(demoengine PUBLIC
    logsystem/ninclude
    )
endif(LOGSYSTEM_MODULE)

if(PHYSIC_MODULE)
  message("Physic module selected")
  target_compile_definitions(demoengine PUBLIC
    PHYSIC_MODULE
    )
  add_subdirectory(physic)
endif(PHYSIC_MODULE)


