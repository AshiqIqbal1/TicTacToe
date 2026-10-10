#include "engine.hpp"

#include <algorithm>
#include <climits>

Engine::Engine(uint16_t &p1, uint16_t &p2) : player_1(p1), player_2(p2) {}

int Engine::minimax(const Board &board, bool is_maximising, int depth) {
  int winner = board.check_winner(player_1, player_2);
  if (winner != 0) {
    return winner * (10 - depth);
  } else if (board.is_full(player_1, player_2)) {
    return 0;
  }

  uint16_t &mover = is_maximising ? player_1 : player_2;
  int best_score = is_maximising ? INT_MIN : INT_MAX;

  for (int i = 0; i < 9; i++) {
    uint16_t offset_mask = (1 << i);
    if (((player_1 | player_2) & offset_mask) == 0) {
      mover |= offset_mask;
      int score = minimax(board, !is_maximising, depth + 1);
      mover ^= offset_mask;
      best_score = is_maximising ? std::max(score, best_score)
                                 : std::min(score, best_score);
    }
  }
  return best_score;
}

void Engine::engine_move(const Board &board) {
  int best_score = INT_MIN;
  int best_move = -1;

  for (int i = 0; i < 9; i++) {
    uint16_t offset_mask = (1 << i);
    if (((player_1 | player_2) & offset_mask) == 0) {
      player_1 |= offset_mask;
      int score = minimax(board, false, 1);
      player_1 ^= offset_mask;
      if (score > best_score) {
        best_score = score;
        best_move = i;
      }
    }
  }

  if (best_move != -1) {
    player_1 |= (1 << best_move);
  }
}
