#include <iostream>
#include <string>

class Board {
public:
  Board() {};
  ~Board() {};

  std::string to_string(uint16_t p1, uint16_t p2) {
    std::string board_str = "";
    board_str.reserve(9);
    for (int i = 0; i < 9; i++) {
      if ((p1 & (1 << i)) != 0) {
        board_str += "X";
      } else if ((p2 & (1 << i)) != 0) {
        board_str += "O";
      } else {
        board_str += std::to_string(i + 1);
      }
    }
    return board_str;
  };

  void print_board(std::string b) {
    std::cout << "\n";
    std::cout << " " << b[0] << " | " << b[1] << " | " << b[2] << "\n";
    std::cout << "---|---|---\n";
    std::cout << " " << b[3] << " | " << b[4] << " | " << b[5] << "\n";
    std::cout << "---|---|---\n";
    std::cout << " " << b[6] << " | " << b[7] << " | " << b[8] << "\n";
    std::cout << "\n";
  };

  void play_move(uint16_t *p, int move, bool *turn) {
    if (!is_valid_move(p, move)) {
      return;
    }

    *p = (*p | (1 << (move - 1)));
    *turn = !(*turn);
  };

private:
  bool is_valid_move(uint16_t *p, int move) {
    return (*p & (1 << (move - 1))) == 0;
  };
};

class Game {
public:
  uint16_t player_1 = 0;
  uint16_t player_2 = 0;
  bool is_player1_turn = true;

  Board *board;
  // Constructor
  Game() { board = new Board(); };

  // Deconstructor
  ~Game() {};

  void start_game() {
    int num;

    board->print_board(board->to_string(player_1, player_2));
    std::cout << "Enter: ";
    while (std::cin >> num) {
      if (is_player1_turn) {
        board->play_move(&player_1, num, &is_player1_turn);
        board->print_board(board->to_string(player_1, player_2));
        if (did_player_win(&player_1)) {
          std::cout << "\nPlayer 1 Won!\n";
          return;
        }
      } else {
        board->play_move(&player_2, num, &is_player1_turn);
        board->print_board(board->to_string(player_1, player_2));
        if (did_player_win(&player_2)) {
          std::cout << "\nPlayer 2 Won!\n";
          return;
        }
      }

      std::cout << "Enter: ";
    }
  };

  bool did_player_win(uint16_t *p) {
    return ((*p & 0x7) == 0x7) || ((*p & 0x38) == 0x38) ||
           ((*p & 0x1C0) == 0x1C0) || ((*p & 0x49) == 0x49) ||
           ((*p & 0x92) == 0x92) || ((*p & 0x124) == 0x124) ||
           ((*p & 0x111) == 0x111) || ((*p & 0x54) == 0x54);
  }
};

int main() {
  Game *game = new Game();
  game->start_game();

  return 0;
}
