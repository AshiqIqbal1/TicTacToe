cmake_minimum_required(VERSION 3.20)
project(tic_tac_toe CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (APPLE)
  list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/" "/usr/local/go/")
endif()

add_executable(TicTacToe src/main.cpp)
