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

add_executable(day01 sources/utils.cpp sources/day01.cpp)

add_executable(day02 sources/utils.cpp sources/day02.cpp)

add_executable(day03 sources/utils.cpp sources/day03.cpp)

add_custom_target(copy_inputs ALL)
add_dependencies(day01 copy_inputs)
add_dependencies(day02 copy_inputs)
add_dependencies(day03 copy_inputs)

add_custom_command(TARGET copy_inputs POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/inputs"
        $<TARGET_FILE_DIR:day01>)

enable_testing()

add_executable(day01_test sources/utils.cpp sources/day01.cpp sources/day01_test.cpp)
target_link_libraries(day01_test GTest::gtest_main)

add_executable(day02_test sources/utils.cpp sources/day02.cpp sources/day02_test.cpp)
target_link_libraries(day02_test GTest::gtest_main)

add_executable(day03_test sources/utils.cpp sources/day03.cpp sources/day03_test.cpp)
target_link_libraries(day03_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(day01_test)
