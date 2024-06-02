#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include <Windows.h>
#include "tetromino_class.h"

// Forward declaration of Player 
class Player;

class TetrisBoard
{
public:
    static constexpr int BOARD_WIDTH = 14;
    static constexpr int MIN_Y = 5;
    static constexpr int BOARD_HEIGHT = 20;

    static constexpr int BORDER_WIDTH = 3;

    static constexpr int LEFT_PLAYER1_BORDER = 10;
    static constexpr int RIGHT_PLAYER1_BORDER = LEFT_PLAYER1_BORDER + BOARD_WIDTH;
    static constexpr int RIGHT_PLAYER2_BORDER = LEFT_PLAYER1_BORDER + (2 * BOARD_WIDTH) + BORDER_WIDTH;
    static constexpr int LEFT_PLAYER2_BORDER = RIGHT_PLAYER1_BORDER + BORDER_WIDTH;

    static constexpr int MID_PLAYER1_BOARD_X = LEFT_PLAYER1_BORDER + BOARD_WIDTH / 2;
    static constexpr int MID_PLAYER2_BOARD_X = LEFT_PLAYER2_BORDER + BOARD_WIDTH / 2;

    static const int NUM_OF_COLORS = 8;
    static const int COLORS[NUM_OF_COLORS];

    // Constructor
    TetrisBoard();

    // Methods

    // Draw the Tetris board with the given offset (x, y)
    void drawBoard(int x, int y);

    // Print the players' boards on the console
    void printPlayers();

    // Print the score of the specified player
    void printPlayerScore(Player& player);

    // Check if a move is valid for the given player and key
    bool isValidMove(Player player, const Tetromino::ePlayersKeys key);

    // Check for collision between a Tetromino and the player's board
    bool checkCollision(const Tetromino& tetromino, Player& player);

    // Check if the last move of a Tetromino is valid for the player
    bool isLastTetrominoMove(Player& player, int x, int y);

    // Add a Tetromino to the player's board at the specified position
    void addTetrominoToPlayerBoard(Player& player, int x, int y);

    // Generate a random Tetromino for the specified player index
    Tetromino generateRandomTetromino(int playerIndex);

    // Check and clear full rows on the player's board
    void checkAndClearFullRows(Player& player);

    // Check if the first row of the board is filled
    bool isFirstRowFilled() const;

private:
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    // Other members and methods...

};

#endif // TETRIS_BOARD_H
