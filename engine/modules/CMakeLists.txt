cmake_minimum_required(VERSION 3.10)

project(demoengine_modules)

option(EXAMPLE_MODULE "Build example module" ON)
option(RENDER_MODULE "Build render module" ON)
option(LOGSYSTEM_MODULE "Build logSystem module" ON)
option(ECS_MODULE "Build ECS module" ON)

if(EXAMPLE_MODULE)
  message("Example module selected")
  target_compile_definitions(demoengine PUBLIC
    EXAMPLE_MODULE
    )
  add_subdirectory(example)
endif(EXAMPLE_MODULE)

if(RENDER_MODULE)
  message("Example render selected")
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
else()
  target_include_directories(demoengine PUBLIC
    logsystem/include
    )
endif(LOGSYSTEM_MODULE)

if(ECS_MODULE)
  target_compile_definitions(demoengine PUBLIC
    ECS_MODULE
    )
  add_subdirectory(ecs)
endif(ECS_MODULE)
