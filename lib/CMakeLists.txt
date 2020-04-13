# CMakeLists for lib directory
# declare project
project(LEETCODE_C)

# find all source file in this directory
# and store them into variable CUR_DIR_SRCS
aux_source_directory(. CUR_DIR_SRCS)

# following C99 standard
set(CMAKE_C_STANDARD 99)

# add a library
add_library(SupportLib ${CUR_DIR_SRCS})