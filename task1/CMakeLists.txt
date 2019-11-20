cmake_minimum_required(VERSION 3.10)
project(task1)

set(CMAKE_C_STANDARD 11)

add_library(
  functions
  functions.c
  functions.h
  )

add_executable(task1 main.c)
target_link_libraries(task1 PRIVATE functions)
