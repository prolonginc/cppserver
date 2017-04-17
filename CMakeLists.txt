cmake_minimum_required(VERSION 3.6)
project(cppserver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Server.cpp Server.h Client.cpp Client.h Thread.cpp Thread.h)
add_executable(cppserver ${SOURCE_FILES})