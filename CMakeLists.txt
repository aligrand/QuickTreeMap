cmake_minimum_required(VERSION 3.24)

project(QuickTreeMap)

set(CMAKE_CXX_STANDARD 17)

include_directories(lib)

add_executable(QuickTreeMap test.cpp)

