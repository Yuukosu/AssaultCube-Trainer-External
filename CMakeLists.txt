cmake_minimum_required(VERSION 3.22)
project(AssaultExternal)

set(CMAKE_CXX_STANDARD 20)

add_executable(AssaultExternal main.cpp Process.cpp Process.h Memory.cpp Memory.h)
