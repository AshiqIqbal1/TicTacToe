#include <iostream>

class Game {
public:
  // Costructor
  Game() {};

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
