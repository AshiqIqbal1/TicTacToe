#pragma once

#include "board.hpp"

#include <cstdint>

class Engine {
public:
  Engine(uint16_t &p1, uint16_t &p2);

  int minimax(const Board &board, bool is_maximising, int depth);
  void engine_move(const Board &board);

private:
  uint16_t &player_1;
  uint16_t &player_2;
};
