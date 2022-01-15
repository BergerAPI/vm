cmake_minimum_required(VERSION 3.22.1)

project(vm)

# Getting every file recursively in the source directory
file(GLOB_RECURSE SRCS ./source/*.c)

add_executable(${PROJECT_NAME} ${SRCS})