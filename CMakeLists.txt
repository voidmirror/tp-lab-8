cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME textGenerator) 
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

add_executable(textGenerator ${PROJECT_SOURCE_DIR}/src/main.cpp)
