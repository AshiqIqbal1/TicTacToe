#include <iostream>

class Board {
public:
  Board() {};
  ~Board() {};

  void print_board() {
    std::cout << " " << " | " << " " << " | " << " " << "\n";
    std::cout << "---------\n";
    std::cout << " " << " | " << " " << " | " << " " << "\n";
    std::cout << "---------\n";
    std::cout << " " << " | " << " " << " | " << " " << "\n";
  };
};

class Game {
public:
  Board *board;
  // Constructor
  Game() { board = new Board(); };

  // Deconstructor
  ~Game() {};

  void start_game() {
    int num;
    while (std::cin >> num) {
      std::cout << num << "\n";
    }
  };
};

int main() {
  Game *game = new Game();
  game->start_game();

  return 0;
}
