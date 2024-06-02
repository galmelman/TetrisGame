#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "general.h"
#include "tetrisBoard_class.h"
#include "tetromino_class.h"
#include "player_class.h"
using namespace std;

// Static constant array of colors for Tetris blocks
const int TetrisBoard::COLORS[NUM_OF_COLORS] = { FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED, FOREGROUND_GREEN | FOREGROUND_BLUE, FOREGROUND_GREEN, FOREGROUND_RED, FOREGROUND_RED | FOREGROUND_GREEN, FOREGROUND_RED | FOREGROUND_BLUE, FOREGROUND_BLUE, FOREGROUND_INTENSITY | FOREGROUND_RED };

// Constructor for the TetrisBoard class
TetrisBoard::TetrisBoard()
{
    int i, j;

    // Initialize the board with empty spaces
    for (i = 0; i < TetrisBoard::BOARD_HEIGHT; i++)
    {
        board[i][0] = '|';
        board[i][TetrisBoard::BOARD_WIDTH - 1] = '|';

        for (j = 1; j < TetrisBoard::BOARD_WIDTH - 1; j++)
            board[i][j] = ' '; // Set each cell to an empty value
    }

    // Draw borders on the top and bottom of the board
    for (int j = 0; j < TetrisBoard::BOARD_WIDTH; j++)
    {
        if (j != 0 && j != TetrisBoard::BOARD_WIDTH - 1)
        {
            board[TetrisBoard::BOARD_HEIGHT - 1][j] = '-';
            board[0][j] = '-';
        }
    }
}

// Function to draw the Tetris board on the console
void TetrisBoard::drawBoard(int x, int y)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TetrisBoard::COLORS[0]);

    // Print player information above the board
    printPlayers();

    // Draw each cell of the board
    for (int i = 0; i < TetrisBoard::BOARD_HEIGHT; i++)
    {
        gotoxy(x, y + i);
        for (int j = 0; j < TetrisBoard::BOARD_WIDTH; j++)
            cout << board[i][j];

        cout << endl;
    }
}

// Function to print player information above the board
void TetrisBoard::printPlayers()
{
    // Print Player_1 on top of Player 1's side
    gotoxy(TetrisBoard::MID_PLAYER1_BOARD_X - 4, TetrisBoard::MIN_Y - 2);
    cout << "Player_1";

    // Print Player_2 on top of Player 2's side
    gotoxy(TetrisBoard::MID_PLAYER2_BOARD_X - 4, TetrisBoard::MIN_Y - 2);
    cout << "Player_2";
}

// Function to print the player's score above the board
void TetrisBoard::printPlayerScore(Player& player)
{
    if (player.getPlayerIndex() == 1)
    {
        // Print Player_1's score on top of Player 1's side
        gotoxy(TetrisBoard::MID_PLAYER1_BOARD_X - 4, TetrisBoard::MIN_Y - 1);
        cout << "Score: " << player.getScore();
    }
    else
    {
        // Print Player_2's score on top of Player 2's side
        gotoxy(TetrisBoard::MID_PLAYER2_BOARD_X - 4, TetrisBoard::MIN_Y - 1);
        cout << "Score: " << player.getScore();
    }
}

// Function to check if a move is valid
bool TetrisBoard::isValidMove(Player player, const Tetromino::ePlayersKeys key)
{
    Tetromino playerTetromino = player.getPlayerTetromino();
    Tetromino movedShape = playerTetromino;
    TetrisBoard playerBoard = player.getPlayerBoard();
    int x = movedShape.getX();
    int y = movedShape.getY();
    bool clockWise = true;

    switch (key)
    {
    case Tetromino::ePlayersKeys::PLAYER_1_LEFT:
    case Tetromino::ePlayersKeys::PLAYER_2_LEFT:
    {
        movedShape.setX(x - 1);
        return playerBoard.checkCollision(movedShape, player);
    }

    case Tetromino::ePlayersKeys::PLAYER_1_RIGHT:
    case Tetromino::ePlayersKeys::PLAYER_2_RIGHT:
    {
        movedShape.setX(x + 1);
        return playerBoard.checkCollision(movedShape, player);
    }

    case Tetromino::ePlayersKeys::PLAYER_1_ROTATE_CLOCKWISE:
    case Tetromino::ePlayersKeys::PLAYER_2_ROTATE_CLOCKWISE:
    {
        movedShape.rotateClockwise();
        return playerBoard.checkCollision(movedShape, player);
    }

    case Tetromino::ePlayersKeys::PLAYER_1_ROTATE_COUNTERCLOCKWISE:
    case Tetromino::ePlayersKeys::PLAYER_2_ROTATE_COUNTERCLOCKWISE:
    {
        movedShape.rotateCounterclockwise();
        return playerBoard.checkCollision(movedShape, player);
    }

    case Tetromino::ePlayersKeys::PLAYER_1_DROP:
    case Tetromino::ePlayersKeys::PLAYER_2_DROP:
        return true;

    default:
        movedShape.setY(y + 1);
        return playerBoard.checkCollision(movedShape, player);
    }
}

// Function to check for collisions between the Tetromino and the board
bool TetrisBoard::checkCollision(const Tetromino& tetromino, Player& player)
{
    int x = tetromino.getX();
    int y = tetromino.getY();

    int shapeIndex = tetromino.getShapeIndex();
    int playerIndex = player.getPlayerIndex();
    TetrisBoard board = player.getPlayerBoard();
    int offSetX, offSetY;
    offSetY = TetrisBoard::MIN_Y;

    if (playerIndex == 1)
        offSetX = TetrisBoard::LEFT_PLAYER1_BORDER;
    else
        offSetX = TetrisBoard::LEFT_PLAYER2_BORDER;

    // Check for overlaps with the board
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if ((tetromino.getCurrentShapeChar(i,j) != ' ') && ((board.board[i + y - offSetY][j + x - offSetX] != ' ')))
                return false;
        }
    }

    return true;
}

// Function to check if the Tetromino is about to reach the bottom
bool TetrisBoard::isLastTetrominoMove(Player& player, int x, int y)
{
    TetrisBoard board = player.getPlayerBoard();
    Tetromino playerTetromino = player.getPlayerTetromino();
    int offSetX, offSetY;
    offSetY = TetrisBoard::MIN_Y;
    int playerIndex = player.getPlayerIndex();

    if (playerIndex == 1)
        offSetX = TetrisBoard::LEFT_PLAYER1_BORDER;
    else
        offSetX = TetrisBoard::LEFT_PLAYER2_BORDER;

    // Check for overlaps with the board
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (playerTetromino.getCurrentShapeChar(i,j) != ' ')
            {
                if (i + y - offSetY >= TetrisBoard::MIN_Y + TetrisBoard::BOARD_HEIGHT)
                    return true;
                if (board.board[i + y - offSetY + 1][j + x - offSetX] != ' ')
                    return true;
            }
        }
    }

    return false;
}

// Function to add the Tetromino to the player's board
void TetrisBoard::addTetrominoToPlayerBoard(Player& player, int x, int y)
{
    TetrisBoard& board = player.getPlayerBoard();
    Tetromino tetromino = player.getPlayerTetromino();
    int offSetX, offSetY;
    offSetY = TetrisBoard::MIN_Y;
    int playerIndex = player.getPlayerIndex();

    if (playerIndex == 1)
        offSetX = TetrisBoard::LEFT_PLAYER1_BORDER;
    else
        offSetX = TetrisBoard::LEFT_PLAYER2_BORDER;

    // Check for overlaps with the board
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (tetromino.getCurrentShapeChar(i,j) == '#')
                board.board[i + y - offSetY][j + x - offSetX] = '#';
        }
    }
}

// Function to generate a random Tetromino for the player
Tetromino TetrisBoard::generateRandomTetromino(int playerIndex)
{
    // Generate a random shape index (0 to 6) for the Tetromino
    int randomShapeIndex = rand() % 7;
    // Create and return a new Tetromino with the random shape
    Tetromino newTetromino(randomShapeIndex, playerIndex);
    return newTetromino;
}

// Function to check and clear full rows in the player's board
void TetrisBoard::checkAndClearFullRows(Player& player)
{
    TetrisBoard& board = player.getPlayerBoard();
    const int playerIndex = player.getPlayerIndex();
    const int offsetY = TetrisBoard::MIN_Y;
    const int offsetX = (playerIndex == 1) ? TetrisBoard::LEFT_PLAYER1_BORDER : TetrisBoard::LEFT_PLAYER2_BORDER;

    for (int i = TetrisBoard::BOARD_HEIGHT - 2; i > 0; --i)
    {
        bool fullRow = true;
        for (int j = 1; j < TetrisBoard::BOARD_WIDTH - 1; ++j)
        {
            if (board.board[i][j] == ' ')
            {
                fullRow = false;
                break;
            }
        }

        if (fullRow)
        {
            // Clear the full row
            for (int k = i; k > 0; --k)
            {
                for (int j = 1; j < TetrisBoard::BOARD_WIDTH - 1; ++j)
                {
                    board.board[k][j] = board.board[k - 1][j];
                }
            }

            // Add an empty row at the top
            for (int j = 1; j < TetrisBoard::BOARD_WIDTH - 1; ++j)
            {
                board.board[1][j] = ' ';
            }

            // Increment the player's score or perform any other necessary actions
            player.addToScore(1); // Add your scoring logic here
        }
    }
}

// Function to check if the first row is filled with blocks
bool TetrisBoard::isFirstRowFilled() const
{
    for (int j = 1; j < BOARD_WIDTH - 1; ++j)
    {
        if (board[1][j] != ' ')
        {
            return true;
        }
    }
    return false;
}
