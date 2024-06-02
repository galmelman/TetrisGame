#include "tetromino_class.h"
#include "Player_class.h"
#include <Windows.h>
#include <conio.h>
#define DOWN 'q'
// Static array containing shapes of Tetrominos
const char Tetromino::shapes[7][4][4] = {
	// I-shaped Tetromino
	{
		{ '#', '#', '#', '#'},
		{' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '}
	},

	// J-shaped Tetromino
	{
		{'#', ' ', ' ', ' '},
		{'#', '#', '#', ' '},
		{' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '}
	},

	// L-shaped Tetromino
	{
		{' ', ' ', '#', ' '},
		{'#', '#', '#', ' '},
		{' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '}
	},

	// O-shaped Tetromino
	{
		{'#', '#', ' ', ' '},
		{'#', '#', ' ', ' '},
		{' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '}
	},

	// S-shaped Tetromino
	{
		{' ', '#', '#', ' '},
		{'#', '#', ' ', ' '},
		{' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '}
	},

	// T-shaped Tetromino
	{
		{' ', '#', ' ', ' '},
		{'#', '#', '#', ' '},
		{' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '}
	},

	// Z-shaped Tetromino
	{
		{'#', '#', ' ', ' '},
		{' ', '#', '#', ' '},
		{' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '}
	}
};

// Constructor for Tetromino
Tetromino::Tetromino(int shapeIndex, int player)
{
	// Initialize currentShape based on the specified shapeIndex
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			currentShape[i][j] = shapes[shapeIndex][i][j];
		}
	}

	// Initial position of the Tetromino
	y = TetrisBoard::MIN_Y + 1;

	// Set the initial x position based on the player
	if (player == 1)
		x = TetrisBoard::MID_PLAYER1_BOARD_X;
	else
		x = TetrisBoard::MID_PLAYER2_BOARD_X;

	this->shapeIndex = shapeIndex;

	// Set the background color based on the shapeIndex
	this->backgroundColor = TetrisBoard::COLORS[shapeIndex + 1];
}

// Setter for x position
void Tetromino::setX(int newX) {
	// Optionally, you can add validation logic here
	x = newX;
}

// Setter for y position
void Tetromino::setY(int newY) {
	// Optionally, you can add validation logic here
	y = newY;
}

// Rotate the Tetromino clockwise
void Tetromino::rotateClockwise()
{
	// Save the current shape before rotation
	char tempShape[4][4];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			tempShape[i][j] = currentShape[i][j];
		}
	}

	// Perform the clockwise rotation
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			currentShape[i][j] = tempShape[3 - j][i];
		}
	}
	// Adjust the position after rotation
}

// Rotate the Tetromino counterclockwise
void Tetromino::rotateCounterclockwise()
{
	// Save the current shape before rotation
	char tempShape[4][4];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			tempShape[i][j] = currentShape[i][j];
		}
	}

	// Perform the counterclockwise rotation
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			currentShape[i][j] = tempShape[j][3 - i];
		}
	}
	// Adjust the position after rotation
}

// Apply a Tetromino move based on the key input
void Tetromino::applyTetrominoMove(Tetromino::ePlayersKeys key, Player& player)
{
	// Retrieve necessary information
	TetrisBoard playerBoard = player.getPlayerBoard();
	Tetromino playerTetromino = player.getPlayerTetromino();
	int x = playerTetromino.getX();
	int y = playerTetromino.getY();
	int shapeIndex = playerTetromino.getShapeIndex();

	// Check if the move is valid before applying it
	if (playerBoard.isValidMove(player, key))
	{
		// Apply the move based on the key
		switch (key)
		{
		case Tetromino::ePlayersKeys::PLAYER_1_LEFT:
		case Tetromino::ePlayersKeys::PLAYER_2_LEFT:
			playerTetromino.setX(x - 1);
			break;

		case Tetromino::ePlayersKeys::PLAYER_1_RIGHT:
		case Tetromino::ePlayersKeys::PLAYER_2_RIGHT:
			playerTetromino.setX(x + 1);
			break;

		case Tetromino::ePlayersKeys::PLAYER_1_ROTATE_CLOCKWISE:
		case Tetromino::ePlayersKeys::PLAYER_2_ROTATE_CLOCKWISE:
			playerTetromino.rotateClockwise();
			break;

		case Tetromino::ePlayersKeys::PLAYER_1_ROTATE_COUNTERCLOCKWISE:
		case Tetromino::ePlayersKeys::PLAYER_2_ROTATE_COUNTERCLOCKWISE:
			playerTetromino.rotateCounterclockwise();
			break;

		case Tetromino::ePlayersKeys::PLAYER_1_DROP:
		case Tetromino::ePlayersKeys::PLAYER_2_DROP:
			// Drop the Tetromino to the lowest possible position
			while (playerBoard.checkCollision(playerTetromino, player))
				playerTetromino.setY(playerTetromino.getY() + 1);
			playerTetromino.setY(playerTetromino.getY() - 1); // Move up by one to avoid collision
			break;

		default:
			playerTetromino.setY(y + 1);
			break;
		}

		// Update the player's Tetromino
		player.setPlayerTetromino(playerTetromino);
	}
	else
	{
		// Handle collision scenarios
		if (playerBoard.isFirstRowFilled())
			player.setIsLost(true);

		if (playerBoard.isLastTetrominoMove(player, x, y) && !player.checkIfLost())
		{
			playerBoard.addTetrominoToPlayerBoard(player, x, y);
			playerBoard.checkAndClearFullRows(player);
			player.setisNewTetrominoNeeded(true);
		}
	}
}
