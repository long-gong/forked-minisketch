cmake_minimum_required(VERSION 3.0)

project(minisketch)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mpclmul")

INCLUDE(CheckIncludeFiles)


set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB FIELD_SRCs "${SRC_DIR}/fields/*.cpp")
set(SRCs ${FIELD_SRCs} ${SRC_DIR}/minisketch.cpp)

set(PACKAGE_NAME "minisketch")
set(PACKAGE_VERSION "0.0.1")
set(BUGREPORT_URL "http://github.com/sipa/minisketch/")
add_definitions(-DPACKAGE_NAME="${PACKAGE_NAME}" -DPACKAGE_TARNAME="${PACKAGE_NAME}" -DPACKAGE_VERSION="${PACKAGE_VERSION}" -DPACKAGE_STRING="${PACKAGE_NAME} ${PACKAGE_VERSION}" -DPACKAGE_BUGREPORT="${BUGREPORT_URL}" -DPACKAGE_URL="" -DPACKAGE="${PACKAGE_NAME}" -DVERSION="${PACKAGE_VERSION}")

macro(CHECK_HEADER_MARK_IF_EXISTS header def)
    CHECK_INCLUDE_FILES(header RESULT)
    message(STATUS "checking for ${header} ...")
    if (RESULT)
        add_definitions(-D${def}=1)
    endif ()
endmacro()

#-DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1
# -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_DLFCN_H=1 -DLT_OBJDIR=\".libs/\" -DHAVE_PTHREAD_PRIO_INHERIT=1 -DHAVE_PTHREAD=1 -DHAVE_CXX11=1 -DHAVE_CLMUL=1 -DHAVE_CLZ=1
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

# Copied from https://github.com/OpenChemistry/protobuf/blob/master/src/CMakeLists.txt
# Define to necessary symbol if this constant
# uses a non-standard name on your system
#function(pthread_test var)
#    message(STATUS "minisketch: doing try-compiles for pthread test")
#
#    set (_result "UNKNOWN")
#    foreach(PTHREAD_TEST PTHREAD_CREATE_JOINABLE PTHREAD_CREATE_UNDETACHED)
#        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMake/pthread_test.cc.in
#                ${CMAKE_CURRENT_BINARY_DIR}/CMake/pthread_test.cc
#                @ONLY)
#        try_compile(SUCCEED
#                ${CMAKE_CURRENT_BINARY_DIR}/CMake
#                ${CMAKE_CURRENT_BINARY_DIR}/CMake/pthread_test.cc)
#        if (SUCCEED)
#            set(_result "${PTHREAD_TEST}")
#            break()
#        endif ()
#    endforeach(PTHREAD_TEST)
#
#    set (pthread_test_result "${_result}" CACHE INTERNAL "")
#    set (${var} "${pthread_test_result}" PARENT_SCOPE)
#endfunction()


add_definitions(-DHAVE_CXX11=1)

file(GLOB HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(minisketch ${SRCs})


# Example
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example)

# Test
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

# Installation configuration
install(
        TARGETS minisketch
        EXPORT minisketch
        LIBRARY DESTINATION lib
)

install(
        FILES ${HEADER}
        CONFIGURATIONS Release
        DESTINATION include
)