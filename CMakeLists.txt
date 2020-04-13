# CMakeLists for src directory
# declare the required minimum version of CMake
cmake_minimum_required(VERSION 3.0)

# declare the project
project(LEETCODE_C)

# add sub-directory of lib and src
add_subdirectory(lib)
add_subdirectory(src)

# set C99 standard
set(CMAKE_C_STANDARD 99)

# add .exe file
add_executable(${PROJECT_NAME} main.c)

# link
target_link_libraries(${PROJECT_NAME} SupportLib;Src)