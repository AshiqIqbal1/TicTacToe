#include "game.hpp"

#include <charconv>
#include <iostream>
#include <random>
#include <string>

Game::Game() : engine(player_1, player_2) {}

void Game::print() const {
  board.print_board(board.to_string(player_1, player_2));
}

std::optional<int> Game::read_move() const {
  std::string input;
  while (true) {
    std::cout << "Enter (1-9, q to quit): ";
    if (!(std::cin >> input) || input == "q") {
      return std::nullopt;
    }
    int move = 0;
    auto [ptr, ec] =
        std::from_chars(input.data(), input.data() + input.size(), move);
    if (ec == std::errc() && ptr == input.data() + input.size() &&
        board.is_valid_move(player_1, player_2, move)) {
      return move;
    }
  }
}

std::optional<int> Game::start_game() {
  const int choices[] = {1, 3, 7, 9, 5};

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<size_t> dist(0, std::size(choices) - 1);

  board.play_move(player_1, choices[dist(gen)]);
  print();

  while (true) {
    std::optional<int> move = read_move();
    if (!move) {
      return std::nullopt;
    }
    board.play_move(player_2, *move);
    engine.engine_move(board);
    print();

    int winner = board.check_winner(player_1, player_2);
    if (winner == 1) {
      std::cout << "\nPlayer 1 Won!\n";
      return 1;
    } else if (winner == -1) {
      std::cout << "\nPlayer 2 Won!\n";
      return -1;
    } else if (board.is_full(player_1, player_2)) {
      std::cout << "Draw!\n";
      return 0;
    }
  }
}
