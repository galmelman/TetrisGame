# Tetris Game

This is a two-player Tetris game implemented in C++. The game features a split-screen setup allowing two players to compete simultaneously.

## Features

- Two-player simultaneous gameplay
- Colorful Tetrominos (optional)
- Adjustable game speed
- Score tracking for each player
- Pause and resume functionality

## Controls

### Player 1 (Left side):
- Move Left: A
- Move Right: D
- Rotate Clockwise: S
- Rotate Counterclockwise: W
- Drop: X

### Player 2 (Right side):
- Move Left: J
- Move Right: L
- Rotate Clockwise: K
- Rotate Counterclockwise: I
- Drop: M

### General:
- Pause/Resume: ESC

## How to Play

1. Choose to start a new game with or without colors.
2. Select the game speed (Slow, Medium, or Fast).
3. Use the controls to move and rotate your Tetrominos.
4. Clear lines to score points.
5. The game ends when a player's board is filled to the top.
6. The player with the highest score wins!

## Building and Running

To build and run the game, you'll need a C++ compiler that supports C++11 or later. The game uses Windows-specific libraries, so it's currently only compatible with Windows systems.

1. Compile all the .cpp files together.
2. Run the resulting executable.

## Files

- `main.cpp`: The entry point of the game
- `tetrisGame_class.cpp/h`: Main game logic and loop
- `tetrisBoard_class.cpp/h`: Tetris board management
- `tetromino_class.cpp/h`: Tetromino (game piece) logic
- `player_class.cpp/h`: Player management
- `general.cpp/h`: Utility functions for console manipulation

## Future Improvements

- Add sound effects
- Implement a high score system
- Add different game modes (e.g., time attack, puzzle mode)
- Port to other platforms for cross-platform compatibility

Enjoy the game!
