#include <conio.h> // for kbhit+getch
#include <iostream>
#include <Windows.h> // for Sleep and colors
using namespace std;

#include "player_class.h"

// Reset the player's Tetris board to its initial state
void Player::resetBoard(TetrisBoard& board)
{
    TetrisBoard newBoard;
    board = newBoard;
}
