cmake_minimum_required(VERSION 3.22.1)

project(vm)

add_executable(${PROJECT_NAME} source/vm.c source/main.c source/vector.c)