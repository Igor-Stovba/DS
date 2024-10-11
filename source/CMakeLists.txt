cmake_minimum_required(VERSION 3.5.0)
project(Vector VERSION 0.1.0 LANGUAGES C CXX)

add_executable(${PROJECT_NAME} vector.cpp main.cpp)

include(CTest)
enable_testing()