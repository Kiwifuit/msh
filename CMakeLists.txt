cmake_minimum_required(VERSION 3.20)

project(msh VERSION 0.0.1)

# Release build flags
set(CMAKE_C_FLAGS_RELEASE "-Os -flto" CACHE STRING "Release build flags" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-Os -flto" CACHE STRING "Release build flags" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE CACHE STRING "Linker flags" FORCE)


# CPack Configuration
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libreadline8 (>=8.1)")
set(CPACK_PACKAGE_CONTACT "Kiwifuit <mahkiwi123@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_CONTACT}")
set(CPACK_RESOURCE_FILE_LICENSE "../LICENSE")
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_BINARY_DIR}/artifacts")
set(CPACK_STRIP_FILES ON)
set(CPACK_GENERATOR "TGZ;DEB")

# Libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(READLINE REQUIRED readline)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEBUG ON)
else()
    set(DEBUG OFF)
endif()

# Project Configuration
set(DEBUG ${DEBUG} CACHE BOOL "Debug mode")
set(MSH_HISTFILE "~/.msh_history" CACHE STRING "Path to msh's history file")

# config.h Generation
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h
)

# Sources discovery
file(GLOB SOURCES src/*.c)
include_directories(include/)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${READLINE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${READLINE_LIBRARIES} history)
target_compile_options(${PROJECT_NAME} PRIVATE ${READLINE_CFLAGS_OTHER})

# Config Display
message(STATUS "Project Configuration:")
get_cmake_property(_variableNames CACHE_VARIABLES)
foreach (_variableName ${_variableNames})
    get_property(_help CACHE ${_variableName} PROPERTY HELPSTRING)
    get_property(_type CACHE ${_variableName} PROPERTY TYPE)
    if(NOT _type STREQUAL "INTERNAL" AND _variableName MATCHES "^MSH")  # Exclude internal variables
        message(STATUS "  ${_variableName} = ${${_variableName}} (${_help})")
    endif()
endforeach()

# Local install location
install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION bin)
include(CPack)

# Post-processing
if (CMAKE_BUILD_TYPE STREQUAL "Release")
  add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND strip --strip-unneeded ${CMAKE_PROJECT_NAME}
    COMMENT "Stripping binary to reduce size"
  )
endif()