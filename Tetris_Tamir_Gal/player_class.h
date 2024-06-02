#ifndef __PLAYER_H
#define __PLAYER_H

#include "tetrisBoard_class.h"
#include "tetromino_class.h"

class Player
{
    TetrisBoard playerBoard;      // The player's Tetris board
    Tetromino playerTetromino;    // The current Tetromino controlled by the player
    int playerIndex = 1;          // Default player index
    bool isLost = false;          // Flag indicating whether the player has lost
    bool isNewTetrominoNeeded = false;  // Flag indicating whether a new Tetromino is needed
    int score = 0;                // Player's score

public:
    // Getter for the player's score
    int getScore() const { return score; }

    // Add points to the player's score
    void addToScore(int addedSum) { this->score += addedSum; }

    // Set the player's score to a specific value
    void setScore(int newScore) { this->score = newScore; }

    // Set whether the player has lost
    void setIsLost(bool lost) { isLost = lost; }

    // Set whether a new Tetromino is needed
    void setisNewTetrominoNeeded(bool isNeeded) { isNewTetrominoNeeded = isNeeded; }

    // Check if a new Tetromino is needed
    bool checkIfNewTetrominoNeeded() const { return isNewTetrominoNeeded; }

    // Check if the player has lost
    bool checkIfLost() const { return isLost; }

    // Set the player's Tetromino
    void setPlayerTetromino(const Tetromino& tetromino) { playerTetromino = tetromino; }

    // Get the player's current Tetromino
    const Tetromino& getPlayerTetromino() const { return playerTetromino; }

    // Get a reference to the player's Tetris board
    TetrisBoard& getPlayerBoard() { return playerBoard; }

    // Set the player's index
    void setIdx(int idx) { playerIndex = idx; }

    // Get the player's index
    int getPlayerIndex() { return playerIndex; }

    // Reset the player's Tetris board
    void resetBoard(TetrisBoard& board);
};

#endif
