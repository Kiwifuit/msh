cmake_minimum_required(VERSION 3.20)

project(msh VERSION 0.0.1)

file(GLOB SOURCES src/*.c)
include_directories(include/)
add_executable(${PROJECT_NAME} ${SOURCES})