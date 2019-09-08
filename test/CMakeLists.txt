cmake_minimum_required(VERSION 3.0)

project(minisketch_tests)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

find_path(SPDLOG_INCLUDE_DIR spdlog/spdlog.h)
find_library(FMT_LIBRARY fmt)
add_definitions(-DUSE_SPDLOG)
find_package(GTest MODULE REQUIRED)
set(GTEST_LIBRARIES GTest::GTest GTest::Main)
find_library(GMOCK_LIBRARY gmock)

include_directories(${SPDLOG_INCLUDE_DIR})

add_executable(minisketch_test minisketch_test.cpp)
target_link_libraries(minisketch_test minisketch ${GTEST_LIBRARIES} ${GMOCK_LIBRARY} ${FMT_LIBRARY})
add_test(AllTests minisketch_test
        COMMAND $<TARGET_FILE:minisketch_test>)
