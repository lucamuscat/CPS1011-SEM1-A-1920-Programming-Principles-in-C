cmake_minimum_required(VERSION 3.10)
project(task2)

set(CMAKE_C_STANDARD 11)

add_library(
  functions
  SHARED
  lib/basic_queue.c
  lib/basic_queue.h
  )

add_library(
  functions_2b
  SHARED
  lib/task2b_utils.c
  lib/task2b_utils.h
  lib/task2b_functions.c
  lib/task2b_functions.h
  lib/task2b_structs.h
  lib/rlp.c
  )


add_executable(task2 main.c lib/basic_queue.c)
target_link_libraries(task2 functions)

add_executable(task2b main_task2.c)
target_link_libraries(task2b functions_2b)
