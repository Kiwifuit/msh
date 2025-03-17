cmake_minimum_required(VERSION 3.20)

project(msh VERSION 0.0.1)

find_package(PkgConfig REQUIRED)
pkg_check_modules(READLINE REQUIRED readline)

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

target_include_directories(${PROJECT_NAME} PRIVATE ${READLINE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${READLINE_LIBRARIES} history)
target_compile_options(${PROJECT_NAME} PRIVATE ${READLINE_CFLAGS_OTHER})

message(STATUS "Project Configuration:")
get_cmake_property(_variableNames CACHE_VARIABLES)
foreach (_variableName ${_variableNames})
    get_property(_help CACHE ${_variableName} PROPERTY HELPSTRING)
    get_property(_type CACHE ${_variableName} PROPERTY TYPE)
    if(NOT _type STREQUAL "INTERNAL" AND _variableName MATCHES "^MSH")  # Exclude internal variables
        message(STATUS "  ${_variableName} = ${${_variableName}} (${_help})")
    endif()
endforeach()
