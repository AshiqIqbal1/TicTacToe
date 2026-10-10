#include "board.hpp"

#include <iostream>

std::vector<std::string> Board::to_string(uint16_t p1, uint16_t p2) const {
  std::vector<std::string> board_str;
  for (int i = 0; i < 9; i++) {
    if ((p1 & (1 << i)) != 0) {
      board_str.emplace_back("\033[1;32mX\033[0m");
    } else if ((p2 & (1 << i)) != 0) {
      board_str.emplace_back("\033[1;31mO\033[0m");
    } else {
      board_str.emplace_back(std::to_string(i + 1));
    }
  }
  return board_str;
}

void Board::print_board(const std::vector<std::string> &b) const {
  std::cout << "\n";
  std::cout << " " << b[0] << " | " << b[1] << " | " << b[2] << "\n";
  std::cout << "---|---|---\n";
  std::cout << " " << b[3] << " | " << b[4] << " | " << b[5] << "\n";
  std::cout << "---|---|---\n";
  std::cout << " " << b[6] << " | " << b[7] << " | " << b[8] << "\n";
  std::cout << "\n";
}

void Board::play_move(uint16_t &p, int move) const { p |= (1 << (move - 1)); }

bool Board::did_player_win(uint16_t p) const {
  return ((p & 0x7) == 0x7) || ((p & 0x38) == 0x38) ||
         ((p & 0x1C0) == 0x1C0) || ((p & 0x49) == 0x49) ||
         ((p & 0x92) == 0x92) || ((p & 0x124) == 0x124) ||
         ((p & 0x111) == 0x111) || ((p & 0x54) == 0x54);
}

int Board::check_winner(uint16_t player_1, uint16_t player_2) const {
  if (did_player_win(player_1)) {
    return 1;
  } else if (did_player_win(player_2)) {
    return -1;
  }
  return 0;
}

bool Board::is_full(uint16_t player_1, uint16_t player_2) const {
  return ((player_1 | player_2) & 0x1FF) == 0x1FF;
}

bool Board::is_valid_move(uint16_t p1, uint16_t p2, int move) const {
  if (move < 1 || move > 9) {
    return false;
  }
  return (p1 & (1 << (move - 1))) == 0 && (p2 & (1 << (move - 1))) == 0;
}
