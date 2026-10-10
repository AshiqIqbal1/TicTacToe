#pragma once

#include "board.hpp"
#include "engine.hpp"

#include <cstdint>
#include <optional>

class Game {
public:
  Game();
  Game(const Game &) = delete;
  Game &operator=(const Game &) = delete;

  std::optional<int> start_game();

private:
  uint16_t player_1 = 0;
  uint16_t player_2 = 0;
  Board board;
  Engine engine;

  void print() const;
  std::optional<int> read_move() const;
};
