cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project(lists)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
