cmake_minimum_required(VERSION 3.16)
project(tictactoe CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -Werror)

# Link compile_commands.json into repo root so clangd/VS Code find it.
file(CREATE_LINK ${CMAKE_BINARY_DIR}/compile_commands.json
     ${CMAKE_SOURCE_DIR}/compile_commands.json SYMBOLIC)

add_library(tictactoe engine/tictactoe.cpp)
target_include_directories(tictactoe PUBLIC engine)

add_executable(ttt_engine engine/main.cpp)
target_link_libraries(ttt_engine PRIVATE tictactoe)

find_package(GTest QUIET)
if(NOT GTest_FOUND)
  include(FetchContent)
  FetchContent_Declare(googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz)
  FetchContent_MakeAvailable(googletest)
endif()

enable_testing()
add_executable(test_engine test/unit/test_engine.cpp)
target_link_libraries(test_engine PRIVATE tictactoe GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(test_engine)
