#include <iostream>
#include <string>

class Board {
public:
  Board() {};
  ~Board() {};

  std::vector<std::string> to_string(uint16_t p1, uint16_t p2) {
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
  };

  void print_board(std::vector<std::string> b) {
    std::cout << "\n";
    std::cout << " " << b[0] << " | " << b[1] << " | " << b[2] << "\n";
    std::cout << "---|---|---\n";
    std::cout << " " << b[3] << " | " << b[4] << " | " << b[5] << "\n";
    std::cout << "---|---|---\n";
    std::cout << " " << b[6] << " | " << b[7] << " | " << b[8] << "\n";
    std::cout << "\n";
  };

  void play_move(uint16_t *p1, uint16_t *p2, int move, bool *turn) {
    *p1 = (*p1 | (1 << (move - 1)));
    *turn = !(*turn);
  };

  bool did_player_win(uint16_t *p) {
    return ((*p & 0x7) == 0x7) || ((*p & 0x38) == 0x38) ||
           ((*p & 0x1C0) == 0x1C0) || ((*p & 0x49) == 0x49) ||
           ((*p & 0x92) == 0x92) || ((*p & 0x124) == 0x124) ||
           ((*p & 0x111) == 0x111) || ((*p & 0x54) == 0x54);
  }

  int check_winner(uint16_t &player_1, uint16_t &player_2) {
    if (did_player_win(&player_1)) {
      return 1;
    } else if (did_player_win(&player_2)) {
      return -1;
    }
    return 0;
  }

  bool is_full(uint16_t &player_1, uint16_t &player_2) {
    return ((player_1 | player_2) & 0x1FF) == 0x1FF;
  };

  bool is_valid_move(uint16_t *p1, uint16_t *p2, int move) {
    if (move < 1 || move > 9) {
      return false;
    }
    return (*p1 & (1 << (move - 1))) == 0 && (*p2 & (1 << (move - 1))) == 0;
  };
};

class Engine {
public:
  uint16_t &player_1;
  uint16_t &player_2;

  Engine(uint16_t &p1, uint16_t &p2) : player_1(p1), player_2(p2) {}
  ~Engine();

  int minimax(Board *board, bool is_maximising) {
    int winner = board->check_winner(player_1, player_2);
    if (winner == 0 && board->is_full(player_1, player_2)) {
      return 0;
    } else if (winner != 0) {
      return winner;
    }
    if (is_maximising) {
      int best_score = INT_MIN;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          int offset_mask = (1 << (i * 3 + j));
          if (((player_1 | player_2) & offset_mask) == 0) {
            player_1 |= offset_mask;
            int score = minimax(board, false);
            player_1 ^= offset_mask;
            best_score = std::max(score, best_score);
          }
        }
      }
      return best_score;
    } else {
      int best_score = INT_MAX;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          int offset_mask = (1 << (i * 3 + j));
          if (((player_1 | player_2) & offset_mask) == 0) {
            player_2 |= offset_mask;
            int score = minimax(board, true);
            player_2 ^= offset_mask;
            best_score = std::min(score, best_score);
          }
        }
      }
      return best_score;
    }
  };

  void engine_move(Board *board) {
    int best_score = INT_MAX;
    int best_move = -1;

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        uint16_t offset_mask = (1 << (i * 3 + j));
        if (((player_1 | player_2) & offset_mask) == 0) {
          player_2 |= offset_mask;
          int score = minimax(board, true);
          player_2 ^= offset_mask;

          if (score < best_score) {
            best_score = score;
            best_move = (i * 3 + j);
          }
        }
      }
    }

    player_2 |= (1 << best_move);
  };
};

class Game {
public:
  uint16_t player_1 = 0;
  uint16_t player_2 = 0;
  bool is_player1_turn = true;

  Board *board;
  Engine *engine;
  // Constructor
  Game() {
    board = new Board();
    engine = new Engine(player_1, player_2);
  };

  // Deconstructor
  ~Game() {};

  void start_game() {
    int move;
    board->print_board(board->to_string(player_1, player_2));
    std::cout << "Enter: ";
    while (std::cin >> move) {
      if (!board->is_valid_move(&player_1, &player_2, move)) {
        std::cout << "Enter: ";
        continue;
      } else if (is_player1_turn) {
        board->play_move(&player_1, &player_2, move, &is_player1_turn);
      }

      engine->engine_move(board);
      is_player1_turn = !is_player1_turn;

      board->print_board(board->to_string(player_1, player_2));

      char winner = board->check_winner(player_1, player_2);
      if (winner == 1) {
        std::cout << "\nPlayer 1 Won!\n";
        return;
      } else if (winner == -1) {
        std::cout << "\nPlayer 2 Won!\n";
        return;
      } else if (board->is_full(player_1, player_2)) {
        std::cout << "Draw!\n";
        return;
      }
      std::cout << "Enter: ";
    }
  };
};

int main() {
  Game *game = new Game();
  game->start_game();

  return 0;
};
