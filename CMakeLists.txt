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
        sources/day06.cpp
        sources/run_all.cpp)

add_executable(current_day
        sources/day11.cpp
        sources/utils.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(current_day PUBLIC OpenMP::OpenMP_CXX)
endif()

add_custom_target(copy_inputs ALL)
add_dependencies(run_all_days copy_inputs)
add_dependencies(current_day copy_inputs)

add_custom_command(TARGET copy_inputs POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/inputs"
        $<TARGET_FILE_DIR:run_all_days>)

enable_testing()

add_executable(day01_test sources/utils.cpp sources/day01.cpp sources/day01_test.cpp)
target_link_libraries(day01_test GTest::gtest_main)

add_executable(day02_test sources/utils.cpp sources/day02.cpp sources/day02_test.cpp)
target_link_libraries(day02_test GTest::gtest_main)

add_executable(day03_test sources/utils.cpp sources/day03.cpp sources/day03_test.cpp)
target_link_libraries(day03_test GTest::gtest_main)

add_executable(day04_test sources/utils.cpp sources/day04.cpp sources/day04_test.cpp)
target_link_libraries(day04_test GTest::gtest_main)

add_executable(day06_test sources/utils.cpp sources/day06.cpp sources/day06_test.cpp)
target_link_libraries(day06_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(day01_test)
