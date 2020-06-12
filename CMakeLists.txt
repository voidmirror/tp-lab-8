cmake_minimum_required(VERSION 2.8)

project(task1)


file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)


add_executable(${CMAKE_PROJECT_NAME} ${MAIN_SRC} src/main.cpp ${MAIN_HEADERS})
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_range_for)

target_link_libraries(${CMAKE_PROJECT_NAME})