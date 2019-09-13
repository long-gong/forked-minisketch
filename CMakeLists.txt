cmake_minimum_required(VERSION 3.0)

project(minisketch)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mpclmul")
INCLUDE(CheckIncludeFiles)

option(ENABLE_GTEST "Build with Google Test enabled" ON)
option(ENABLE_EXAMPLE "Build with example enabled" ON)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB FIELD_SRCs "${SRC_DIR}/fields/*.cpp")
set(SRCs ${FIELD_SRCs} ${SRC_DIR}/minisketch.cpp)

set(PACKAGE_NAME "minisketch")
set(PACKAGE_VERSION "0.0.1")
set(BUGREPORT_URL "http://github.com/sipa/minisketch/")
add_definitions(-DPACKAGE_NAME="${PACKAGE_NAME}"
        -DPACKAGE_TARNAME="${PACKAGE_NAME}"
        -DPACKAGE_VERSION="${PACKAGE_VERSION}"
        -DPACKAGE_STRING="${PACKAGE_NAME} ${PACKAGE_VERSION}"
        -DPACKAGE_BUGREPORT="${BUGREPORT_URL}"
        -DPACKAGE_URL="" -DPACKAGE="${PACKAGE_NAME}"
        -DVERSION="${PACKAGE_VERSION}")

macro(CHECK_HEADER_MARK_IF_EXISTS header def)
    CHECK_INCLUDE_FILES(header RESULT)
    message(STATUS "checking for ${header} ...")
    if (RESULT)
        add_definitions(-D${def}=1)
    endif ()
endmacro()

check_include_files("stdlib.h;stdarg.h;string.h;float.h" STDC_HEADERS)
if (STDC_HEADERS)
    add_definitions(-DSTDC_HEADERS=1)
endif ()
CHECK_HEADER_MARK_IF_EXISTS("sys/type.h" HAVE_SYS_TYPES_H)
CHECK_HEADER_MARK_IF_EXISTS("stdlib.h" HAVE_STDLIB_H)
CHECK_HEADER_MARK_IF_EXISTS("string.h" HAVE_STRING_H)
CHECK_HEADER_MARK_IF_EXISTS("memory.h" HAVE_MEMORY_H)
CHECK_HEADER_MARK_IF_EXISTS("strings.h" HAVE_STRINGS_H)
CHECK_HEADER_MARK_IF_EXISTS("inttypes.h" HAVE_INTTYPES_H)
CHECK_HEADER_MARK_IF_EXISTS("stdint.h" HAVE_STDINT_H)
CHECK_HEADER_MARK_IF_EXISTS("unistd.h" HAVE_UNISTD_H)
CHECK_HEADER_MARK_IF_EXISTS("dlfcn.h" HAVE_DLFCN_H)


add_definitions(-DHAVE_CXX11=1)

file(GLOB HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(minisketch ${SRCs})

# Example
if (ENABLE_EXAMPLE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example)
endif()

# Test
if (ENABLE_GTEST)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()

# Installation configuration
install(
        TARGETS minisketch
        EXPORT minisketch
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

install(
        FILES ${HEADER}
        CONFIGURATIONS Release
        DESTINATION include
)