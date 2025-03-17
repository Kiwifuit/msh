cmake_minimum_required(VERSION 3.20)

project(msh VERSION 0.0.1)

find_package(PkgConfig REQUIRED)
pkg_check_modules(READLINE REQUIRED readline)

file(GLOB SOURCES src/*.c)
include_directories(include/)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${READLINE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${READLINE_LIBRARIES} history)
target_compile_options(${PROJECT_NAME} PRIVATE ${READLINE_CFLAGS_OTHER})

