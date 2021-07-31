cmake_minimum_required(VERSION 3.21)

project(ebfswt)

find_package(OpenGL REQUIRED)


include_directories(include)

add_executable(${PROJECT_NAME}
src/main.cpp
src/glad.c
)


target_link_libraries(${PROJECT_NAME}
../glfw-3.3.4.bin.WIN64/lib-vc2019/glfw3.lib
../glfw-3.3.4.bin.WIN64/lib-vc2019/glfw3_mt.lib
../glfw-3.3.4.bin.WIN64/lib-vc2019/glfw3dll.lib
opengl32 
)