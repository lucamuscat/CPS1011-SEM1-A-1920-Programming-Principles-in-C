cmake_minimum_required(VERSION 3.10)
project(task2)

set(CMAKE_C_STANDARD 11)

add_library(
  functions
  SHARED
  lib/basic_queue.c
  lib/basic_queue.h
  )


add_executable(task2 main.c lib/basic_queue.c)
target_link_libraries(task2 functions)
