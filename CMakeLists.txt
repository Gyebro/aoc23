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

add_executable(run_all_days
        sources/utils.cpp
        sources/day01.cpp
        sources/day02.cpp
        sources/day03.cpp
        sources/day04.cpp
        sources/day05.cpp
        sources/day06.cpp
        sources/day07.cpp
        sources/day08.cpp
        sources/day09.cpp
        sources/day10.cpp
        sources/day11.cpp
        sources/day12.cpp
        sources/day13.cpp
        sources/day14.cpp
        sources/day15.cpp
        sources/run_all.cpp)

add_executable(current_day
        sources/day16.cpp
        sources/utils.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(current_day PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(run_all_days PUBLIC OpenMP::OpenMP_CXX)
endif()

add_custom_target(copy_inputs ALL)
add_dependencies(run_all_days copy_inputs)
add_dependencies(current_day copy_inputs)

add_custom_command(TARGET copy_inputs POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/inputs"
        $<TARGET_FILE_DIR:run_all_days>)

enable_testing()

add_executable(day01_test sources/utils.cpp sources/day01.cpp tests/day01_test.cpp)
target_link_libraries(day01_test GTest::gtest_main)

add_executable(day02_test sources/utils.cpp sources/day02.cpp tests/day02_test.cpp)
target_link_libraries(day02_test GTest::gtest_main)

add_executable(day03_test sources/utils.cpp sources/day03.cpp tests/day03_test.cpp)
target_link_libraries(day03_test GTest::gtest_main)

add_executable(day04_test sources/utils.cpp sources/day04.cpp tests/day04_test.cpp)
target_link_libraries(day04_test GTest::gtest_main)

add_executable(day05_test sources/utils.cpp sources/day05.cpp tests/day05_test.cpp)
target_link_libraries(day05_test GTest::gtest_main)

add_executable(day06_test sources/utils.cpp sources/day06.cpp tests/day06_test.cpp)
target_link_libraries(day06_test GTest::gtest_main)

add_executable(day07_test sources/utils.cpp sources/day07.cpp tests/day07_test.cpp)
target_link_libraries(day07_test GTest::gtest_main)

add_executable(day08_test sources/utils.cpp sources/day08.cpp tests/day08_test.cpp)
target_link_libraries(day08_test GTest::gtest_main)

add_executable(day09_test sources/utils.cpp sources/day09.cpp tests/day09_test.cpp)
target_link_libraries(day09_test GTest::gtest_main)

add_executable(day10_test sources/utils.cpp sources/day10.cpp tests/day10_test.cpp)
target_link_libraries(day10_test GTest::gtest_main)


add_executable(day11_test sources/utils.cpp sources/day11.cpp tests/day11_test.cpp)
target_link_libraries(day11_test GTest::gtest_main)

add_executable(day12_test sources/utils.cpp sources/day12.cpp tests/day12_test.cpp)
target_link_libraries(day12_test GTest::gtest_main)

add_executable(day13_test sources/utils.cpp sources/day13.cpp tests/day13_test.cpp)
target_link_libraries(day13_test GTest::gtest_main)

add_executable(day14_test sources/utils.cpp sources/day14.cpp tests/day14_test.cpp)
target_link_libraries(day14_test GTest::gtest_main)

add_executable(day15_test sources/utils.cpp sources/day15.cpp tests/day15_test.cpp)
target_link_libraries(day15_test GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(day01_test)
