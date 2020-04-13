# CMakeLists for src directory
# declare project
project(LEETCODE_C)

# following C99 standard
set(CMAKE_C_STANDARD 99)

# find all source file in this directory
# and store them into variable CUR_DIR_SRCS
aux_source_directory(. CUR_DIR_SRCS)

# add lib for src
include_directories(../lib)

# add a library
add_library(Src ${CUR_DIR_SRCS})

# link lib for src
target_link_libraries(Src SupportLib)