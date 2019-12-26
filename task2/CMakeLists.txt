cmake_minimum_required(VERSION 3.10)
project(task2)

set(CMAKE_C_STANDARD 11)

add_library(
  functions
  SHARED
  lib/task2a/task2a_functions.c
  lib/task2a/task2a_functions.h
  )

add_library(
  functions_2b
  SHARED
  lib/task2b/task2b_utils.c
  lib/task2b/task2b_utils.h
  lib/task2b/task2b_functions.c
  lib/task2b/task2b_functions.h
  lib/task2b/task2b_structs.h
  lib/task2b/rlp.c
  )


add_executable(task2 main.c lib/task2a/task2a_functions.c)
target_link_libraries(task2 functions)

add_executable(task2b main_task2b.c)
target_link_libraries(task2b functions_2b)
