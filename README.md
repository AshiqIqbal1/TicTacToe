# TicTacToe

[![build](https://github.com/AshiqIqbal1/TicTacToe/actions/workflows/build.yml/badge.svg)](https://github.com/AshiqIqbal1/TicTacToe/actions/workflows/build.yml)

Unbeatable terminal tic-tac-toe in C++20, built on bitboards and minimax.

```
 X | 2 | 3
---|---|---
 4 | O | 6
---|---|---
 7 | 8 | X
```

## Build

Requires CMake 3.20+ and a C++20 compiler.

```sh
cmake -B build
cmake --build build
./build/TicTacToe
```

## How to play

- The bot plays **X** and moves first, opening on a random corner or the centre.
- You play **O**. Type a number from `1` to `9` to take that square.
- Type `q` (or press Ctrl-D) to quit.
- The score carries over between rounds.

The best you can do is draw.

## How it works

**Bitboards.** Each player is a single `uint16_t`. Bit `i` is set when that player owns square `i + 1`:

```
 0 | 1 | 2
---|---|---
 3 | 4 | 5
---|---|---
 6 | 7 | 8
```

A move is one OR (`p |= 1 << i`), a free square is `((p1 | p2) & (1 << i)) == 0`, and the board is full when `(p1 | p2) == 0x1FF`.

**Win detection.** All eight winning lines are fixed masks, so a win check is eight ANDs:

| Lines | Masks |
|---|---|
| Rows | `0x007`, `0x038`, `0x1C0` |
| Columns | `0x049`, `0x092`, `0x124` |
| Diagonals | `0x111`, `0x054` |

**Minimax.** The engine searches the full game tree from every free square. A bot win scores `10 - depth`, a loss scores `depth - 10`, and a draw scores `0`. Subtracting the depth makes the bot pick the fastest win and the slowest loss. The tree has at most 9! leaves, so the search needs no pruning or heuristics.

## Project layout

```
include/   board.hpp, engine.hpp, game.hpp
src/       board.cpp, engine.cpp, game.cpp, main.cpp
```

## License

[MIT](LICENSE)
