cmake_minimum_required(VERSION 3.6)
project(fx-V8)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp V8.cpp V8.h)
add_executable(fx-V8 ${SOURCE_FILES} V8.cpp V8.h)