#include "game.hpp"

#include <iostream>

int main() {
  int player_1_score = 0;
  int player_2_score = 0;

  while (true) {
    Game game;
    std::optional<int> res = game.start_game();
    if (!res) {
      break;
    }
    if (*res == 1) {
      player_1_score++;
    } else if (*res == -1) {
      player_2_score++;
    }

    std::cout << "\n#################################################\n";
    std::cout << "############# PLAYER 1: " << player_1_score
              << " PLAYER 2: " << player_2_score << " ###########\n";
    std::cout << "#################################################\n";
  }

  return 0;
}
