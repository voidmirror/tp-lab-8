cmake_minimum_required(VERSION 2.8)

# Make PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, and PROJECT_NAME available.
set(PROJECT_NAME TextGenerator) 
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall")

# If you want your own include/ directory, set this, and then you can do
# include_directories(${COMMON_INCLUDES}) in other CMakeLists.txt files.
# set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Define project sources and includes
#----------------------------------------------------------------------------
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})

set(SRC_FILES ${PROJECT_SOURCE_DIR}/src/TextGenerator.cpp)

set(CMAKE_CXX_STANDARD 11)

add_library(text_generator_lib ${SRC_FILES})
add_executable(text_generator ${PROJECT_SOURCE_DIR}/src/Main.cpp)

target_link_libraries(text_generator text_generator_lib)
