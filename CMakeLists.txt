cmake_minimum_required(VERSION 3.20)

project(msh VERSION 0.0.1)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEBUG ON)
else()
    set(DEBUG OFF)
endif()

# Project Configuration
set(MSH_IBUF_LEN 256 CACHE STRING "Input buffer length")
set(DEBUG ${DEBUG} CACHE BOOL "Debug mode")

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h
)

file(GLOB SOURCES src/*.c)
include_directories(include/)
add_executable(${PROJECT_NAME} ${SOURCES})

message(STATUS "Project Configuration:")
get_cmake_property(_variableNames CACHE_VARIABLES)
foreach (_variableName ${_variableNames})
    get_property(_help CACHE ${_variableName} PROPERTY HELPSTRING)
    get_property(_type CACHE ${_variableName} PROPERTY TYPE)
    if(NOT _type STREQUAL "INTERNAL" AND _variableName MATCHES "^MSH")  # Exclude internal variables
        message(STATUS "  ${_variableName} = ${${_variableName}} (${_help})")
    endif()
endforeach()