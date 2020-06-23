cmake_minimum_required(VERSION 2.8)

# Make PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, and PROJECT_NAME available.
set(PROJECT_NAME textGenerator) 
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

add_executable(textGenerator ${PROJECT_SOURCE_DIR}/src/main.cpp)