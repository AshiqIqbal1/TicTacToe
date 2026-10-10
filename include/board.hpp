#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Board {
public:
  std::vector<std::string> to_string(uint16_t p1, uint16_t p2) const;
  void print_board(const std::vector<std::string> &b) const;
  void play_move(uint16_t &p, int move) const;
  bool did_player_win(uint16_t p) const;
  int check_winner(uint16_t player_1, uint16_t player_2) const;
  bool is_full(uint16_t player_1, uint16_t player_2) const;
  bool is_valid_move(uint16_t p1, uint16_t p2, int move) const;
};
