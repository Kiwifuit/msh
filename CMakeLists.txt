cmake_minimum_required(VERSION 3.20)

project(msh VERSION 0.0.1)

# set(IBUF_LEN "Input Buffer Length, in bytes" 256)
set(IBUF_LEN 256 CACHE STRING "Input buffer length")

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
# Configure the header file
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h
)

file(GLOB SOURCES src/*.c)
include_directories(include/)
add_executable(${PROJECT_NAME} ${SOURCES})