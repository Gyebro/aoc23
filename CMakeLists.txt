cmake_minimum_required(VERSION 3.25)
project(aoc23)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(day01 utils.cpp day01.cpp main.cpp)

add_custom_command(TARGET day01 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/inputs"
        $<TARGET_FILE_DIR:day01>)

enable_testing()

add_executable(day01_test utils.cpp day01.cpp day01_test.cpp)
target_link_libraries(day01_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(day01_test)
