cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_FLAGS "-O0 -std=c99")

ADD_LIBRARY(SimpleComputer STATIC memory.c register.c command.c memory.h register.h command.h)

ADD_EXECUTABLE(MySimpleComputer main.c)

TARGET_LINK_LIBRARIES(MySimpleComputer SimpleComputer)