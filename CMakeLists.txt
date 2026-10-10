cmake_minimum_required(VERSION 3.20)
project(tic_tac_toe CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TicTacToe
  src/main.cpp
  src/board.cpp
  src/engine.cpp
  src/game.cpp
)

target_include_directories(TicTacToe PRIVATE include)
target_compile_options(TicTacToe PRIVATE -Wall -Wextra -Wpedantic)
