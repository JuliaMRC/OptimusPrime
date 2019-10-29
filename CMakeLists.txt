cmake_minimum_required(VERSION 3.14)
project(OptimusPrime)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(OptimusPrime src/main.c libs/queue/src/queue.c libs/queue/include/queue.h libs/queue/src/node.c libs/queue/include/node.h)