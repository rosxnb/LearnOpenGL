# Minimum version of cmake needed to run following commands
cmake_minimum_required(VERSION 3.0.0)

# Generate the compile commands in JSON format to help clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Compiler variable (locally defined)
# set(CLANG_LINKER_FLAGS "-Llibglfw.3.3.dylib")
set(CLANG_COMPILE_FLAGS "-Wno-deprecated -Wall")

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_COMPILE_FLAGS}")


# Name of the project 
project(OpenGL_Setup VERSION 0.0.1)

set(DEPENDENCY_ROOT_PATH "~/Dependencies/opengl/")
set(TEMP ${DEPENDENCY_ROOT_PATH})
string(APPEND TEMP glad.c)

# Generate the application executable
add_executable(app main.cpp ${TEMP})

# Specify path to include directories 
target_include_directories(app PRIVATE ~/Dependencies/opengl/include/)

# Specify path to libraries
target_link_directories(app PRIVATE ~/Dependencies/opengl/library/)

target_link_libraries(app libglfw.3.3.dylib)

target_link_libraries(app
"-framework OpenGL"
"-framework Cocoa"
"-framework IOKit"
"-framework CoreVideo"
"-framework CoreFoundation"
)
